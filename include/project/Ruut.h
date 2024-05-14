#pragma once

#include <memory>
#include <ostream>
#include "string"
#include "Nupp.h"

using namespace std;

class Ruut {
private:
    shared_ptr<Nupp> m_nupp;
    short m_sonaKordaja;
    short m_taheKordaja;
public:
    Ruut(short sonaKordaja, short taheKordaja);

    bool kasTyhi();

    const shared_ptr<Nupp> &getNupp() const;

    friend ostream &operator<<(ostream &os, const Ruut &ruut);
};
