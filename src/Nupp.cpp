//
// Created by Martin on 15.04.2024.
//

#include "Nupp.h"

Nupp::Nupp(char taht, short punktid) : m_taht(taht), m_punktid(punktid) {}


std::ostream &operator<<(std::ostream &os, const Nupp &nupp) {
    os << nupp.m_taht;
    return os;
}

bool Nupp::operator<(const Nupp &rhs) const {
    if (m_taht < rhs.m_taht)
        return true;
    if (rhs.m_taht < m_taht)
        return false;
    return m_punktid < rhs.m_punktid;
}

bool Nupp::operator>(const Nupp &rhs) const {
    return rhs < *this;
}

bool Nupp::operator<=(const Nupp &rhs) const {
    return !(rhs < *this);
}

bool Nupp::operator>=(const Nupp &rhs) const {
    return !(*this < rhs);
}

bool Nupp::operator==(const Nupp &rhs) const {
    return m_taht == rhs.m_taht;
}

bool Nupp::operator!=(const Nupp &rhs) const {
    return !(rhs == *this);
}

const char &Nupp::getTaht() const {
    return m_taht;
}

