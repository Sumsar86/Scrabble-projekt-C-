//
// Created by Martin on 15.04.2024.
//

#ifndef SCRABBLE_PROJEKT_C_RUUT_H
#define SCRABBLE_PROJEKT_C_RUUT_H

#include <memory>
#include <ostream>
#include "string"
#include "Nupp.h"

using namespace std;

class Ruut {
    shared_ptr<Nupp> m_nupp;
    short m_sonaKordaja;
    short m_taheKordaja;
public:
    Ruut(short sonaKordaja, short taheKordaja);

    friend ostream &operator<<(ostream &os, const Ruut &ruut);
};


#endif //SCRABBLE_PROJEKT_C_RUUT_H
