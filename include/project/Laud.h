#pragma once

#include <ostream>
#include <vector>
#include <set>
#include "Ruut.h"
#include "Kaik.h"

using namespace std;

class Laud {
    vector<shared_ptr<Ruut>> m_mangulaud;
    static set<short> m_kahekordsed_tahed;
    static set<short> m_kolmekordsed_tahed;
    static set<short> m_kahekordsed_sonad;
    static set<short> m_kolmekordsed_sonad;
    static map<char, int> m_tahe_punktid;

    bool kontrolliPos(const shared_ptr<Kaik> &kaik);

    int kontrolliSonu(const shared_ptr<Kaik> &kaik); //return -1 kui pole korrektne käik, vastasel juhul return saadavad punktid

    bool kasEsimeneKaik();

    bool kasIndeksTyhi(int indeks);

    int leiaSonaAlgusReas(int indeks);

    int leiaSonaAlgusVeerus(int indeks);

    int leiaSonaLoppReas(int indeks);

    int leiaSonaLoppVeerus(int indeks);


public:
    Laud();

    explicit Laud(vector<shared_ptr<Ruut>> mangulaud);

    explicit Laud(string mangulaud); //sisestada 225-karakteriline string tähtedega laual õigetes kohtades. Ülejäänud kohtades peab olema "_".

    int kontrolli(const shared_ptr<Kaik> &kaik); //tagastab -1 kui pole korrektne käik, vastasel juhul tagastab saadavad punktid

    friend ostream &operator<<(ostream &os, const Laud &laud);
};
