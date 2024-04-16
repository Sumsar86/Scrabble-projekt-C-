//
// Created by Martin on 15.04.2024.
//

#ifndef SCRABBLE_PROJEKT_C__NUPP_H
#define SCRABBLE_PROJEKT_C__NUPP_H
//testcomment

#include <ostream>

class Nupp {
    char m_taht;
    short m_punktid;
public:
    Nupp(char taht, short punktid);

    friend std::ostream &operator<<(std::ostream &os, const Nupp &nupp);
};


#endif //SCRABBLE_PROJEKT_C__NUPP_H
