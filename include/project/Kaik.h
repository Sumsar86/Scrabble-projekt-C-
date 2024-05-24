#pragma once

#include <map>
#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>
#include "Ruut.h"
#include "Konstandid.h"
//#include "Laud.h"
//#include "Nupp.h"

class Kaik {
private:
    map<int, shared_ptr<Nupp>> m_kaik;
public:
    explicit Kaik(const map<int, shared_ptr<Nupp>> &kaik);

    Kaik(string sona, string koordinaadid, string suund);

    bool yhesReas();

    bool yhesVeerus();

    friend ostream &operator<<(ostream &os, const Kaik &kaik);

    int esimeneIndeks();

    int viimaneIndeks();

    bool kasIndeksOlemas(int indeks);

    shared_ptr<Nupp> getNupp(int indeks);

    shared_ptr<vector<int>> getIndeksid() const;

    map<int, shared_ptr<Nupp>> getKaik() const;
};
