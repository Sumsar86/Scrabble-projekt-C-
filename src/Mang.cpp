//
// Created by Martin on 15.04.2024.
//

#include "Mang.h"
#include "Mangija.h"
//testcomment

int main() {
    Laud laud{};
    cout << laud;

    return 0;
}



/*
    shared_ptr<Kott> kott = make_shared<Kott>();

    cout << "kas on tühi: " << boolalpha << kott->kas_on_tuhi() << ", " << *kott << "\n";

    Mangija m(kott);
//    cout << "kos on tühi: " << boolalpha << kott->kas_on_tuhi() << ", " << *kott << "\n";

    cout << m << "\n\n";

    vector<char> vahetatavad_tahed{'U', 'A', 'E'};
    cout << "vahetan {";
    for_each(vahetatavad_tahed.begin(), vahetatavad_tahed.end(), [](const char& taht){cout << taht << " ";});
    cout << "} uue tähe vastu, kas õnnestus kõik ära vahetada: " << boolalpha << m.vahetaNupud(vahetatavad_tahed) << "\n";

    cout << m << "\n\n";
    cout << "kas on tühi: " << boolalpha << kott->kas_on_tuhi() << ", " << *kott << "\n";

    for (int i = 0; i < 102 - 7; i++)
        cout << *kott->getNupp() << " ";
    cout << "\nkas on tühi: " << boolalpha << kott->kas_on_tuhi() << ", " << *kott << "\n";

    cout << "vahetan 'e' uue tähe vastu, kas õnnestus kõik ära vahetada: " << boolalpha << m.vahetaNupud(*(new vector<char>{'E'})) << "\n";
 */