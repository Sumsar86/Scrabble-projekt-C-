//
// Created by rasmu on 29.04.2024.
//

#include "Mangija.h"

Mangija::Mangija(shared_ptr<Kott> &kott) : mp_kott(kott), m_kuna(Kuna(7, kott)), m_punktid(0) {}

ostream &operator<<(ostream &os, const Mangija &mangija) {
    os << "Mängija punktid: " << mangija.m_punktid << ", küna: " << mangija.m_kuna;
    return os;
}

bool Mangija::vahetaNupud(vector<char> &tahed) {
    return m_kuna.vahetaNupp(tahed, mp_kott);
}


