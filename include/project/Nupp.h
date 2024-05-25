#pragma once

#include <ostream>
#include <string>
#include <map>

using namespace std;

class Nupp {
    char m_taht;
    short m_punktid;
    bool m_tyhi;
public:
    Nupp(char taht, short punktid, bool tyhi = false);

    void setTyhi(bool tyhi);

    bool kasTyhiNupp() const;

    const char &getTaht() const;

    short getPunktid() const;

    friend std::ostream &operator<<(std::ostream &os, const Nupp &nupp);

    bool operator<(const Nupp &rhs) const;

    bool operator>(const Nupp &rhs) const;

    bool operator<=(const Nupp &rhs) const;

    bool operator>=(const Nupp &rhs) const;

    bool operator==(const Nupp &rhs) const;

    bool operator!=(const Nupp &rhs) const;
};
