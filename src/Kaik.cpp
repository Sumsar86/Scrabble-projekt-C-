#include "Kaik.h"

// Käigu konstruktor, kui mõne nupu indeks on laualt väljas visatakse erind
Kaik::Kaik(const map<int, shared_ptr<Nupp>> &kaik) : m_kaik(kaik) {
    if (any_of(kaik.begin(), kaik.end(), [](const auto &el) { return (el.first < 0 || el.first > 224); })) {
        throw invalid_argument("Indeks mängulaualt väljas!\n");
    }
}

Kaik::Kaik(string sona, string koordinaadid, string suund) {
    int x = toupper(koordinaadid[0]) - 65;
    int y = stoi(koordinaadid.substr(1, koordinaadid.size() - 1)) - 1;
    int esimeneIndeks = y * 15 + x;

    switch (toupper(suund[0])) {
        case 'A':
            for (int i = 0; i < sona.size(); i++) {
                if (esimeneIndeks + i * 15 > 244)
                    throw invalid_argument("Indeks mängulaualt väljas!\n");
                if (sona[i] == '*')
                    continue;
                bool tyhi = false;
                if (sona[i] >= 97 && sona[i] <= 122 || sona[i] == '#')
                    tyhi = true;
                m_kaik[esimeneIndeks + i * 15] = make_shared<Nupp>(sona[i], TAHE_PUNKTID[sona[i]], tyhi);
            }
            break;
        case 'P':
            for (int i = 0; i < sona.size(); i++) {
                if (esimeneIndeks + i > 244)
                    throw invalid_argument("Indeks mängulaualt väljas!\n");
                if (sona[i] == '*')
                    continue;
                m_kaik[esimeneIndeks + i] = make_shared<Nupp>(sona[i], TAHE_PUNKTID[sona[i]]);
            }
            break;
    }
}

// Kontrollib, kas kõik käigus käidud nupud asuvad ühel real
bool Kaik::yhesReas() {
    if (m_kaik.size() < 2)
        return true;
    for (auto it = m_kaik.begin(); ++it != m_kaik.end();) {
        --it;
        if (it->first >= 225 || it->first < 0) {
            SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(4));
            cout << "\nNupp läheb laualt välja!";
            SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(7));
            return false;
        }
        if ((it->first / 15) != ((++it)->first / 15))
            return false;
    }
    return true;
}

// Kontrollib, kas kõik käigus käidud nupud asuvad ühes veerus
bool Kaik::yhesVeerus() {
    if (m_kaik.size() < 2)
        return true;
    for (auto it = m_kaik.begin(); ++it != m_kaik.end();) {
        --it;
        if (it->first >= 225 || it->first < 0) {
            SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(4));
            cout << "\nNupp läheb laualt välja!";
            SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(7));
            return false;
        }
        if ((it->first % 15) != ((++it)->first % 15))
            return false;
    }
    return true;
}

// Tagastab käigu kõige ülemise ja vasakpoolse nupu indekis ehk vähima indeksiga nupu indeksi
int Kaik::esimeneIndeks() {
    return m_kaik.begin()->first;
}

// Tagastab suurima ehk viimase indeksi
int Kaik::viimaneIndeks() {
    return (--m_kaik.end())->first;
}

// Kontrollib, kas käidavas käigus on vastava indeksiga ruudule nupp asetatud
bool Kaik::kasIndeksOlemas(int indeks) {
    return any_of(m_kaik.begin(), m_kaik.end(), [indeks](const auto &el) {
        return el.first == indeks;
    });
//    for (const auto& el : m_kaik){
//        if (el.first == indeks)
//            return true;
//    }
//    return false;
}

// Tagastab viida käidud nuppude indeksite vektorile
shared_ptr<vector<int>> Kaik::getIndeksid() const {
    shared_ptr<vector<int>> indeksid = make_shared<vector<int>>();
    for (const auto &el: m_kaik)
        indeksid->push_back(el.first);
    return indeksid;
}

// Tagastab viida Nupule, mille indeks sisestati. Kui sellel indeksil nuppu ei leidu, siis tagastatakse nullptr.
shared_ptr<Nupp> Kaik::getNupp(int indeks) {
    vector<int> indeksid = *getIndeksid();
    if (find(indeksid.begin(), indeksid.end(), indeks) != indeksid.end())
        return m_kaik[indeks];

    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(4));
    cout << "Viga! Ei leidnud nuppu: indeks = " << indeks << '\n';
    SetConsoleTextAttribute(H_CONSOLE, static_cast<WORD>(7));
    return nullptr;
}

map<int, shared_ptr<Nupp>> Kaik::getKaik() const {
    return m_kaik;
}

ostream &operator<<(ostream &os, const Kaik &kaik) {
    os << "Kaik: ";
    for (auto k: kaik.m_kaik)
        os << "indeks: " << k.first << ", täht: " << k.second->getTaht() << ", ";
    return os;
}
