// Created by Martin on 28.04.2024.

#ifndef SCRABBLE_PROJEKT_C__KOTT_H
#define SCRABBLE_PROJEKT_C__KOTT_H

#include "Nupp.h"
#include <map>
#include <ostream>
#include <utility>
#include <random>
#include <chrono>

using namespace std;

class Kott {
private:
    static map<shared_ptr<Nupp>, int> m_vaike_kott;

    map<shared_ptr<Nupp>, int> m_nupud;
    int m_nuppude_arv;

    mt19937 m_rng;
    uniform_int_distribution<std::mt19937::result_type> m_juhuslik_arv;

private:
    void loo_juhuarvu_generaator();
    void leia_nuppude_arv();

public:
    explicit Kott(map<shared_ptr<Nupp>, int> nupud);

    Kott();

    shared_ptr<Nupp> getNupp();

    shared_ptr<Nupp> vahetaNupp(const shared_ptr<Nupp>& vana_nupp);

    bool kas_on_tuhi() const;
    int getNuppudeArv() const;

    friend ostream &operator<<(ostream &os, const Kott &kott);

};


#endif //SCRABBLE_PROJEKT_C__KOTT_H
