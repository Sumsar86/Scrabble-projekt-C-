#pragma once

#include <memory>
#include <utility>
#include <ostream>
#include "Kuna.h"
#include "Kott.h"

class Mangija {
private:
    shared_ptr<Kott> mp_kott;
    Kuna m_kuna;
    int m_punktid;

public:
    explicit Mangija(shared_ptr<Kott> &kott);

    bool vahetaNupud(vector<char> &tahed);

    friend ostream &operator<<(ostream &os, const Mangija &mangija);
};
