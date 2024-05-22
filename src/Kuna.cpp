#include <iostream>
#include "Kuna.h"

// Konstruktor, mis loob uue Küna, võttes kotist juhuslikult max_arv_nuppe arvu nuppe.
Kuna::Kuna(short max_arv_nuppe, const shared_ptr<Kott> &kott) : m_max_arv_nuppe(max_arv_nuppe), m_nupud({}) {
    for (int i = 0; i < max_arv_nuppe; i++)
        m_nupud.push_back(kott->getJuhuslikNupp());
}

// Küna ekraanile kuvamiseks
ostream &operator<<(ostream &os, const Kuna &kuna) {
    os << "max arv nuppe: " << kuna.m_max_arv_nuppe << ", nupud: ";
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
    if (kott->getNuppudeArv() < 7 || tahed.size() > 7)
        return false;

    vector<shared_ptr<Nupp>> nupud;
    for (const char &taht: tahed)
        nupud.push_back(kasSisaldabNuppu(taht));

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