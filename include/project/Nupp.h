#ifndef SCRABBLE_PROJEKT_C__NUPP_H
#define SCRABBLE_PROJEKT_C__NUPP_H

#include <ostream>
#include <string>

using namespace std;

class Nupp {
    char m_taht;
    short m_punktid;
public:
    Nupp(char taht, short punktid);

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



#endif //SCRABBLE_PROJEKT_C__NUPP_H
