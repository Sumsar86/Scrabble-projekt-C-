#include <iostream>
#include "Ruut.h"
#include <utility>

// Ruudu konstruktor
Ruut::Ruut(short sonaKordaja, short taheKordaja) : m_nupp(nullptr), m_sonaKordaja(sonaKordaja), m_taheKordaja(taheKordaja) {};

Ruut::Ruut(shared_ptr<Nupp> nupp) : m_nupp(std::move(nupp)), m_sonaKordaja(1), m_taheKordaja(1){};

// Ruudu kuvamiseks ekraanil
ostream &operator<<(ostream &os, const Ruut &ruut) {
    // Kui ruudule ei ole veel nuppu käidud
    if (!ruut.m_nupp){
        // Kui ruudul on tähekordaja
        if (ruut.m_taheKordaja > 1) {
            os << ruut.m_taheKordaja;
            return os;
        }
        // Kui ruudul on sõnakordaja
        if (ruut.m_sonaKordaja > 1) {
            os << ruut.m_sonaKordaja;
            return os;
        }
        // Kui ruut on täiesti tühi (ehk kõik kordajad on ühed)
        os << "_";
        return os;
    }
    // Kui ruudul on nupp, siis kordajaid ei kuvata
    os << *(ruut.getNupp());
    return os;
}

// Kas ruudule on nupp asetatud
bool Ruut::kasTyhi() {
    return !m_nupp;
}

// Tagastab enale asetatud nupu
const shared_ptr<Nupp> &Ruut::getNupp() const {
    if (!m_nupp)
        cerr << "Ruudul pole nuppu! Tagastan nullptr.\n";
    return m_nupp;
}
