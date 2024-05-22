#pragma once

#include <memory>
#include <ostream>
#include "string"
#include "Nupp.h"


using namespace std;

class Ruut {
private:
    shared_ptr<Nupp> mp_nupp;
    short m_sonakordaja;
    short m_tahekordaja;
public:
    Ruut(short sonakordaja, short tahekordaja);
    Ruut(shared_ptr<Nupp> nupp);

    bool kasTyhi();

    const shared_ptr<Nupp> &getNupp() const;

    friend ostream &operator<<(ostream &os, const Ruut &ruut);
};
