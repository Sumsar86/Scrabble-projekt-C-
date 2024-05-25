#include "Mang.h"

// Kui uus sõna panna rea lõppu, kas see läheb järgmisele reale
int main() {
    Mang mang{};
    shared_ptr<Mangija> praegune_mangija;
    while (!mang.kasMangLabi(praegune_mangija)) {
        praegune_mangija = mang.jargmineMangija();
        mang.jargmineKaik(praegune_mangija);
    }
    mang.lopetaMang(praegune_mangija);

    return 0;
}

Mang::Mang() : m_kott(make_shared<Kott>()),
               m_laud(Laud()),
               m_praeguse_mangija_id(0),
               m_vahele_jaetud_kaikude_arv(0) {
    string mangijate_arv = kysiMangijateArv();
    kysiMangijateNimed(stoi(mangijate_arv));
}

void Mang::jargmineKaik(const shared_ptr<Mangija> &mangija) {
    cout << m_laud;
    cout << *mangija << "\n\n";

    bool oige_vastus = false;
    string vastus;

    while (true) {
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
        cout << "Sinu kord: ";
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(2));
        cout << mangija->getNimi();
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
        cout << "\nKas sa soovid käia sõna (";
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(2));
        cout << "S";
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
        cout << "), käigu vahele jätta (";
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(2));
        cout << "J";
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
        cout << ") või künalt tähti vahetada (";
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(2));
        cout << "V";
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
        cout << ")? ";
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(7));

        getline(cin, vastus);
        switch (toupper(vastus.c_str()[0])) {
            case 'S':
                if (!kaiSona(mangija, oige_vastus)) // sõna ei õnnestunud käia
                    continue;
                m_vahele_jaetud_kaikude_arv = 0;
                oige_vastus = true;
                break;
            case 'J':
                jataVahele(mangija, oige_vastus);
                m_vahele_jaetud_kaikude_arv++;
                oige_vastus = true;
                break;
            case 'V':
                if (!vahetaTahti(mangija, oige_vastus))
                    continue;
                m_vahele_jaetud_kaikude_arv++;
                oige_vastus = true;
                break;
            default:
                SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(4));
                cout << "\nVale sisend!\n";
                SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(7));
        }
        if (oige_vastus)
            break;
    }
}

shared_ptr<Mangija> Mang::jargmineMangija() {
    return m_mangijad[m_praeguse_mangija_id++ % m_mangijad.size()];
}

string Mang::kysiMangijateArv() {
    string mangijate_arv;
    while (true) {
        try {
            SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
            cout << "Sisesta mängijate arv: ";
            SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(7));
            getline(cin, mangijate_arv);
            if (stoi(mangijate_arv) < 1 || stoi(mangijate_arv) > 4)
                throw invalid_argument("Arv ei sobi!");
            break;
        } catch (exception e) {
            SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(4));
            cout << "\nSisesta täisarv vahemikus 1 kuni 4!";
            SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(7));
            continue;
        }
    }
    return mangijate_arv;
}

void Mang::kysiMangijateNimed(int mangijate_arv) {
    string nimi;
    for (int i = 0; i < mangijate_arv; i++) {
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
        cout << "Sisesta mängija nimi: ";
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(7));

        getline(cin, nimi);
        m_mangijad[i] = make_shared<Mangija>(m_kott, nimi);
    }
}

string Mang::kysiKoordinaadid() {
    string koordinaadid;
    while (true) {
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
        cout << "Sisesta esimese tähe koordinaadid (näiteks: ";
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(2));
        cout << "A1";
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
        cout << "): ";
        getline(cin, koordinaadid);
        if (toupper(koordinaadid[0]) < 'A' ||
            toupper(koordinaadid[0]) > 'O' ||
            koordinaadid[1] - 48 < 0 ||
            koordinaadid[1] - 48 > 9 ||
            koordinaadid.size() > 2 &&
            koordinaadid[1] - 48 != 1 &&
            (koordinaadid[2] - 48 < 0 ||
             koordinaadid[2] - 48 > 5)) {
            SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(4));
            cout << "\nKoordinaat on vale!\n";
            SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(7));
            continue;
        }
        break;
    }
    return koordinaadid;
}

string Mang::kysiSuund() {
    string suund;
    while (true) {
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
        cout << "Sisesta suund (alla - ";
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(2));
        cout << "A";
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
        cout << ", paremale - ";
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(2));
        cout << "P";
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
        cout << "): ";
        getline(cin, suund);
        if (suund != "A" && suund != "P" &&
            suund != "a" && suund != "p") {
            SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(4));
            cout << "\nSuund on vale!\n";
            SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(7));
            continue;
        }
        break;
    }
    return suund;
}

string Mang::kysiSona() {
    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
    cout << "Sisesta käidav sõna, kui see ristub laual oleva sõnaga, märgi laual juba olevad tähed tärniga (";
    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(2));
    cout << "*";
    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
    cout << "): ";
    string sona;
    getline(cin, sona);
    return sona;
}

bool Mang::kaiSona(const shared_ptr<Mangija> &mangija, bool &oige_vastus) {
    string koordinaadid = kysiKoordinaadid();
    string suund = kysiSuund();
    string vastus = kysiSona();

    if (vastus.empty())
        return false;

    shared_ptr<Kaik> kaik;
    try {
        kaik = make_shared<Kaik>(vastus, koordinaadid, suund);
    } catch (const invalid_argument &e) {
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(4));
        cout << "\nSõna positsioon ei ole korrektne!\n";
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(7));
        return false;
    }

    if (!mangija->kasNupudKunal(kaik)) {
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(4));
        cout << "\nKõiki nuppe pole künal!\n";
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(7));
        return false;
    }

    int tulemus = m_laud.kontrolli(kaik);
    if (tulemus < 0) {
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(4));
        cout << "\nSelle sõna paigutus on vale või seda sõna pole sõnastikus!\n";
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(7));
        return false;
    }

    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
    cout << "\nSinu käidud sõna (";
    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(2));
    cout << vastus;
    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
    cout << ") eest saadud punktid: ";
    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(2));
    cout << tulemus;
    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
    cout << ".\n";

    mangija->lisaPunktid(tulemus);

    m_laud.lisaSonaLauale(kaik);

    mangija->eemaldaNupud(kaik);

    mangija->taidaKuna();

    cout << m_laud << "\n";
    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
    cout << "Uus küna: " << *mangija->getKuna() << "\n";

    return true;
}

void Mang::jataVahele(const shared_ptr<Mangija> &mangija, bool &oige_vastus) {
    cout << "\n";
    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(2));
    cout << mangija->getNimi();
    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
    cout << ", jätsid oma käigu vahele.\n";
}

bool Mang::vahetaTahti(const shared_ptr<Mangija> &mangija, bool &oige_vastus) {
    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
    cout << "Sisesta vahetatavad tähed kokku kirjutatuna: ";
    string vahetatavad_tahed;
    getline(cin, vahetatavad_tahed);

    vector<char> tahed;
    for (char taht: vahetatavad_tahed)
        tahed.push_back(toupper(taht));

    if (tahed.empty())
        return false;

    if (!mangija->vahetaNupud(tahed)) {
        tahed.clear();
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(4));
        cout << "\nNuppe ei õnnestunud vahetada.\n";
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(7));
        return false;
    }

    tahed.clear();
    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
    cout << "Uus küna: " << *mangija->getKuna() << "\n";
    return true;
}

bool Mang::kasMangLabi(const shared_ptr<Mangija> &mangija) {
    if (!mangija)
        return false;
    // kui kõik mängijad on kaks korda järjest vahele jätnud, saab mäng läbi ehk mängijate arv * 2 käiku
    if (m_vahele_jaetud_kaikude_arv >= m_mangijad.size() * 2)
        return true;
    if (mangija->getKuna()->kasTyhi() && m_kott->kas_on_tuhi())
        return true;

    return false;
}

void Mang::lopetaMang(const shared_ptr<Mangija> &mangija) {
    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
    cout << "\n<~~~~~~~~~~~~~~~| ";
    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(2));
    cout << "Mäng sai läbi";
    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
    cout << " |~~~~~~~~~~~~~~~>\n";

    int mangija_kaotatud_punktid;
    if (m_vahele_jaetud_kaikude_arv != 0) {
        for (const auto &p: m_mangijad) {
            mangija_kaotatud_punktid = p.second->getKuna()->kunaNuppudePunktid();
            p.second->eemaldaPunktid(mangija_kaotatud_punktid);
        }
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
        cout << "\nKahe vooru jooksul pole ükski mängija käiku teinud.\n";
        trykiTulemused();
        cout << "\n<~~~~~~~~~~~~~| ";
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(2));
        cout << "Aitäh mängimast!";
        SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
        cout << " |~~~~~~~~~~~~~~>\n";
        return;
    }

    int teiste_mangijate_punktid = 0;
    for (const auto &p: m_mangijad) {
        if (p.second != mangija) {
            mangija_kaotatud_punktid = p.second->getKuna()->kunaNuppudePunktid();
            teiste_mangijate_punktid += mangija_kaotatud_punktid;
            p.second->eemaldaPunktid(mangija_kaotatud_punktid);
        }
    }
    mangija->lisaPunktid(teiste_mangijate_punktid);

    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
    cout << "\nMängijal ";
    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(2));
    cout << mangija->getNimi();
    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
    cout << " said nupud otsa.\n";

    trykiTulemused();

    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
    cout << "\n<~~~~~~~~~~~~~| ";
    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(2));
    cout << "Aitäh mängimast!";
    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
    cout << " |~~~~~~~~~~~~~~>\n";
}

void Mang::trykiTulemused() {
    vector<shared_ptr<Mangija>> mangijad;
    transform(m_mangijad.begin(), m_mangijad.end(), back_inserter(mangijad),
              [](const auto &p) { return p.second; });
    sort(mangijad.begin(), mangijad.end());

    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(15));
    cout << "\nTulemused on järgnevad:\n";
    for_each(mangijad.begin(), mangijad.end(), [](const auto &el) {
        cout << "  " << *el << "\n";
    });
}
