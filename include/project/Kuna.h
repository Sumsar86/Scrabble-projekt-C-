#pragma once

#include <vector>
#include <memory>
#include <ostream>
#include "Nupp.h"
#include "Kott.h"

class Kuna {
private:
    short m_max_arv_nuppe; // maksimaalne lubatud nuppude arv künas
    vector<shared_ptr<Nupp>> m_nupud;
public:
    Kuna(short max_arv_nuppe, const shared_ptr<Kott> &kott);

    shared_ptr<Nupp> kasSisaldabNuppu(const char &taht);

    bool vahetaNupp(vector<char> &tahed, shared_ptr<Kott> &kott);

    friend ostream &operator<<(ostream &os, const Kuna &kuna);
};
