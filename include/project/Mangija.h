//
// Created by rasmu on 29.04.2024.
//

#ifndef SCRABBLE_PROJEKT_C__MANGIJA_H
#define SCRABBLE_PROJEKT_C__MANGIJA_H

#include <memory>
#include <utility>
#include <ostream>
#include "Kuna.h"
#include "Kott.h"

class Mangija {
private:
    std::shared_ptr<Kott> mp_kott;
    Kuna m_kuna;
    int m_punktid;

public:
    explicit Mangija(shared_ptr<Kott> &kott);

    bool vahetaNupud(vector<char> &tahed);

    friend ostream &operator<<(ostream &os, const Mangija &mangija);
};


#endif //SCRABBLE_PROJEKT_C__MANGIJA_H
