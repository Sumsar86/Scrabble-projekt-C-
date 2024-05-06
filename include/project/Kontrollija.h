//
// Created by Martin on 06.05.2024.
//

#ifndef SCRABBLE_PROJEKT_C__KONTROLLIJA_H
#define SCRABBLE_PROJEKT_C__KONTROLLIJA_H


#include "Kaik.h"
#include "Laud.h"
#include <memory>

class Kontrollija {
private:
    shared_ptr<Kaik> m_kaik;
    shared_ptr<Laud> m_laud;
public:
    Kontrollija(const shared_ptr<Kaik> &mKaik, const shared_ptr<Laud> &mLaud);

    bool kontrolli(); //kontrollib, kas käik on valiidne
    bool kontrolliPositsiooni(); //kontrollib, kas käik on valiidses kohas laual
    bool kontrolliSonu(); //kontrollib, kas käigu lõpuks tekkinud sõnad on olemas
};


#endif //SCRABBLE_PROJEKT_C__KONTROLLIJA_H
