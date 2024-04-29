#ifndef SCRABBLE_PROJEKT_C__NUPP_H
#define SCRABBLE_PROJEKT_C__NUPP_H

#include <ostream>
#include <string>

using namespace std;

class Nupp {
    string m_taht;
    short m_punktid;
public:
    Nupp(string taht, short punktid);

    const string &getTaht() const;

    friend std::ostream &operator<<(std::ostream &os, const Nupp &nupp);

    bool operator<(const Nupp &rhs) const;

    bool operator>(const Nupp &rhs) const;

    bool operator<=(const Nupp &rhs) const;

    bool operator>=(const Nupp &rhs) const;

    bool operator==(const Nupp &rhs) const;

    bool operator!=(const Nupp &rhs) const;
};



#endif //SCRABBLE_PROJEKT_C__NUPP_H
