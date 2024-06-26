#include "Kuna.h"

// Konstruktor, mis loob uue Küna, võttes kotist juhuslikult max_arv_nuppe arvu nuppe.
Kuna::Kuna(short max_arv_nuppe, const shared_ptr<Kott> &kott) : m_max_arv_nuppe(max_arv_nuppe), m_nupud({}) {
    for (int i = 0; i < max_arv_nuppe; i++)
        m_nupud.push_back(kott->getJuhuslikNupp());
}

// Küna ekraanile kuvamiseks
ostream &operator<<(ostream &os, const Kuna &kuna) {
    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
    os << "nupud: ";
    for (const auto &it: kuna.m_nupud) {
        if (!it)
            return os;
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(2));
        os << *it;
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
        os << ", ";
    }
    return os;
}

// Tagastab viida nupule, kui see on künal, vastasel juhul tagastab nullptr.
shared_ptr<Nupp> Kuna::kasSisaldabNuppu(const char &taht) {
    for (auto nupp: m_nupud) {
        if (nupp->getTaht() == taht)
            return nupp;
    }
    return nullptr;
//    return std::any_of(m_nupud.begin(), m_nupud.end(), [nupp](const shared_ptr<Nupp> &el) { return nupp == *el; });
}

// Nupu/nuppude künal välja vahetamiseks
bool Kuna::vahetaNupp(vector<char> &tahed, shared_ptr<Kott> &kott) {
    // Kui kotis on vähem kui seitse nuppu või tahetakse üle 7 nupu korraga vahetada
    if (tahed.size() > 7) {
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(4));
        cout << "\nSaad vahetada kuni 7 tähte!\n";
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(7));
        return false;
    }
    if (kott->getNuppudeArv() < 7) {
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(4));
        cout << "\nKotis on alla 7 tähe.";
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(7));
        return false;
    }

    vector<pair<shared_ptr<Nupp>, char>> nupud;
    for (const char &taht: tahed)
        nupud.emplace_back(kasSisaldabNuppu(taht), taht);

    vector<char> leitudTahed;
    for (const auto &p: nupud) {
        if (p.first)
            leitudTahed.push_back(p.first->getTaht());
    }

    for (char t: leitudTahed) {
        tahed.erase(find(tahed.begin(), tahed.end(), t));
    }

    if (!tahed.empty()) {
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(4));
        cout << "\nNuppu ei ole künal (";
        char viimane = tahed[tahed.size() - 1];
        tahed.pop_back();
        for (char t: tahed) {
            SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(2));
            cout << t;
            SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(4));
            cout << ", ";
        }
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(2));
        cout << viimane;
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(4));
        cout << ")!";
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(7));
        return false;
    }

    for (char taht: leitudTahed) {
        for (int j = 0; j < m_nupud.size(); j++) {
            if (m_nupud[j]->getTaht() == taht) {
                m_nupud.erase(m_nupud.begin() + j);
                break;
            }
        }
        for (const auto &nupp: nupud) {
            if (nupp.first->getTaht() == taht) {
                m_nupud.push_back(kott->vahetaNupp(nupp.first));
                break;
            }
        }
    }
    // Kas kõik tähed said vahetatud.
    return true;
}

int Kuna::mituNuppuKunal() const {
    return m_nupud.size();
}

short Kuna::getMaxArvNuppeKunal() const {
    return m_max_arv_nuppe;
}

void Kuna::lisaNupp(const shared_ptr<Nupp> &nupp) {
    m_nupud.push_back(nupp);
}

bool Kuna::kasSisaldabKaiku(const shared_ptr<Kaik> &kaik) {
    map<char, int> nupud(TAHE_PUNKTID.begin(), TAHE_PUNKTID.end());

    for_each(nupud.begin(), nupud.end(), [](auto &el) { el.second = 0; });

    for_each(m_nupud.begin(), m_nupud.end(), [&nupud](auto el) { if (el) ++nupud[el->getTaht()]; });

    for (const auto &k: kaik->getKaik()) {
        char taht = k.second->getTaht();
        if (taht >= 97 && taht <= 122 || taht == '#')
            --nupud['?'];
        else
            --nupud[taht];
    }
//    for_each(kaik->getKaik().begin(), kaik->getKaik().end(), [&nupud](auto el) { --nupud[el.second->getTaht()]; });

// Trüki nupud, mida pole, välja
    return !any_of(nupud.begin(), nupud.end(), [](auto el) { return el.second < 0; });
}

void Kuna::eemaldaNupud(const shared_ptr<Kaik> &kaik) {
    for (const auto &k: kaik->getKaik()) {
        for (int i = m_nupud.size() - 1; i >= 0; i--) {
            char taht = k.second->getTaht();
            if (!m_nupud[i])
                continue;
            if (m_nupud[i]->getTaht() == taht) {
                m_nupud.erase(m_nupud.begin() + i);
                break;
            }
            if ((taht >= 97 && taht <= 122 || taht == '#') && m_nupud[i]->getTaht() == '?') {
                m_nupud.erase(m_nupud.begin() + i);
                break;
            }
        }
    }
}

bool Kuna::kasTyhi() {
    int summa = 0;
    for (const auto &nupp: m_nupud) {
        if (nupp)
            summa++;
    }
    return summa == 0;
}

int Kuna::kunaNuppudePunktid() const {
    int punktid = 0;
    for (const auto &nupp: m_nupud)
        punktid += nupp->getPunktid();
    return punktid;
}

void Kuna::printKuna() {
    shared_ptr<Nupp> viimane = m_nupud[m_nupud.size() - 1];
    for (int i = 0; i < m_nupud.size() - 1; i++) {
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(2));
        cout << *m_nupud[i];
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(7));
        cout << ", ";
    }
    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(2));
    cout << *viimane;
    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(7));
}
