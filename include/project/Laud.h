#pragma once

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
    static map<char, int> m_tahePunktid;

    bool kontrolliPos(const shared_ptr<Kaik>& kaik);
    int kontrolliSonu(const shared_ptr<Kaik>& kaik); //return -1 kui pole korrektne käik, vastasel juhul return saadavad punktid
    bool kasEsimeneKaik();

    bool kasIndeksTyhi(int indeks);

    int leiaSonaAlgusReas(int indeks);

    int leiaSonaAlgusVeerus(int indeks);

    int leiaSonaLoppReas(int indeks);

    int leiaSonaLoppVeerus(int indeks);


public:
    Laud();
    Laud(vector<shared_ptr<Ruut>> mangulaud);
    Laud(string mangulaud); //sisestada 225-karakteriline string tähtedega laual õigetes kohtades. Ülejäänud kohtades peab olema "_".

    int kontrolli(const shared_ptr<Kaik>& kaik); //tagastab -1 kui pole korrektne käik, vastasel juhul tagastab saadavad punktid

    friend ostream &operator<<(ostream &os, const Laud &laud);
};
