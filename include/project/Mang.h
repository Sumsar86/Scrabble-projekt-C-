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
    Mang() : m_kott(make_shared<Kott>()),
             m_laud(Laud()),
             m_praeguse_mangija_id(0),
             m_vahele_jaetud_kaikude_arv(0) {
        string mangijate_arv;
        while (true) {
            try {
                cout << "Sisesta mängijate arv: ";
                getline(cin, mangijate_arv);
                if (stoi(mangijate_arv) < 1 || stoi(mangijate_arv) > 4)
                    throw invalid_argument("Arv ei sobi!");
                break;
            } catch (exception e) {
                cerr << "\nSisesta täisarv vahemikus 1--4!";
                continue;
            }
        }
        string nimi{};
        for (int i = 0; i < stoi(mangijate_arv); i++) {
            cout << "Sisesta mängija nimi: ";
            getline(cin, nimi);
            m_mangijad[i] = make_shared<Mangija>(m_kott, nimi);
        }
    }

    void jargmineKaik() {
        shared_ptr<Mangija> m = jargmineMangija();

        cout << m_laud << "\n";

        cout << *m << "\n";

        bool oige_vastus = false;
        string vastus{};
        string koordinaadid{};
        string suund{};
        shared_ptr<Kaik> kaik;
        int tulemus;
        vector<char> tahed{};

        while (true) {
            cout << "Sinu kord: " << m->getNimi()
                 << "\nKas sa soovid käia sõna (S), käigu vahele jätta (J) või künalt tähti vahetada (V)? ";
            getline(cin, vastus);
            switch (toupper(vastus.c_str()[0])) {
                case 'S':
                    while (true) {
                        cout << "Sisesta esimese tähe koordinaadid (A1): ";
                        getline(cin, koordinaadid);
                        if (toupper(koordinaadid[0]) < 'A' ||
                            toupper(koordinaadid[0]) > 'O' ||
                            koordinaadid[1] - 48 < 0 ||
                            koordinaadid[1] - 48 > 9 ||
                            koordinaadid.size() > 2 &&
                            koordinaadid[1] - 48 != 1 &&
                            (koordinaadid[2] - 48 < 0 ||
                             koordinaadid[2] - 48 > 5)) {
                            cerr << "\nKoordinaat on vale!\n";
                            continue;
                        }
                        break;
                    }

                    while (true) {
                        cout << "Sisesta suund (alla - A, paremale - P): ";
                        getline(cin, suund);
                        if (suund != "A" && suund != "P" &&
                            suund != "a" && suund != "p") {
                            cerr << "\nSuund on vale!\n";
                            continue;
                        }
                        break;
                    }

                    cout
                            << "Sisesta käidav sõna, kui see ristub laual oleva sõnaga, märgi laual juba olevad tähed tärniga (*): ";
                    getline(cin, vastus);

                    if (vastus.empty())
                        break;

//                    cout << "1\n";
                    try {
                        kaik = make_shared<Kaik>(vastus, koordinaadid, suund);
                    } catch (const invalid_argument &e) {
                        cerr << "\nSõna positsioon ei ole korrektne!\n";
                        continue;
                    }
//                    cout << "2\n";

                    if (!m->kasNupudKunal(kaik)) {
                        cerr << "\nKõiki nuppe pole künal!\n";
                        continue;
                    }
//                    cout << "3\n";
                    cout << *kaik;

                    tulemus = m_laud.kontrolli(kaik);
                    if (tulemus < 0) {
                        cerr << "\nSelle sõna paigutus on vale või seda sõna pole sõnastikus!\n";
                        continue;
                    }

                    cout << "Sinu käidud sõna (" << vastus << ") eest saadud punktid: " << tulemus << ".\n";

                    m->lisaPunktid(tulemus);

                    m_laud.lisaSonaLauale(kaik);

                    m->eemaldaNupud(kaik);

                    m->taidaKuna();

                    cout << m_laud << "\n";
                    cout << "Uus küna: " << *m->getKuna() << "\n";

                    m_vahele_jaetud_kaikude_arv = 0;
                    oige_vastus = true;
                    break;
                case 'J':
                    // kui kõik mängijad on kaks korda järjest vahele jätnud, saab mäng läbi ehk mängijate arv * 2 käiku
                    cout << m->getNimi() << ", jätsid oma käigu vahele.\n";
                    m_vahele_jaetud_kaikude_arv++;
                    oige_vastus = true;
                    break;
                case 'V':
                    cout << "Sisesta vahetatavad tähed kokku kirjutatuna: ";
                    getline(cin, vastus);
                    for (char taht: vastus)
                        tahed.push_back(toupper(taht));

                    if (!m->vahetaNupud(tahed)) {
                        tahed.clear();
                        cerr << "\nNuppe ei õnnestunud vahetada.\n";
                        break;
                    }

                    tahed.clear();
                    cout << "Uus küna: " << *m->getKuna() << "\n";

                    m_vahele_jaetud_kaikude_arv = 0;
                    oige_vastus = true;
                    break;
                default:
                    cerr << "\nVale sisend!\n";
            }
            if (oige_vastus)
                break;
        }
    }

private:
    shared_ptr<Mangija> jargmineMangija() {
        return m_mangijad[m_praeguse_mangija_id++ % m_mangijad.size()];
    }
};
