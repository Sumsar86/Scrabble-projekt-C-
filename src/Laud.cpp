//
// Created by Martin on 15.04.2024.
//

#include <iostream>
#include "Laud.h"

set<short> Laud::m_kahekordsedTahed = {3, 11, 36, 38, 45, 52, 59, 92, 96, 98, 102, 108, 116, 122, 126, 128, 132, 165,
                                       172, 179, 186, 188, 213, 221};
set<short> Laud::m_kolmekordsedTahed = {20, 24, 76, 80, 84, 88, 136, 140, 144, 148, 200, 204};
set<short> Laud::m_kahekordsedSonad = {16,28,32,42,48,56,64,70,154,160,168,176,182,192,196,208};
set<short> Laud::m_kolmekordsedSonad = {0,14,105,119,210,224};


Laud::Laud() {
    for (short i{0}; i < 225; i++){
        if (m_kahekordsedTahed.contains(i)){
            m_mangulaud.push_back(make_shared<Ruut>(1,2));
            continue;
        }
        if (m_kolmekordsedTahed.contains(i)){
            m_mangulaud.push_back(make_shared<Ruut>(1,3));
            continue;
        }
        if (m_kahekordsedSonad.contains(i)){
            m_mangulaud.push_back(make_shared<Ruut>(2,1));
            continue;
        }
        if (m_kolmekordsedSonad.contains(i)){
            m_mangulaud.push_back(make_shared<Ruut>(3,1));
            continue;
        }
        m_mangulaud.push_back(make_shared<Ruut>(1,1));
    }
}

ostream &operator<<(ostream &os, const Laud &laud) {
    for (int i{0}; i < 15; i++){
        if (i < 9)
            os << ' ';
        os << i + 1 << " | ";

        for (int j{0}; j < 15; j++){
            short index = i * 15 + j;
            os << *laud.m_mangulaud.at(index) << ' ';
        }
        os << '\n';
    }
    os << "   +------------------------------\n";
    os << "     A B C D E F G H I J K L M N O\n";
    return os;
}
