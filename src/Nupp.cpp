#include "Nupp.h"

// Nupu konstruktor
Nupp::Nupp(char taht, short punktid, bool tyhi) : m_taht(taht), m_punktid(punktid), m_tyhi(tyhi) {}

// Nupu kuvamiseks ekraanil
std::ostream &operator<<(std::ostream &os, const Nupp &nupp) {
#ifdef tapitahed
    switch (nupp.getTaht()) {
        case 'Q':
            os << "Õ";
            break;
        case 'q':
            os << "õ";
            break;
        case 'X':
            os << "Ä";
            break;
        case 'x':
            os << "ä";
            break;
        case 'C':
            os << "Ö";
            break;
        case 'c':
            os << "ö";
            break;
        case 'Y':
            os << "Ü";
            break;
        case 'y':
            os << "ü";
            break;
        case '$':
            os << "Š";
            break;
        case '#':
            os << "š";
            break;
        case 'W':
            os << "Ž";
            break;
        case 'w':
            os << "ž";
            break;
        default:
            os << nupp.getTaht();
    }
#else
    os << nupp.getTaht();
#endif
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

// Tagastab nupu punktid
short Nupp::getPunktid() const {
    if (m_tyhi)
        return 0;
    return m_punktid;
}

void Nupp::setTyhi(bool tyhi) {
    m_tyhi = tyhi;
}

bool Nupp::kasTyhiNupp() const {
    return m_tyhi;
}
