#pragma once

#include <memory>
#include <iostream>
#include "Mangija.h"
//#include "Laud.h"

using namespace std;

class Mang {
private:
    shared_ptr<Kott> m_kott;
    map<int, shared_ptr<Mangija>> m_mangijad;
    Laud m_laud;
    int m_praeguse_mangija_id;
    int m_vahele_jaetud_kaikude_arv;

public:
    Mang();

    void jargmineKaik();

private:
    shared_ptr<Mangija> jargmineMangija();
    static string kysiMangijateArv();
    void kysiMangijateNimed(int mangijate_arv);
    static string kysiKoordinaadid();
    static string kysiSuund();
    static string kysiSona();
    bool kaiSona(const shared_ptr<Mangija>& mangija, bool &oige_vastus);
    void jataVahele(const shared_ptr<Mangija>& mangija, bool &oige_vastus);
    void vahetaTahti(const shared_ptr<Mangija>& mangija, bool &oige_vastus);
};
