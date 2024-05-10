//
// Created by Martin on 06.05.2024.
//

#ifndef SCRABBLE_PROJEKT_C__KAIK_H
#define SCRABBLE_PROJEKT_C__KAIK_H


#include <map>
#include "Nupp.h"
#include <memory>

class Kaik {
private:
    map<int,shared_ptr<Nupp>> m_kaik;
public:
    explicit Kaik(const map<int, shared_ptr<Nupp>> &mKaik);

    bool yhesReas();
    bool yhesVeerus();
    int esimeneIndeks();
    int viimaneIndeks();

    bool kasIndeksOlemas(int indeks);
    shared_ptr<Nupp> getNupp(int indeks);
    shared_ptr<vector<int>> getIndeksid();
};


#endif //SCRABBLE_PROJEKT_C__KAIK_H
