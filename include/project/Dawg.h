#pragma once

#include <iostream>
#include <fstream>
#include <vector>
//#include <bitset>

using namespace std;

class Dawg {
private:
    static vector<int> m_dawg;

    static bool kasLasteLopp(int tipp);

    static bool kasSonaLopp(int tipp);

    static char misTaht(int tipp);

    static int misLaps(int tipp);

public:
    static vector<int> readIntegers(const string &faili_nimi);

    bool static kasSona(string sona, int algus = 2);

    //kontrollib, kas antud sõna algusele (algus) saab tähe taht lisada nii, et sellest saaks veel mingi korrektse sõna ehitada (vajadusel veel tähti lõppu lisades).
    int static kasTahtSobib(string taht, int algus = 2);
};
