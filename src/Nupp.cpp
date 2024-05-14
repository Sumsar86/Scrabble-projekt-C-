#include "Nupp.h"

// Nupu konstruktor
Nupp::Nupp(char taht, short punktid) : m_taht(taht), m_punktid(punktid) {}

// Nupu kuvamiseks ekraanil
std::ostream &operator<<(std::ostream &os, const Nupp &nupp) {
    os << nupp.getTaht();
    return os;
}

// Nuppude omavaheliseks võrdlemiseks
bool Nupp::operator<(const Nupp &rhs) const {
    if (m_taht < rhs.m_taht)
        return true;
    if (rhs.m_taht < m_taht)
        return false;
    return m_punktid < rhs.m_punktid;
}

// Nuppude omavaheliseks võrdlemiseks
bool Nupp::operator>(const Nupp &rhs) const {
    return rhs < *this;
}

// Nuppude omavaheliseks võrdlemiseks
bool Nupp::operator<=(const Nupp &rhs) const {
    return !(rhs < *this);
}

// Nuppude omavaheliseks võrdlemiseks
bool Nupp::operator>=(const Nupp &rhs) const {
    return !(*this < rhs);
}

// Nuppude omavaheliseks võrdlemiseks
bool Nupp::operator==(const Nupp &rhs) const {
    return m_taht == rhs.m_taht;
}

// Nuppude omavaheliseks võrdlemiseks
bool Nupp::operator!=(const Nupp &rhs) const {
    return !(rhs == *this);
}

// Tagastab nupu tähe
const char &Nupp::getTaht() const {
    return m_taht;
}

short Nupp::getPunktid() const {
    return m_punktid;
}

