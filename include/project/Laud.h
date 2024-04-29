//
// Created by Martin on 15.04.2024.
//

#ifndef SCRABBLE_PROJEKT_C__LAUD_H
#define SCRABBLE_PROJEKT_C__LAUD_H


#include <ostream>
#include <vector>
#include <set>
#include "Ruut.h"

using namespace std;
//testcomment

class Laud {
    vector<shared_ptr<Ruut>> m_mangulaud;
    static set<short> m_kahekordsedTahed;
    static set<short> m_kolmekordsedTahed;
    static set<short> m_kahekordsedSonad;
    static set<short> m_kolmekordsedSonad;
public:
    Laud();

    friend ostream &operator<<(ostream &os, const Laud &laud);
};


#endif //SCRABBLE_PROJEKT_C__LAUD_H
