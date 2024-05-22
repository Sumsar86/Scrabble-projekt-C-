#include "Mang.h"
#include "Mangija.h"
#include <memory>

int main() {
    /*Laud laud("_______________"
              "_______________"
              "__J__________M_"
              "__Q___W___JUGA_"
              "__U_T_E___O__I_"
              "__K_U_S___T__N_"
              "__A_R_TAFTIL_E_"
              "__MXNGITA____N_"
              "__A_E_D_I____I_"
              "____E__________"
              "____D__________"
              "_______________"
              "_______________"
              "_______________"
              "_______________");

    //Laud laud{};

//    vector<shared_ptr<Ruut>> asi;
//    for (int i{0}; i < 225; i++){
//        if (i == 1) {
//            auto nupp = make_shared<Nupp>('A', 1);
//            auto ruut = make_shared<Ruut>(nupp);
//            asi.push_back(ruut);
//        }
//        else{
//            asi.push_back(make_shared<Ruut>(1,1));
//        }
//    }
//    Laud laud(asi);

    cout << laud;
    /*
    shared_ptr<Nupp> taht1 = make_shared<Nupp>('A', 1);
    shared_ptr<Nupp> taht2 = make_shared<Nupp>('A', 1);
    shared_ptr<Nupp> taht3 = make_shared<Nupp>('B', 3);
    shared_ptr<Nupp> taht4 = make_shared<Nupp>('I', 1);
    shared_ptr<Nupp> taht5 = make_shared<Nupp>('T', 1);
    shared_ptr<Nupp> taht6 = make_shared<Nupp>('S', 1);
    shared_ptr<Nupp> taht7 = make_shared<Nupp>('A', 1);
    shared_ptr<Nupp> taht8 = make_shared<Nupp>('S', 1);
    shared_ptr<Nupp> taht9 = make_shared<Nupp>('T', 1);

    map<int, shared_ptr<Nupp>> sona1{{112, taht1}, {127,taht2},
                                     {142,taht3}, {157,taht4}, {172,taht5},
                                     {187,taht6}, {202, taht7}
    };

    shared_ptr<Kaik> kaik = make_shared<Kaik>(sona1);

    cout << "Punktid sõna AABITSAST eest: " << laud.kontrolli(kaik) << "\n";


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
        cout << *kott->getJuhuslikNupp() << " ";
    cout << "\nkas on tühi: " << boolalpha << kott->kas_on_tuhi() << ", " << *kott << "\n";

    cout << "vahetan 'e' uue tähe vastu, kas õnnestus kõik ära vahetada: " << boolalpha << m.vahetaNupud(*(new vector<char>{'E'})) << "\n";

    */
    return 0;
}