//
// Created by Martin on 15.04.2024.
//

#include "Nupp.h"

Nupp::Nupp(char taht, short punktid) : m_taht(taht), m_punktid(punktid) {}

std::ostream &operator<<(std::ostream &os, const Nupp &nupp) {
    os << nupp.m_taht;
    return os;
}
