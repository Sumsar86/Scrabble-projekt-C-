//
// Created by Martin on 15.04.2024.
//

#include <iostream>

#include "../include/project/Ruut.h"
//testcomment

Ruut::Ruut(short sonaKordaja, short taheKordaja) : m_nupp(nullptr), m_sonaKordaja(sonaKordaja),
                                                                      m_taheKordaja(taheKordaja) {};

ostream &operator<<(ostream &os, const Ruut &ruut) {
    if (!ruut.m_nupp){
        if (ruut.m_taheKordaja > 1) {
            os << ruut.m_taheKordaja;
            return os;
        }
        if (ruut.m_sonaKordaja > 1) {
            os << ruut.m_sonaKordaja;
            return os;
        }
        os << "_";
        return os;
    }
    os << ruut.m_nupp;
    return os;
}
