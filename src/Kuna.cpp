#include "Kuna.h"

// Konstruktor, mis loob uue Küna, võttes kotist juhuslikult max_arv_nuppe arvu nuppe.
Kuna::Kuna(short max_arv_nuppe, const shared_ptr<Kott> &kott) : m_max_arv_nuppe(max_arv_nuppe), m_nupud({}) {
    for (int i = 0; i < max_arv_nuppe; i++)
        m_nupud.push_back(kott->getJuhuslikNupp());
}

// Küna ekraanile kuvamiseks
ostream &operator<<(ostream &os, const Kuna &kuna) {
    os << "nupud: ";
    for (const auto &it: kuna.m_nupud)
        os << *it << ", ";
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
        cerr << "\nSaad vahetada kuni 7 tähte!\n";
        return false;
    }
    if (kott->getNuppudeArv() < 7) {
        cerr << "\nKotis on alla 7 tähe.";
        return false;
    }

    vector<pair<shared_ptr<Nupp>, char>> nupud;
    for (const char &taht: tahed)
        nupud.emplace_back(kasSisaldabNuppu(taht), taht);

    bool vastus{true};
    for (int i = 0; i < nupud.size(); i++) {
        // Kui nuppu ei olnud künal
        if (nupud[i].first == nullptr) {
            cerr << "\nNupp ei ole künal! (" + string(1, nupud[i].second) + ")\n";
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

    if (!vastus)
        cerr << "\nKõiki nuppe ei õnnestunud välja vahetada!\n";
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
    map<char, int> nupud;
//    cout << "3\n";
    for_each(m_nupud.begin(), m_nupud.end(), [&nupud](auto el) { ++nupud[el->getTaht()]; });
//    cout << "4\n";
    for (const auto& k : kaik->getKaik()) {
//        cout << *k.second << " " << nupud[k.second->getTaht()] << " ";
        --nupud[k.second->getTaht()];
//        cout << nupud[k.second->getTaht()] << "\n";
    }
//    for_each(kaik->getKaik().begin(), kaik->getKaik().end(), [&nupud](auto el) { --nupud[el.second->getTaht()]; });
//    cout << "5\n";
    return !any_of(nupud.begin(), nupud.end(), [](auto el) { return el.second < 0; });
}

void Kuna::eemaldaNupud(const shared_ptr<Kaik> &kaik) {
    for (const auto& k: kaik->getKaik()) {
        for (int i = 0; i < m_nupud.size(); i++) {
            if (m_nupud[i]->getTaht() == k.second->getTaht()) {
                m_nupud.erase(m_nupud.begin() + i);
            }
        }
    }

}
