//
// Created by Martin on 28.04.2024.
//

#include "Kott.h"

Kott::Kott(map<Nupp, int> mNupud) : m_nupud(mNupud) {}
Kott::Kott() : m_nupud{
            {Nupp("A",1), 10}, {Nupp("B",3), 1},
            {Nupp("D",2), 4}, {Nupp("E",1), 9},
            {Nupp("F",8), 1}, {Nupp("G",3), 2},
            {Nupp("H",4), 2}, {Nupp("I",1), 9},
            {Nupp("J",4), 2}, {Nupp("K",1), 5},
            {Nupp("L",1), 5}, {Nupp("M",2), 4},
            {Nupp("N",2), 4}, {Nupp("O",1), 5},
            {Nupp("P",4), 2}, {Nupp("R",2), 2},
            {Nupp("S",1), 8}, {Nupp("Š",10), 1},
            {Nupp("Z",10), 1}, {Nupp("Ž",10), 1},
            {Nupp("T",1), 7}, {Nupp("U",1), 5},
            {Nupp("V",3), 2}, {Nupp("Õ",4), 2},
            {Nupp("Ä",5), 2}, {Nupp("Ö",6), 2},
            {Nupp("Ü",5), 2}, {Nupp("?",0), 2}
} {}
