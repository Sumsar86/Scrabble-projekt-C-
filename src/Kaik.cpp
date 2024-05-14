//
// Created by Martin on 06.05.2024.
//

#include <vector>
#include "Kaik.h"
#include <algorithm>
#include <iostream>

Kaik::Kaik(const map<int, shared_ptr<Nupp>> &mKaik) : m_kaik(mKaik) {
    if (any_of(mKaik.begin(),mKaik.end(),[](const auto &el){return (el.first < 0 || el.first > 224);})){
        throw invalid_argument("Indeks mängulaualt väljas!\n");
    }
}

bool Kaik::yhesReas() {
    if (m_kaik.size() < 2)
        return true;
    for (auto it = m_kaik.begin(); it != m_kaik.end(); ++it){
        if (it->first / 15 != (++it)->first / 15){
            return false;
        }
        it++;
    }
    return true;
}

bool Kaik::yhesVeerus() {
    if (m_kaik.size() < 2)
        return true;
    for (auto it = m_kaik.begin(); it != m_kaik.end(); ++it){
        if (it->first % 15 != (++it)->first % 15)
            return false;
        it++;
    }
    return true;
}

int Kaik::esimeneIndeks() {
    return m_kaik.begin()->first;
}
int Kaik::viimaneIndeks() {
    return (--m_kaik.end())->first;
}

bool Kaik::kasIndeksOlemas(int indeks) {
    for (const auto& el : m_kaik){
        if (el.first == indeks)
            return true;
    }
    return false;
}

shared_ptr<vector<int>> Kaik::getIndeksid() {
    shared_ptr<vector<int>> indeksid = make_shared<vector<int>>();
    for (auto el : m_kaik)
        indeksid->push_back(el.first);
    return indeksid;
}

shared_ptr<Nupp> Kaik::getNupp(int indeks){
    vector<int> indeksid = *getIndeksid();
    if (find(indeksid.begin(), indeksid.end(), indeks) != indeksid.end()) {
        return m_kaik[indeks];
    }
    cerr << "Viga! Ei leidnud nuppu: indeks = " << indeks << '\n';
    return nullptr;
}

