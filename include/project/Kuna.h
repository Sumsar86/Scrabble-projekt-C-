#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <ostream>
//#include "Nupp.h"
#include "Kott.h"
#include "Laud.h"

class Kuna {
private:
    short m_max_arv_nuppe; // maksimaalne lubatud nuppude arv künas
    vector<shared_ptr<Nupp>> m_nupud;

public:
    Kuna(short max_arv_nuppe, const shared_ptr<Kott> &kott);

    shared_ptr<Nupp> kasSisaldabNuppu(const char &taht);

    bool kasSisaldabKaiku(const shared_ptr<Kaik> &kaik);

    void eemaldaNupud(const shared_ptr<Kaik> &kaik);

    bool vahetaNupp(vector<char> &tahed, shared_ptr<Kott> &kott);

    bool kasTyhi();

    void lisaNupp(const shared_ptr<Nupp> &nupp);

    friend ostream &operator<<(ostream &os, const Kuna &kuna);

    int mituNuppuKunal() const;

    short getMaxArvNuppeKunal() const;

    int kunaNuppudePunktid() const;
};
