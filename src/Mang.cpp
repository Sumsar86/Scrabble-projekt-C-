//
// Created by Martin on 15.04.2024.
//

#include "Mang.h"
#include "Mangija.h"
#include <memory>

int main() {
    Laud laud{};
    cout << laud;
    shared_ptr<Nupp> taht1 = make_shared<Nupp>('A', 1);
    shared_ptr<Nupp> taht2 = make_shared<Nupp>('A', 1);
    shared_ptr<Nupp> taht3 = make_shared<Nupp>('B', 3);
    shared_ptr<Nupp> taht4 = make_shared<Nupp>('I', 1);
    shared_ptr<Nupp> taht5 = make_shared<Nupp>('T', 1);
    shared_ptr<Nupp> taht6 = make_shared<Nupp>('S', 1);
    shared_ptr<Nupp> taht7 = make_shared<Nupp>('A', 1);

    map<int, shared_ptr<Nupp>> sona1{{112, taht1}, {113,taht2}};

    shared_ptr<Kaik> kaik = make_shared<Kaik>(sona1);

    cout << boolalpha << laud.kontrolli(kaik);


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