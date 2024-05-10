//
// Created by Martin on 15.04.2024.
//

#ifndef SCRABBLE_PROJEKT_C__LAUD_H
#define SCRABBLE_PROJEKT_C__LAUD_H


#include <ostream>
#include <vector>
#include <set>
#include "Ruut.h"
#include "Kaik.h"

using namespace std;

class Laud {
    vector<shared_ptr<Ruut>> m_mangulaud;
    static set<short> m_kahekordsedTahed;
    static set<short> m_kolmekordsedTahed;
    static set<short> m_kahekordsedSonad;
    static set<short> m_kolmekordsedSonad;

    bool kontrolliPos(shared_ptr<Kaik> kaik);
    bool kontrolliSonu(shared_ptr<Kaik> kaik);
    bool kasEsimeneKaik();
    bool kasIndeksTyhi(int indeks);

    int leiaSonaAlgusReas(int indeks);
    int leiaSonaAlgusVeerus(int indeks);


public:
    Laud();

    bool kontrolli(shared_ptr<Kaik> kaik);

    friend ostream &operator<<(ostream &os, const Laud &laud);
};


#endif //SCRABBLE_PROJEKT_C__LAUD_H
