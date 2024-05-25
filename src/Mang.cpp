#include "Mang.h"


// Kui uus sõna panna rea lõppu, kas see läheb järgmisele reale
int main() {
    Mang m{};
    m.jargmineKaik();

//    string koordinaadid{"c2"};
//    int x = toupper(koordinaadid[0]) - 65;
//    int y = stoi(koordinaadid.substr(1, koordinaadid.size() - 1)) - 1;
//    int indeks = y * 15 + x;
//    cout << "x: " << x << ", y:" << y << ", i: " << indeks << "\n";

//    Laud laud("_______________"
//              "_______________"
//              "__J__________M_"
//              "__Q___W___JUGA_"
//              "__U_T_E___O__I_"
//              "__K_U_S___T__N_"
//              "__A_R_TAFTIL_E_"
//              "__MXNGITA____N_"
//              "__A_E_D_I____I_"
//              "____E__________"
//              "____D__________"
//              "_______________"
//              "_______________"
//              "_______________"
//              "_______________");

//    Laud laud{};

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

//    cout << laud;

//    shared_ptr<Nupp> taht1 = make_shared<Nupp>('A', 1);
//    shared_ptr<Nupp> taht2 = make_shared<Nupp>('A', 1);
//    shared_ptr<Nupp> taht3 = make_shared<Nupp>('B', 3);
//    shared_ptr<Nupp> taht4 = make_shared<Nupp>('I', 1);
//    shared_ptr<Nupp> taht5 = make_shared<Nupp>('T', 1);
//    shared_ptr<Nupp> taht6 = make_shared<Nupp>('S', 1);
//    shared_ptr<Nupp> taht7 = make_shared<Nupp>('A', 1);
//    shared_ptr<Nupp> taht8 = make_shared<Nupp>('S', 1);
//    shared_ptr<Nupp> taht9 = make_shared<Nupp>('T', 1);
//
//    map<int, shared_ptr<Nupp>> sona1{{112, taht1}, {127,taht2},
//                                     {142,taht3}, {157,taht4}, {172,taht5},
//                                     {187,taht6}, {202, taht7}
//    };
//
//    shared_ptr<Kaik> kaik = make_shared<Kaik>(sona1);
//
//    cout << "Punktid sõna AABITSAST eest: " << laud.kontrolli(kaik) << "\n";
//
//
//    shared_ptr<Kott> kott = make_shared<Kott>();
//
//    cout << "kas on tühi: " << boolalpha << kott->kas_on_tuhi() << ", " << *kott << "\n";
//
//    Mangija m(kott);
////    cout << "kos on tühi: " << boolalpha << kott->kas_on_tuhi() << ", " << *kott << "\n";
//
//    cout << m << "\n\n";
//
//    vector<char> vahetatavad_tahed{'U', 'A', 'E'};
//    cout << "vahetan {";
//    for_each(vahetatavad_tahed.begin(), vahetatavad_tahed.end(), [](const char& taht){cout << taht << ", ";});
//    cout << "} uue tähe vastu, kas õnnestus kõik ära vahetada: " << boolalpha << m.vahetaNupud(vahetatavad_tahed) << "\n";
//
//    cout << m << "\n\n";
//    cout << "kas on tühi: " << boolalpha << kott->kas_on_tuhi() << ", " << *kott << "\n";
//
//    for (int i = 0; i < 102 - 7; i++)
//        cout << *kott->getJuhuslikNupp() << " ";
//    cout << "\nkas on tühi: " << boolalpha << kott->kas_on_tuhi() << ", " << *kott << "\n";
//
//    cout << "vahetan 'e' uue tähe vastu, kas õnnestus kõik ära vahetada: " << boolalpha << m.vahetaNupud(*(new vector<char>{'E'})) << "\n";


    return 0;
}

Mang::Mang() : m_kott(make_shared<Kott>()),
               m_laud(Laud()),
               m_praeguse_mangija_id(0),
               m_vahele_jaetud_kaikude_arv(0) {
    string mangijate_arv = kysiMangijateArv();
    kysiMangijateNimed(stoi(mangijate_arv));
}

void Mang::jargmineKaik() {
    shared_ptr<Mangija> praegune_mangija = jargmineMangija();

    cout << m_laud << "\n";
    cout << *praegune_mangija << "\n";

    bool oige_vastus = false;
    string vastus;

    while (true) {
        cout << "Sinu kord: " << praegune_mangija->getNimi()
             << "\nKas sa soovid käia sõna (S), käigu vahele jätta (J) või künalt tähti vahetada (V)? ";
        getline(cin, vastus);
        switch (toupper(vastus.c_str()[0])) {
            case 'S':
                if (!kaiSona(praegune_mangija, oige_vastus)) // sõna ei õnnestunud käia
                    continue;
                break;
            case 'J':
                // kui kõik mängijad on kaks korda järjest vahele jätnud, saab mäng läbi ehk mängijate arv * 2 käiku
                jataVahele(praegune_mangija, oige_vastus);
                break;
            case 'V':
                vahetaTahti(praegune_mangija, oige_vastus);
                break;
            default:
                cerr << "\nVale sisend!\n";
        }
        if (oige_vastus) {
            m_vahele_jaetud_kaikude_arv = 0;
            break;
        }
    }
}

shared_ptr<Mangija> Mang::jargmineMangija() {
    return m_mangijad[m_praeguse_mangija_id++ % m_mangijad.size()];
}

string Mang::kysiMangijateArv() {
    string mangijate_arv;
    while (true) {
        try {
            cout << "Sisesta mängijate arv: ";
            getline(cin, mangijate_arv);
            if (stoi(mangijate_arv) < 1 || stoi(mangijate_arv) > 4)
                throw invalid_argument("Arv ei sobi!");
            break;
        } catch (exception e) {
            cerr << "\nSisesta täisarv vahemikus 1--4!";
            continue;
        }
    }
    return mangijate_arv;
}

void Mang::kysiMangijateNimed(int mangijate_arv) {
    string nimi;
    for (int i = 0; i < mangijate_arv; i++) {
        cout << "Sisesta mängija nimi: ";
        getline(cin, nimi);
        m_mangijad[i] = make_shared<Mangija>(m_kott, nimi);
    }
}

string Mang::kysiKoordinaadid() {
    string koordinaadid;
    while (true) {
        cout << "Sisesta esimese tähe koordinaadid (A1): ";
        getline(cin, koordinaadid);
        if (toupper(koordinaadid[0]) < 'A' ||
            toupper(koordinaadid[0]) > 'O' ||
            koordinaadid[1] - 48 < 0 ||
            koordinaadid[1] - 48 > 9 ||
            koordinaadid.size() > 2 &&
            koordinaadid[1] - 48 != 1 &&
            (koordinaadid[2] - 48 < 0 ||
             koordinaadid[2] - 48 > 5)) {
            cerr << "\nKoordinaat on vale!\n";
            continue;
        }
        break;
    }
    return koordinaadid;
}

string Mang::kysiSuund() {
    string suund;
    while (true) {
        cout << "Sisesta suund (alla - A, paremale - P): ";
        getline(cin, suund);
        if (suund != "A" && suund != "P" &&
            suund != "a" && suund != "p") {
            cerr << "\nSuund on vale!\n";
            continue;
        }
        break;
    }
    return suund;
}

string Mang::kysiSona() {
    cout << "Sisesta käidav sõna, kui see ristub laual oleva sõnaga, märgi laual juba olevad tähed tärniga (*): ";
    string sona;
    getline(cin, sona);
    return sona;
}

bool Mang::kaiSona(const shared_ptr<Mangija> &mangija, bool &oige_vastus) {
    string koordinaadid = kysiKoordinaadid();
    string suund = kysiSuund();
    string vastus = kysiSona();

    if (vastus.empty())
        return true;

    shared_ptr<Kaik> kaik;
    try {
        kaik = make_shared<Kaik>(vastus, koordinaadid, suund);
    } catch (const invalid_argument &e) {
        cerr << "\nSõna positsioon ei ole korrektne!\n";
        return false;
    }

    if (!mangija->kasNupudKunal(kaik)) {
        cerr << "\nKõiki nuppe pole künal!\n";
        return false;
    }
//                cout << *kaik;

    int tulemus = m_laud.kontrolli(kaik);
    if (tulemus < 0) {
        cerr << "\nSelle sõna paigutus on vale või seda sõna pole sõnastikus!\n";
        return false;
    }

    cout << "Sinu käidud sõna (" << vastus << ") eest saadud punktid: " << tulemus << ".\n";

    mangija->lisaPunktid(tulemus);

    m_laud.lisaSonaLauale(kaik);

    mangija->eemaldaNupud(kaik);

    mangija->taidaKuna();

    cout << m_laud << "\n";
    cout << "Uus küna: " << *mangija->getKuna() << "\n";

    m_vahele_jaetud_kaikude_arv = 0;
    oige_vastus = true;
    return true;
}

void Mang::jataVahele(const shared_ptr<Mangija> &mangija, bool &oige_vastus) {
    cout << mangija->getNimi() << ", jätsid oma käigu vahele.\n";
    m_vahele_jaetud_kaikude_arv++;
    oige_vastus = true;
}

void Mang::vahetaTahti(const shared_ptr<Mangija> &mangija, bool &oige_vastus) {
    cout << "Sisesta vahetatavad tähed kokku kirjutatuna: ";
    string vahetatavad_tahed;
    getline(cin, vahetatavad_tahed);

    vector<char> tahed;
    for (char taht: vahetatavad_tahed)
        tahed.push_back(toupper(taht));

    if (!mangija->vahetaNupud(tahed)) {
        tahed.clear();
        cerr << "\nNuppe ei õnnestunud vahetada.\n";
        return;
    }

    tahed.clear();
    cout << "Uus küna: " << *mangija->getKuna() << "\n";

    m_vahele_jaetud_kaikude_arv = 0;
    oige_vastus = true;
}
