#include "Ruut.h"

// Ruudu konstruktor
Ruut::Ruut(short sonakordaja, short tahekordaja) : mp_nupp(nullptr), m_sonakordaja(sonakordaja),
                                                   m_tahekordaja(tahekordaja) {};

// Ruudu konstruktor, mis võtab olemasoleva nupu endale aluseks
Ruut::Ruut(shared_ptr<Nupp> nupp) : mp_nupp(std::move(nupp)), m_sonakordaja(1), m_tahekordaja(1) {};

// Ruudu kuvamiseks ekraanil
ostream &operator<<(ostream &os, const Ruut &ruut) {
    // Kui ruudule ei ole veel nuppu käidud
    if (!ruut.mp_nupp) {
//         Kui ruudul on tähekordaja
        if (ruut.m_tahekordaja == 2) {
            SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(9));
            os << " " << ruut.m_tahekordaja;
            SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(7));
            return os;
        }
        if (ruut.m_tahekordaja == 3) {
            SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(1));
            os << " " << ruut.m_tahekordaja;
            SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(7));
            return os;
        }
//         Kui ruudul on sõnakordaja
        if (ruut.m_sonakordaja == 2) {
            SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(14));
            os << " " << ruut.m_sonakordaja;
            SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(7));
            return os;
        }
        if (ruut.m_sonakordaja == 3) {
            SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(4));
            os << " " << ruut.m_sonakordaja;
            SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(7));
            return os;
        }
        // Kui ruut on täiesti tühi (ehk kõik kordajad on ühed)
        os << " _";
        return os;
    }
    // Kui ruudul on nupp, siis kordajaid ei kuvata
    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
    os << " " << *(ruut.getNupp());
    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(7));
    return os;
}

// Kas ruudule on nupp asetatud
bool Ruut::kasTyhi() {
    return !mp_nupp;
}

// Tagastab enale asetatud nupu
const shared_ptr<Nupp> &Ruut::getNupp() const {
    if (!mp_nupp) {
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(4));
        cout << "Ruudul pole nuppu! Tagastan nullptr.\n";
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(7));
    }
    return mp_nupp;
}
