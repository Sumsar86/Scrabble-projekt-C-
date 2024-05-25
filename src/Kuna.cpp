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

    bool vastus{true};
    for (int i = 0; i < nupud.size(); i++) {
        // Kui nuppu ei olnud künal
        if (nupud[i].first == nullptr) {
            SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(4));
            cout << "\nKüna: ";
            for (const auto &n: m_nupud)
                cout << *n << ", ";
            cout << "\nNupp ei ole künal! (" + string(1, nupud[i].second) + ")\n";
            SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(7));
            vastus = false;
            continue;
        }
        for (int j = 0; j < m_nupud.size(); j++)
            if (m_nupud[j]->getTaht() == tahed[i]) {
                m_nupud.erase(m_nupud.begin() + j);
                break;
            }
        m_nupud.push_back(kott->vahetaNupp(nupud[i].first));
    }

    if (!vastus) {
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(4));
        cout << "\nKõiki nuppe ei õnnestunud välja vahetada!\n";
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(7));
    }
    // Kas kõik tähed said vahetatud.
    return vastus;
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

    for_each(m_nupud.begin(), m_nupud.end(), [&nupud](auto el) { ++nupud[el->getTaht()]; });

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
        for (int i = 0; i < m_nupud.size(); i++) {
            if (m_nupud[i]->getTaht() == k.second->getTaht()) {
                m_nupud.erase(m_nupud.begin() + i);
            }
            char taht = k.second->getTaht();
            if ((taht >= 97 && taht <= 122 || taht == '#') && m_nupud[i]->getTaht() == '?')
                m_nupud.erase(m_nupud.begin() + i);
        }
    }
}

bool Kuna::kasTyhi() {
    return m_nupud.empty();
}

int Kuna::kunaNuppudePunktid() const {
    int punktid = 0;
    for (const auto &nupp: m_nupud)
        punktid += nupp->getPunktid();
    return punktid;
}
