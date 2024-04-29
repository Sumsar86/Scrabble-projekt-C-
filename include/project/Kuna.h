// Created by Martin on 28.04.2024.

#ifndef SCRABBLE_PROJEKT_C__KUNA_H
#define SCRABBLE_PROJEKT_C__KUNA_H

#include <vector>
#include "Nupp.h"

class Kuna {
private:
    short m_maxNuppe; //mitmenda mängija oma on
    vector<Nupp> m_nupud;
public:
    Kuna(short maxNuppe, const vector<Nupp> &nupud);
};


#endif //SCRABBLE_PROJEKT_C__KUNA_H
