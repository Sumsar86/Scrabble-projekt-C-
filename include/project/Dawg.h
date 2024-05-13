#ifndef SCRABBLE_PROJEKT_C__DAWG_H
#define SCRABBLE_PROJEKT_C__DAWG_H

using namespace std;

class Dawg {
private:
    static vector<int> m_dawg;

    static bool kasLasteLopp(int tipp);

    static bool kasSonaLopp(int tipp);

    static char misTaht(int tipp);

    static int misLaps(int tipp);

public:
    Dawg(string failiNimi);

    static vector<int> readIntegers(const string &failiNimi);

    bool static kasSona(string sona, int algus = 2);
};

#endif //SCRABBLE_PROJEKT_C__DAWG_H
