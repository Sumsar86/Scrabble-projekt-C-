#pragma once

#include "Mangija.h"

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

    Mang(const shared_ptr<Kott> &kott);

    void jargmineKaik(const shared_ptr<Mangija> &mangija);

    shared_ptr<Mangija> jargmineMangija();

    bool kasMangLabi(const shared_ptr<Mangija> &mangija);

    void lopetaMang(const shared_ptr<Mangija> &mangija);

    int mangijateArv();

private:
    static string kysiMangijateArv();

    void kysiMangijateNimed(int mangijate_arv);

    static string kysiKoordinaadid();

    static string kysiSuund();

    static string kysiSona();

    bool kaiSona(const shared_ptr<Mangija> &mangija, bool &oige_vastus);

    static void jataVahele(const shared_ptr<Mangija> &mangija, bool &oige_vastus);

    static bool vahetaTahti(const shared_ptr<Mangija> &mangija, bool &oige_vastus);

    void trykiTulemused();
};
