#include <vector>
#include "Kaik.h"
#include <algorithm>
#include <iostream>

Kaik::Kaik(const map<int, shared_ptr<Nupp>> &mKaik) : m_kaik(mKaik) {}

// Kontrollib, kas kõik käigus käidud nupud asuvad ühel real
bool Kaik::yhesReas() {
    if (m_kaik.size() < 2)
        return true;
    for (auto it = m_kaik.begin(); it != m_kaik.end(); ++it) {
        if (it->first / 15 != (++it)->first / 15)
            return false;
        it++;
    }
    return true;
}

// Kontrollib, kas kõik käigus käidud nupud asuvad ühes veerus
bool Kaik::yhesVeerus() {
    if (m_kaik.size() < 2)
        return true;
    for (auto it = m_kaik.begin(); it != m_kaik.end(); ++it) {
        if (it->first % 15 != (++it)->first % 15)
            return false;
        it++;
    }
    return true;
}

// Tagastab käigu kõige ülemise ja vasakpoolse nupu indekis ehk vähima indeksiga nupu indeksi
int Kaik::esimeneIndeks() {
    return m_kaik.begin()->first;
}

// Tagastab suurima ehk viimase indeksi
int Kaik::viimaneIndeks() {
    return (--m_kaik.end())->first;
}

// Kontrollib, kas käidavas käigus on vastava indeksiga ruudule nupp asetatud
bool Kaik::kasIndeksOlemas(int indeks) {
    return any_of(m_kaik.begin(), m_kaik.end(), [indeks](const auto &el) {
        return el.first == indeks;
    });
//    for (const auto& el : m_kaik){
//        if (el.first == indeks)
//            return true;
//    }
//    return false;
}

// Tagastab viida käidud nuppude indeksite vektorile
shared_ptr<vector<int>> Kaik::getIndeksid() {
    shared_ptr<vector<int>> indeksid = make_shared<vector<int>>();
    for (const auto &el: m_kaik)
        indeksid->push_back(el.first);
    return indeksid;
}

// Tagastab viida Nupule, mille indeks sisestati. Kui sellel indeksil nuppu ei leidu, siis tagastatakse nullptr.
shared_ptr<Nupp> Kaik::getNupp(int indeks) {
    vector<int> indeksid = *getIndeksid();
    if (find(indeksid.begin(), indeksid.end(), indeks) != indeksid.end())
        return m_kaik[indeks];

    cerr << "Viga! Ei leidnud nuppu: indeks = " << indeks << '\n';
    return nullptr;
}

