#include <iostream>
#include <algorithm>
#include "Laud.h"
#include "Dawg.h"

// Erinevate ruutude sõna- ja tähekordajad laual
set<short> Laud::m_kahekordsedTahed = {3, 11, 36, 38, 45, 52, 59, 92, 96, 98, 102, 108, 116, 122, 126, 128, 132, 165,
                                       172, 179, 186, 188, 213, 221};
set<short> Laud::m_kolmekordsedTahed = {20, 24, 76, 80, 84, 88, 136, 140, 144, 148, 200, 204};
set<short> Laud::m_kahekordsedSonad = {16, 28, 32, 42, 48, 56, 64, 70, 154, 160, 168, 176, 182, 192, 196, 208};
set<short> Laud::m_kolmekordsedSonad = {0, 14, 105, 119, 210, 224};

// Laua konstruktor, mis loob mängualguse laua ehk lisab sinna õigete kordajatega tühjad ruudud
Laud::Laud() {
    for (short i{0}; i < 225; i++) {
        if (m_kahekordsedTahed.contains(i)) {
            m_mangulaud.push_back(make_shared<Ruut>(1, 2));
            continue;
        }
        if (m_kolmekordsedTahed.contains(i)) {
            m_mangulaud.push_back(make_shared<Ruut>(1, 3));
            continue;
        }
        if (m_kahekordsedSonad.contains(i)) {
            m_mangulaud.push_back(make_shared<Ruut>(2, 1));
            continue;
        }
        if (m_kolmekordsedSonad.contains(i)) {
            m_mangulaud.push_back(make_shared<Ruut>(3, 1));
            continue;
        }
        m_mangulaud.push_back(make_shared<Ruut>(1, 1));
    }
}

// Laua ekraanile kuvamiseks
ostream &operator<<(ostream &os, const Laud &laud) {
    for (int i{0}; i < 15; i++) {
        if (i < 9)
            os << ' ';
        os << i + 1 << " | ";

        for (int j{0}; j < 15; j++) {
            short index = i * 15 + j;
            os << *laud.m_mangulaud.at(index) << ' ';
        }
        os << '\n';
    }
    os << "   +------------------------------\n";
    os << "     A B C D E F G H I J K L M N O\n";
    return os;
}

// Kutsub käigu kontrollimise funktsioonid välja
bool Laud::kontrolli(const shared_ptr<Kaik> &kaik) {
    return kontrolliPos(kaik) && kontrolliSonu(kaik);
}

// Kontrollib, kas käidav käik asetseb laual vastavalt reeglitele
bool Laud::kontrolliPos(const shared_ptr<Kaik> &kaik) {
    bool onReas = kaik->yhesReas();
    bool onVeerus = kaik->yhesVeerus();
    int indeks, viimane;
    // Käik pole sirges reas ega veerus
    if (!(onReas || onVeerus)) {
        cerr << "Ei ole reas ega veerus!\n";
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
            cerr << "Esimene käik tuleb käia läbi keskmise ruudu!\n";
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

// Kontrollib, kas sõna on sõnastikus (DAWG andmestruktuuris) olemas
bool Laud::kontrolliSonu(const shared_ptr<Kaik> &kaik) { //eeldame, et käik on korrektselt positsioneeritud
    bool onReas = kaik->yhesReas();
    int praegune;
    string sona{}, teineSona{};

    // Kui sõna käidi reas
    if (onReas) {
        // Käidava sõna esimese tähe asukoht (indeks) reas
        praegune = leiaSonaAlgusReas(kaik->esimeneIndeks());

        // Liigume reas vasakule, kuni jõuame rea algusesse või tuleb tühi ruut
        while ((praegune - 1) % 15 + 1 != 0 && kaik->kasIndeksOlemas(praegune - 1))
            praegune -= 1;

        // Liigume reas paremale ja vaatame, kas kõik tekkinud sõnad on päriselt olemas
        do {
            // Kui leiame laualt paremalt tähe lisame selle oma sõnale otsa
            if (!kasIndeksTyhi(praegune))
                sona += m_mangulaud[praegune]->getNupp()->getTaht();
            // Kui leiame tähe hoopis käidavast sõnast mitte laualt (sest see on sealt tühi)
            else if (kaik->kasIndeksOlemas(praegune)) {
                // Veerus tekkiv sõna
                teineSona = "";
                // Leiame veerus tekkiva sõna kõige ülemise tähe indeksi
                int ajutine = leiaSonaAlgusVeerus(praegune);
                // Kui ülevalt alla liikudes on laual juba täht või on käidav täht
                while (!kasIndeksTyhi(ajutine) || ajutine == praegune) {
                    // Kui täht on juba laual olemas või on see meie käidav täht lisame selle veerus tekkivale sõnale otsa
                    if (ajutine != praegune)
                        teineSona += m_mangulaud[ajutine]->getNupp()->getTaht();
                    else
                        teineSona += kaik->getNupp(ajutine)->getTaht();
                    // Kas oleme juba viimases reas ehk indeks > 209 = 255 - 15
                    if (ajutine > 209)
                        break;
                    // Järgmine rida
                    ajutine += 15;
                }
                // Kui vertikaalset sõna ei ole olemas
                if (teineSona.size() >= 2 && !(Dawg::kasSona(teineSona)))
                    return false;
                // Lisame käidud tähe sõnale otsa
                sona += kaik->getNupp(praegune)->getTaht();
            }
            // Järgmine veerg
            praegune += 1;
        } while (praegune != leiaSonaLoppReas(kaik->viimaneIndeks()) + 1);

        // Kas leitud sõna on olemas
        return Dawg::kasSona(sona);
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
        if (!kasIndeksTyhi(praegune))
            sona += m_mangulaud[praegune]->getNupp()->getTaht();
        // Kui leiame tähe hoopis käidavast sõnast mitte laualt (sest see on sealt tühi)
        else if (kaik->kasIndeksOlemas(praegune)) {
            // Reas tekkiv sõna
            teineSona = "";
            // Leiame reas tekkiva sõna kõige vasakpoolsema tähe indeksi
            int ajutine = leiaSonaAlgusReas(praegune);
            // Kui vasakult paremale liikudes on laual juba täht või on käidav täht
            while (!kasIndeksTyhi(ajutine) || ajutine == praegune) {
                // Kui täht on juba laual olemas või on see meie käidav täht lisame selle reas tekkivale sõnale otsa
                if (ajutine != praegune)
                    teineSona += m_mangulaud[ajutine]->getNupp()->getTaht();
                else
                    teineSona += kaik->getNupp(ajutine)->getTaht();
                // Kas oleme juba viimases vaarus
                if (ajutine % 15 == 14)
                    break;
                // Järgmine veerg
                ajutine += 1;
            }
            // Kui horisontaalset sõna ei ole olemas
            if (teineSona.size() >= 2 && !(Dawg::kasSona(teineSona)))
                return false;
            // Lisame käidud tähe sõnale otsa
            sona += kaik->getNupp(praegune)->getTaht();
        }
        // Järgmine rida
        praegune += 15;
    } while (praegune != leiaSonaLoppVeerus(kaik->viimaneIndeks()) + 15);
    // Kas leitud sõna on olemas
    return Dawg::kasSona(sona);
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


