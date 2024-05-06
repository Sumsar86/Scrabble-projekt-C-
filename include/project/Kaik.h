//
// Created by Martin on 06.05.2024.
//

#ifndef SCRABBLE_PROJEKT_C__KAIK_H
#define SCRABBLE_PROJEKT_C__KAIK_H


#include <map>
#include "Nupp.h"

class Kaik {
private:
    map<int,Nupp> m_kaik;
public:
    explicit Kaik(const map<int, Nupp> &mKaik);
};


#endif //SCRABBLE_PROJEKT_C__KAIK_H
