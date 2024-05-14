#include <iostream>
#include "Kuna.h"

// Konstruktor, mis loob uue Küna, võttes kotist juhuslikult maxNuppe arvu nuppe.
Kuna::Kuna(short maxNuppe, const shared_ptr<Kott> &kott) : m_maxNuppe(maxNuppe), m_nupud({}) {
    for (int i = 0; i < maxNuppe; i++)
        m_nupud.push_back(kott->getJuhuslikNupp());
}

// Küna ekraanile kuvamiseks
ostream &operator<<(ostream &os, const Kuna &kuna) {
    os << "maxNuppe: " << kuna.m_maxNuppe << ", nupud: ";
    for (const auto &it: kuna.m_nupud)
        os << *it << ", ";
    return os;
}

// Tagastab viida nupule, kui see on künal, vastasel juhul tagastab nullptr.
shared_ptr<Nupp> Kuna::kas_sisaldab_nuppu(const char &taht) {
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
    if (kott->getNuppudeArv() < 7 || tahed.size() > 7)
        return false;

    vector<shared_ptr<Nupp>> nupud;
    for (const char &taht: tahed)
        nupud.push_back(kas_sisaldab_nuppu(taht));

    bool vastus{true};
    for (int i = 0; i < nupud.size(); i++) {
        // Kui nuppu ei olnud künal
        if (nupud[i] == nullptr) {
            cerr << "Nupp ei ole künal!\n";
            vastus = false;
            continue;
        }
        for (int j = 0; j < m_nupud.size(); j++)
            if (m_nupud[j]->getTaht() == tahed[i]) {
                m_nupud.erase(m_nupud.begin() + j);
                break;
            }
        m_nupud.push_back(kott->vahetaNupp(nupud[i]));
    }

    if (!vastus)
        cerr << "Kõiki nuppe ei õnnestunud välja vahetada!\n";
    // Kas kõik tähed said vahetatud.
    return vastus;
}