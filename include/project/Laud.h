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

    bool kontrolliPos(const shared_ptr<Kaik>& kaik);

    bool kontrolliSonu(const shared_ptr<Kaik>& kaik);

    bool kasEsimeneKaik();

    bool kasIndeksTyhi(int indeks);

    int leiaSonaAlgusReas(int indeks);

    int leiaSonaAlgusVeerus(int indeks);

    int leiaSonaLoppReas(int indeks);

    int leiaSonaLoppVeerus(int indeks);


public:
    Laud();

    bool kontrolli(const shared_ptr<Kaik>& kaik);

    friend ostream &operator<<(ostream &os, const Laud &laud);
};
