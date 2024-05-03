// Created by Martin on 28.04.2024.

#ifndef SCRABBLE_PROJEKT_C__KUNA_H
#define SCRABBLE_PROJEKT_C__KUNA_H

#include <vector>
#include <memory>
#include <ostream>
#include "Nupp.h"
#include "Kott.h"

class Kuna {
private:
    short m_maxNuppe; // maksimaalne lubatud nuppude arv künas
    vector<shared_ptr<Nupp>> m_nupud;
public:
    Kuna(short maxNuppe, const shared_ptr<Kott> &kott);

    shared_ptr<Nupp> kas_sisaldab_nuppu(const string &taht);

    bool vahetaNupp(vector<string> &tahed, shared_ptr<Kott> &kott);

    friend ostream &operator<<(ostream &os, const Kuna &kuna);
};


#endif //SCRABBLE_PROJEKT_C__KUNA_H
