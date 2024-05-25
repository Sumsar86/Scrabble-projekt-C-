#include "Laud.h"

// Laua konstruktor, mis loob mängualguse laua ehk lisab sinna õigete kordajatega tühjad ruudud
Laud::Laud() {
    for (short i{0}; i < 225; i++) {
        if (KAHEKORDSED_TAHED.contains(i)) {
            m_mangulaud.push_back(make_shared<Ruut>(1, 2));
            continue;
        }
        if (KOLMEKORDSED_TAHED.contains(i)) {
            m_mangulaud.push_back(make_shared<Ruut>(1, 3));
            continue;
        }
        if (KAHEKORDSED_SONAD.contains(i)) {
            m_mangulaud.push_back(make_shared<Ruut>(2, 1));
            continue;
        }
        if (KOLMEKORDSED_SONAD.contains(i)) {
            m_mangulaud.push_back(make_shared<Ruut>(3, 1));
            continue;
        }
        m_mangulaud.push_back(make_shared<Ruut>(1, 1));
    }
}

// Laua konstruktor, mis võtab sisendiks olemasolevate ruutudega vektori
Laud::Laud(vector<shared_ptr<Ruut>> mangulaud) {
    m_mangulaud = std::move(mangulaud);
}

// Laua konstruktor, mis võtab aluseks sõne ja loob selle järgi uue laua
Laud::Laud(string mangulaud) {
    if (mangulaud.size() != 225)
        throw invalid_argument("Stringi pikkus konstruktoris peab olema täpselt 225 ühikut!\n");
    for (int i{0}; i < 225; i++) {
        if (mangulaud[i] != '_')
            m_mangulaud.push_back(make_shared<Ruut>(make_shared<Nupp>(mangulaud[i], TAHE_PUNKTID[mangulaud[i]])));
        else if (KAHEKORDSED_TAHED.contains(i)) {
            m_mangulaud.push_back(make_shared<Ruut>(1, 2));
            continue;
        } else if (KOLMEKORDSED_TAHED.contains(i)) {
            m_mangulaud.push_back(make_shared<Ruut>(1, 3));
            continue;
        } else if (KAHEKORDSED_SONAD.contains(i)) {
            m_mangulaud.push_back(make_shared<Ruut>(2, 1));
            continue;
        } else if (KOLMEKORDSED_SONAD.contains(i)) {
            m_mangulaud.push_back(make_shared<Ruut>(3, 1));
            continue;
        } else m_mangulaud.push_back(make_shared<Ruut>(1, 1));
    }

}

// Kas praegu on esimene käik
bool Laud::kasEsimeneKaik() {
    for (int i{0}; i < m_mangulaud.size(); i++) {
        if (!kasIndeksTyhi(i))
            return false;
    }
    return true;
}

// Kas mängulaual on kohal (indeksil) mõni käidud nupp
bool Laud::kasIndeksTyhi(int indeks) {
    return m_mangulaud[indeks]->kasTyhi();
}

// Leiab esimese reas eelnevatega ühendatud tähe asukoha laual
int Laud::leiaSonaAlgusReas(int indeks) {
    while (indeks % 15 > 0) {
        indeks--;
        if (kasIndeksTyhi(indeks))
            return ++indeks;
    }
    return indeks;
}

// Leiab viimase reas eelnevatega ühendatud tähe asukoha laual
int Laud::leiaSonaLoppReas(int indeks) {
    while (indeks % 15 < 14) {
        indeks++;
        if (kasIndeksTyhi(indeks))
            return --indeks;
    }
    return indeks;
}

// Leiab esimese veerus eelnevatega ühendatud tähe asukoha laual
int Laud::leiaSonaAlgusVeerus(int indeks) {
    while (indeks / 15 > 0) {
        indeks -= 15;
        if (kasIndeksTyhi(indeks))
            return indeks + 15;
    }
    return indeks;
}

// Leiab viimase veerus eelnevatega ühendatud tähe asukoha laual
int Laud::leiaSonaLoppVeerus(int indeks) {
    while (indeks / 15 < 14) {
        indeks += 15;
        if (kasIndeksTyhi(indeks))
            return indeks - 15;
    }
    return indeks;
}

// Laua ekraanile kuvamiseks
ostream &operator<<(ostream &os, const Laud &laud) {
    os << "\n";
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i{0}; i < 15; i++) {
        if (i < 9)
            os << ' ';
//        SetConsoleTextAttribute(hConsole, static_cast<WORD>(i % 16));
        os << i + 1 << " | ";
//        SetConsoleTextAttribute(hConsole, static_cast<WORD>(15));

        for (int j{0}; j < 15; j++) {
            short index = i * 15 + j;
            os << *laud.m_mangulaud.at(index) << ' ';
        }
        os << '\n';
    }
    os << "   +---------------------------------------------\n";
    os << "      A  B  C  D  E  F  G  H  I  J  K  L  M  N  O\n";
    return os << "\n";
}

// Kutsub käigu kontrollimise funktsioonid välja ja tagastab sõna eest saadud punktid.
// Kui sõna pole olemas tagastab -1.
int Laud::kontrolli(const shared_ptr<Kaik> &kaik) {
    if (kontrolliPos(kaik)) return kontrolliSonu(kaik);
    return -1;
}

// Kontrollib, kas käidav käik asetseb laual vastavalt reeglitele
bool Laud::kontrolliPos(const shared_ptr<Kaik> &kaik) {
    bool onReas = kaik->yhesReas();
    bool onVeerus = kaik->yhesVeerus();
    cout << "\nrida: " << onReas << ", veerg: " << onVeerus << "\n";
    int indeks, viimane;
    // Käik pole sirges reas ega veerus
    if (!(onReas || onVeerus)) {
        cerr << "\nEi ole reas ega veerus!";
        return false;
    }

    // Käik on reas
    if (onReas) {
        indeks = kaik->esimeneIndeks();
        viimane = kaik->viimaneIndeks();
        // Kuni indeks pole viimase täheni jõudnud
        while (indeks != viimane) {
            // Kui nupp käiakse kohale kus laual on nupp juba olemas või vaadeldaval kohal pole nuppu ega käida ka nuppu
            if (!kasIndeksTyhi(indeks) && kaik->kasIndeksOlemas(indeks) ||
                kasIndeksTyhi(indeks) && !(kaik->kasIndeksOlemas(indeks)))
                return false;
            indeks++; // järgmine veerg
        }
    } else { // Käik on veerus
        indeks = kaik->esimeneIndeks();
        viimane = kaik->viimaneIndeks();
        // Kuni indeks pole viimase täheni jõudnud
        while (indeks != viimane) {
            // Kui nupp käiakse kohale kus laual on nupp juba olemas või vaadeldaval kohal pole nuppu ega käida ka nuppu
            if (!kasIndeksTyhi(indeks) && kaik->kasIndeksOlemas(indeks) ||
                kasIndeksTyhi(indeks) && !(kaik->kasIndeksOlemas(indeks)))
                return false;
            indeks += 15; // järgmine rida
        }
    }

    // Kui on mängu esimene käik
    if (kasEsimeneKaik()) {
        // Kui käigus pole nuppu, mis asetatakse laua keskmisele ruudule
        if (!(kaik->kasIndeksOlemas(m_mangulaud.size() / 2))) {
            cerr << "\nEsimene käik tuleb käia läbi keskmise ruudu!";
            return false;
        }
        return true;
    }

    // Kontrollib kas mõni käidav täht puutub eelnevalt käidud tähtedega kokku
    vector<int> indeksid = *kaik->getIndeksid();
    return any_of(indeksid.begin(), indeksid.end(), [this](const int &i) {
        return !kasIndeksTyhi(i - 1) ||
               !kasIndeksTyhi(i + 1) ||
               !kasIndeksTyhi(i - 15) ||
               !kasIndeksTyhi(i + 15);
    });
//    for (int i: *kaik->getIndeksid()) {
//        if (!kasIndeksTyhi(i - 1))
//            return true;
//        if (!kasIndeksTyhi(i + 1))
//            return true;
//        if (!kasIndeksTyhi(i - 15))
//            return true;
//        if (!kasIndeksTyhi(i + 15))
//            return true;
//    }
//    return false;
}

//tagastab -1, kui pole korrektne sõna, tagastab korrektse sõna puhul selle punktid.
int Laud::kontrolliSonu(const shared_ptr<Kaik> &kaik) { //eeldame, et käik on korrektselt positsioneeritud
    bool onReas = kaik->yhesReas();
    int praegune;
    string sona{}, teineSona{};
    int punktid{0}; //see on risti olevate sõnade eest saadav koguskoor + bingoSkoor
    int sonaKordaja{1}; //mitmega peamine sõna korrutatakse
    int sonaPunktid{0}; //peamise sõna punktid ilma sõna x N boonus(t)eta.
    int teiseSonaPunktid;
    int teiseSonaKordaja; //mitmega risti olev sõna korrutatakse

    // Kui kõik nupud (künasse mahub 7 nuppu) korraga ära käia saab boonuseks 50 punkti
    if (kaik->getIndeksid()->size() >= 7)
        punktid += 50;

    // Kui sõna käidi reas
    if (onReas) {
        // Käidava sõna esimese tähe asukoht (indeks) reas
        praegune = leiaSonaAlgusReas(kaik->esimeneIndeks());

        // Liigume reas vasakule, kuni jõuame rea algusesse või tuleb tühi ruut
        while ((praegune - 1) % 15 + 1 != 0 && kaik->kasIndeksOlemas(praegune - 1)) //leiab sõna alguse reas
            praegune -= 1;

        // Liigume reas paremale ja vaatame, kas kõik tekkinud sõnad on päriselt olemas
        do {
            // Kui leiame laualt paremalt tähe lisame selle oma sõnale otsa
            if (!kasIndeksTyhi(praegune)) {
                sona += m_mangulaud[praegune]->getNupp()->getTaht();
                sonaPunktid += m_mangulaud[praegune]->getNupp()->getPunktid();
            }
                // Kui leiame tähe hoopis käidavast sõnast mitte laualt (sest see on sealt tühi)
            else if (kaik->kasIndeksOlemas(praegune)) {
                // Veerus tekkiv sõna
                teineSona = "";
                teiseSonaPunktid = 0;
                teiseSonaKordaja = 1;
                // Leiame veerus tekkiva sõna kõige ülemise tähe indeksi
                int ajutine = leiaSonaAlgusVeerus(praegune);
                // Kui ülevalt alla liikudes on laual juba täht või on käidav täht
                while (!kasIndeksTyhi(ajutine) || ajutine == praegune) {
                    // Kui täht on juba laual olemas või on see meie käidav täht lisame selle veerus tekkivale sõnale otsa
                    // Lisaks liidame tähe eest saadavad punktid
                    if (ajutine != praegune) {
                        teineSona += m_mangulaud[ajutine]->getNupp()->getTaht();
                        teiseSonaPunktid += m_mangulaud[ajutine]->getNupp()->getPunktid();
                    } else {
                        // Kui on praegu käidud nupp, arvestame ka erinevaid ruutude kordajaid
                        teineSona += kaik->getNupp(ajutine)->getTaht();
                        if (KAHEKORDSED_TAHED.contains(ajutine))
                            teiseSonaPunktid += 2 * (kaik->getNupp(ajutine)->getPunktid());
                        else if (KOLMEKORDSED_TAHED.contains(ajutine))
                            teiseSonaPunktid += 3 * (kaik->getNupp(ajutine)->getPunktid());
                        else if (KAHEKORDSED_SONAD.contains(ajutine)) {
                            teiseSonaKordaja = 2;
                            teiseSonaPunktid += kaik->getNupp(ajutine)->getPunktid();
                        } else if (KOLMEKORDSED_SONAD.contains(ajutine)) {
                            teiseSonaKordaja = 3;
                            teiseSonaPunktid += kaik->getNupp(ajutine)->getPunktid();
                        } else teiseSonaPunktid += kaik->getNupp(ajutine)->getPunktid();
                    }
                    // Kas oleme juba viimases reas ehk indeks > 209 = 255 - 15
                    if (ajutine > 209) // kontroll, et oleme viimases reas
                        break;
                    // Järgmine rida
                    ajutine += 15;
                }
                // Kui vertikaalset sõna ei ole olemas
                if (teineSona.size() >= 2 && !(Dawg::kasSona(teineSona)))
                    return -1;
                if (teineSona.size() >= 2 && Dawg::kasSona(teineSona)) punktid += teiseSonaKordaja * teiseSonaPunktid;
                // Lisame käidud tähe sõnale otsa
                sona += kaik->getNupp(praegune)->getTaht();
                // Lisaks liidame tähe eest saadavad punktid arvestades sealjuures kordajaid
                if (KAHEKORDSED_TAHED.contains(praegune))
                    sonaPunktid += 2 * (kaik->getNupp(praegune)->getPunktid());
                else if (KOLMEKORDSED_TAHED.contains(praegune))
                    sonaPunktid += 3 * (kaik->getNupp(praegune)->getPunktid());
                else if (KAHEKORDSED_SONAD.contains(praegune)) {
                    sonaKordaja *= 2;
                    sonaPunktid += kaik->getNupp(praegune)->getPunktid();
                } else if (KOLMEKORDSED_SONAD.contains(praegune)) {
                    sonaKordaja *= 3;
                    sonaPunktid += kaik->getNupp(praegune)->getPunktid();
                } else {
                    sonaPunktid += kaik->getNupp(praegune)->getPunktid();
                }
            }
            // Järgmine veerg
            praegune += 1;
        } while (praegune != leiaSonaLoppReas(kaik->viimaneIndeks()) + 1);
        // Kas on päris sõna, siis tagastame sõna eest saadud punktid
        if (Dawg::kasSona(sona))
            return punktid + sonaKordaja * sonaPunktid;
        // Sellist sõna pole olemas
        return -1;
    }

    // Kui sõna käidi veerus
    // Käidava sõna esimese tähe asukoht (indeks) veerus
    praegune = leiaSonaAlgusVeerus(kaik->esimeneIndeks());

    // Liigume vaarus üles, kuni jõuame veeru algusesse või tuleb tühi ruut
    while ((praegune - 15) / 15 + 1 != 0 && kaik->kasIndeksOlemas(praegune - 15))
        praegune -= 15;

    // Liigume vaarus alla ja vaatame, kas kõik tekkinud sõnad on päriselt olemas
    do {
        // Kui leiame laualt alt tähe lisame selle oma sõnale otsa
        if (!kasIndeksTyhi(praegune)) {
            sona += m_mangulaud[praegune]->getNupp()->getTaht();
            sonaPunktid += m_mangulaud[praegune]->getNupp()->getPunktid();
        }
            // Kui leiame tähe hoopis käidavast sõnast mitte laualt (sest see on sealt tühi)
        else if (kaik->kasIndeksOlemas(praegune)) {
            // Reas tekkiv sõna
            teineSona = "";
            // Leiame reas tekkiva sõna kõige vasakpoolsema tähe indeksi
            int ajutine = leiaSonaAlgusReas(praegune);
            teineSona = "";
            teiseSonaPunktid = 0;
            teiseSonaKordaja = 1;
            // Kui vasakult paremale liikudes on laual juba täht või on käidav täht
            while (!kasIndeksTyhi(ajutine) || ajutine == praegune) {
                // Kui täht on juba laual olemas või on see meie käidav täht lisame selle reas tekkivale sõnale otsa
                // Lisaks liidame tähe eest saadavad punktid
                if (ajutine != praegune) {
                    teineSona += m_mangulaud[ajutine]->getNupp()->getTaht();
                    teiseSonaPunktid += m_mangulaud[ajutine]->getNupp()->getPunktid();
                } else {
                    // Kui on praegu käidud nupp, arvestame ka erinevaid ruutude kordajaid
                    teineSona += kaik->getNupp(ajutine)->getTaht();
                    if (KAHEKORDSED_TAHED.contains(ajutine))
                        teiseSonaPunktid += 2 * (kaik->getNupp(ajutine)->getPunktid());
                    else if (KOLMEKORDSED_TAHED.contains(ajutine))
                        teiseSonaPunktid += 3 * (kaik->getNupp(ajutine)->getPunktid());
                    else if (KAHEKORDSED_SONAD.contains(ajutine)) {
                        teiseSonaKordaja = 2;
                        teiseSonaPunktid += kaik->getNupp(ajutine)->getPunktid();
                    } else if (KOLMEKORDSED_SONAD.contains(ajutine)) {
                        teiseSonaKordaja = 3;
                        teiseSonaPunktid += kaik->getNupp(ajutine)->getPunktid();
                    } else teiseSonaPunktid += kaik->getNupp(ajutine)->getPunktid();
                }
                // Kas oleme juba viimases vaarus
                if (ajutine % 15 == 14) //kontroll, et oleme viimases veerus
                    break;
                // Järgmine veerg
                ajutine += 1;
            }
            // Kui horisontaalset sõna ei ole olemas
            if (teineSona.size() >= 2 && !(Dawg::kasSona(teineSona)))
                return -1;
            if (teineSona.size() >= 2 && Dawg::kasSona(teineSona)) punktid += teiseSonaKordaja * teiseSonaPunktid;
            // Lisame käidud tähe sõnale otsa
            sona += kaik->getNupp(praegune)->getTaht();
            // Lisaks liidame tähe eest saadavad punktid arvestades sealjuures kordajaid
            if (KAHEKORDSED_TAHED.contains(praegune))
                sonaPunktid += 2 * (kaik->getNupp(praegune)->getPunktid());
            else if (KOLMEKORDSED_TAHED.contains(praegune))
                sonaPunktid += 3 * (kaik->getNupp(praegune)->getPunktid());
            else if (KAHEKORDSED_SONAD.contains(praegune)) {
                sonaKordaja *= 2;
                sonaPunktid += kaik->getNupp(praegune)->getPunktid();
            } else if (KOLMEKORDSED_SONAD.contains(praegune)) {
                sonaKordaja *= 3;
                sonaPunktid += kaik->getNupp(praegune)->getPunktid();
            } else {
                sonaPunktid += kaik->getNupp(praegune)->getPunktid();
            }
        }
        // Järgmine rida
        praegune += 15;
    } while (praegune != leiaSonaLoppVeerus(kaik->viimaneIndeks()) + 15);
    // Kui sõna on päriselt olemas, sagastame selle eest saadavad punktid
    if (Dawg::kasSona(sona)) {
        return punktid + sonaKordaja * sonaPunktid;
    }
    // Sellist sõna ei ole olemas
    return -1;
}

void Laud::lisaSonaLauale(const shared_ptr<Kaik> &kaik) {
    for (int indeks: *kaik->getIndeksid()) {
        if (!kasIndeksTyhi(indeks))
            throw invalid_argument("Kohal (indeks: " + to_string(indeks) + ") on nupp juba olemas!");
    }
    for (const auto &k: kaik->getKaik())
        m_mangulaud[k.first] = make_shared<Ruut>(k.second);
}
