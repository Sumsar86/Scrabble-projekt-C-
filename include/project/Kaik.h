#pragma once

#include <map>
#include "Nupp.h"
#include <memory>

class Kaik {
private:
    map<int, shared_ptr<Nupp>> m_kaik;
public:
    explicit Kaik(const map<int, shared_ptr<Nupp>> &kaik);

    bool yhesReas();

    bool yhesVeerus();

    int esimeneIndeks();

    int viimaneIndeks();

    bool kasIndeksOlemas(int indeks);

    shared_ptr<Nupp> getNupp(int indeks);

    shared_ptr<vector<int>> getIndeksid();
};
