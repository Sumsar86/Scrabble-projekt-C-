//
// Created by Martin on 15.04.2024.
//

#include <iostream>
#include "Laud.h"
#include "Dawg.cpp"

set<short> Laud::m_kahekordsedTahed = {3, 11, 36, 38, 45, 52, 59, 92, 96, 98, 102, 108, 116, 122, 126, 128, 132, 165,
                                       172, 179, 186, 188, 213, 221};
set<short> Laud::m_kolmekordsedTahed = {20, 24, 76, 80, 84, 88, 136, 140, 144, 148, 200, 204};
set<short> Laud::m_kahekordsedSonad = {16,28,32,42,48,56,64,70,154,160,168,176,182,192,196,208};
set<short> Laud::m_kolmekordsedSonad = {0,14,105,119,210,224};


Laud::Laud() {
    for (short i{0}; i < 225; i++){
        if (m_kahekordsedTahed.contains(i)){
            m_mangulaud.push_back(make_shared<Ruut>(1,2));
            continue;
        }
        if (m_kolmekordsedTahed.contains(i)){
            m_mangulaud.push_back(make_shared<Ruut>(1,3));
            continue;
        }
        if (m_kahekordsedSonad.contains(i)){
            m_mangulaud.push_back(make_shared<Ruut>(2,1));
            continue;
        }
        if (m_kolmekordsedSonad.contains(i)){
            m_mangulaud.push_back(make_shared<Ruut>(3,1));
            continue;
        }
        m_mangulaud.push_back(make_shared<Ruut>(1,1));
    }
}

ostream &operator<<(ostream &os, const Laud &laud) {
    for (int i{0}; i < 15; i++){
        if (i < 9)
            os << ' ';
        os << i + 1 << " | ";

        for (int j{0}; j < 15; j++){
            short index = i * 15 + j;
            os << *laud.m_mangulaud.at(index) << ' ';
        }
        os << '\n';
    }
    os << "   +------------------------------\n";
    os << "     A B C D E F G H I J K L M N O\n";
    return os;
}

bool Laud::kontrolli(shared_ptr<Kaik> kaik) {
    return kontrolliPos(kaik) && kontrolliSonu(kaik);
}

bool Laud::kontrolliPos(shared_ptr<Kaik> kaik) {
    bool onReas = kaik->yhesReas();
    bool onVeerus = kaik->yhesVeerus();
    int indeks, viimane;
    if (!(onReas || onVeerus))
        return false;

    if (onReas){
        indeks = kaik->esimeneIndeks();
        viimane = kaik->viimaneIndeks();
        while (indeks != viimane){
            if (!kasIndeksTyhi(indeks) && kaik->kasIndeksOlemas(indeks) || kasIndeksTyhi(indeks) && !(kaik->kasIndeksOlemas(indeks)))
                return false;
            indeks++;
        }
    }
    else{
        indeks = kaik->esimeneIndeks();
        viimane = kaik->viimaneIndeks();
        while (indeks != viimane){
            if (!kasIndeksTyhi(indeks) && kaik->kasIndeksOlemas(indeks) || kasIndeksTyhi(indeks) && !(kaik->kasIndeksOlemas(indeks)))
                return false;
            indeks += 15;
        }
    }

    if (kasEsimeneKaik()){
        if (!(kaik->kasIndeksOlemas(m_mangulaud.size()/2)))
            return false;
    }

    for (int i : *kaik->getIndeksid()){
        if (!kasIndeksTyhi(i - 1))
            return true;
        if (!kasIndeksTyhi(i + 1))
            return true;
        if (!kasIndeksTyhi(i - 15))
            return true;
        if (!kasIndeksTyhi(i + 15))
            return true;
    }
    return false;
}

bool Laud::kontrolliSonu(shared_ptr<Kaik> kaik) { //eeldame, et käik on korrektselt positsioneeritud
    bool onReas = kaik->yhesReas();
    if (onReas){
        int praegune = leiaSonaAlgusReas(kaik->esimeneIndeks());
        string sona{};

        while ((praegune - 1) % 15 + 1 != 0 && kaik->kasIndeksOlemas(praegune - 1))
            praegune -= 1;
        do{
            if (!kasIndeksTyhi(praegune)) {
                sona += m_mangulaud[praegune]->getNupp()->getTaht();
                praegune += 1;
            }
            else if (kaik->kasIndeksOlemas(praegune)) {
                int ajutine = leiaSonaAlgusVeerus(praegune);
                string teineSona{};
                while (!kasIndeksTyhi(ajutine) && ajutine != praegune){
                    if (ajutine != praegune)
                        teineSona += m_mangulaud[ajutine]->getNupp()->getTaht();
                    else{
                        teineSona += kaik->getNupp(ajutine)->getTaht();
                    }
                    if (ajutine > 209)
                        break;
                    ajutine += 15;
                }
                if (!(Dawg::kasSona(teineSona))) return false;
                sona += kaik->getNupp(ajutine)->getTaht();
            }
        }
        while (praegune % 15 != 0);
        return Dawg::kasSona(sona);
    }
}

bool Laud::kasEsimeneKaik() {
    for (int i{0}; i < m_mangulaud.size(); i++){
        if (!kasIndeksTyhi(i))
            return false;
    }
    return true;
}

bool Laud::kasIndeksTyhi(int indeks) {
    return m_mangulaud[indeks]->kasTyhi();
}

int Laud::leiaSonaAlgusReas(int indeks) {
    while (indeks % 15 > 0){
        indeks--;
        if (kasIndeksTyhi(indeks))
            return ++indeks;
    }
    return indeks;
}

int Laud::leiaSonaAlgusVeerus(int indeks) {
    while (indeks / 15 > 0){
        indeks -= 15;
        if (kasIndeksTyhi(indeks))
            return indeks + 15;
    }
    return indeks;
}


