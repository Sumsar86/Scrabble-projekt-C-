#pragma once

#include <set>
#include <map>

using namespace std;

// Erinevate ruutude sõna- ja tähekordajad laual
const static set<short> KAHEKORDSED_TAHED = {3, 11, 36, 38, 45, 52, 59, 92, 96, 98, 102, 108, 116, 122, 126, 128, 132, 165,
                                         172, 179, 186, 188, 213, 221};
const static set<short> KOLMEKORDSED_TAHED = {20, 24, 76, 80, 84, 88, 136, 140, 144, 148, 200, 204};
const static set<short> KAHEKORDSED_SONAD = {16, 28, 32, 42, 48, 56, 64, 70, 112, 154, 160, 168, 176, 182, 192, 196, 208};
const static set<short> KOLMEKORDSED_SONAD = {0, 14, 105, 119, 210, 224};

// Kõigi tähtede punktid (väikesed on tühjad ruudud, seega punkte ei anna)
static map<char, int> TAHE_PUNKTID = {{'A', 1},
                                        {'a', 0},
                                        {'B', 3},
                                        {'b', 0},
                                        {'D', 2},
                                        {'d', 0},
                                        {'E', 1},
                                        {'e', 0},
                                        {'F', 8},
                                        {'f', 0},
                                        {'G', 3},
                                        {'g', 0},
                                        {'H', 4},
                                        {'h', 0},
                                        {'I', 1},
                                        {'i', 0},
                                        {'J', 4},
                                        {'j', 0},
                                        {'K', 1},
                                        {'k', 0},
                                        {'L', 1},
                                        {'l', 0},
                                        {'M', 2},
                                        {'m', 0},
                                        {'N', 2},
                                        {'n', 0},
                                        {'O', 1},
                                        {'0', 0},
                                        {'P', 4},
                                        {'p', 0},
                                        {'R', 2},
                                        {'r', 0},
                                        {'S', 1},
                                        {'s', 0},
                                        {'$', 10},
                                        {'#', 0},
                                        {'Z', 10},
                                        {'z', 0},
                                        {'W', 10},
                                        {'w', 0},
                                        {'T', 1},
                                        {'t', 0},
                                        {'U', 1},
                                        {'u', 0},
                                        {'V', 3},
                                        {'v', 0},
                                        {'Q', 4},
                                        {'q', 0},
                                        {'X', 5},
                                        {'x', 0},
                                        {'C', 6},
                                        {'c', 0},
                                        {'Y', 5},
                                        {'y', 0},
                                        {'?', 0}};