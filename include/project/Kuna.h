// Created by Martin on 28.04.2024.

#ifndef SCRABBLE_PROJEKT_C__KUNA_H
#define SCRABBLE_PROJEKT_C__KUNA_H

#include <vector>
#include "Nupp.h"

class Kuna {
private:
    short mangija; //mitmenda mängija oma on
    vector<Nupp> nupud;
public:
    Kuna(short mangija, const vector<Nupp> &nupud);
};


#endif //SCRABBLE_PROJEKT_C__KUNA_H
