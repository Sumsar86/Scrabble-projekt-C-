#include "Mangija.h"

// Mängija konstruktor, küna suurus on 7
Mangija::Mangija(shared_ptr<Kott> &kott) : mp_kott(kott), m_kuna(Kuna(7, kott)), m_punktid(0) {}

// Mängija ekraanile kuvamiseks
ostream &operator<<(ostream &os, const Mangija &mangija) {
    os << "Mängija punktid: " << mangija.m_punktid << ", küna: " << mangija.m_kuna;
    return os;
}

// Mängija nuppude vahetamiseks
bool Mangija::vahetaNupud(vector<char> &tahed) {
    return m_kuna.vahetaNupp(tahed, mp_kott);
}


