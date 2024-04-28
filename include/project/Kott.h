// Created by Martin on 28.04.2024.

#ifndef SCRABBLE_PROJEKT_C__KOTT_H
#define SCRABBLE_PROJEKT_C__KOTT_H

#include "Nupp.h"
#include <map>

using namespace std;

class Kott {
private:
    map<Nupp, int> m_nupud;
public:
    Kott(map<Nupp, int> mNupud);
    Kott();
};


#endif //SCRABBLE_PROJEKT_C__KOTT_H
