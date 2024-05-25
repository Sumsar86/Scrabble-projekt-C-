#include "Kott.h"

// Eesti keelsetele reeglitele vastav kott, kus on õige arv kõiki nuppe.
// Š = $ (š = #), Ž = W, Õ = Q, Ä = X, Ö = C, Ü = Y, ? = tühi nupp
map<shared_ptr<Nupp>, int> Kott::m_vaike_kott = {
        {make_shared<Nupp>('A', 1),  10},
        {make_shared<Nupp>('B', 3),  1},
        {make_shared<Nupp>('D', 2),  4},
        {make_shared<Nupp>('E', 1),  9},
        {make_shared<Nupp>('F', 8),  1},
        {make_shared<Nupp>('G', 3),  2},
        {make_shared<Nupp>('H', 4),  2},
        {make_shared<Nupp>('I', 1),  9},
        {make_shared<Nupp>('J', 4),  2},
        {make_shared<Nupp>('K', 1),  5},
        {make_shared<Nupp>('L', 1),  5},
        {make_shared<Nupp>('M', 2),  4},
        {make_shared<Nupp>('N', 2),  4},
        {make_shared<Nupp>('O', 1),  5},
        {make_shared<Nupp>('P', 4),  2},
        {make_shared<Nupp>('R', 2),  2},
        {make_shared<Nupp>('S', 1),  8},
        {make_shared<Nupp>('$', 10), 1},
        {make_shared<Nupp>('Z', 10), 1},
        {make_shared<Nupp>('W', 10), 1},
        {make_shared<Nupp>('T', 1),  7},
        {make_shared<Nupp>('U', 1),  5},
        {make_shared<Nupp>('V', 3),  2},
        {make_shared<Nupp>('Q', 4),  2},
        {make_shared<Nupp>('X', 5),  2},
        {make_shared<Nupp>('C', 6),  2},
        {make_shared<Nupp>('Y', 5),  2},
        {make_shared<Nupp>('?', 0),  2}
};

// Konstruktor, mis võtab varasemalt defineeritud koti sisu. Lisaks seab valmis juhuarvu generaatori.
Kott::Kott(map<shared_ptr<Nupp>, int> nupud) : m_nupud(std::move(nupud)), m_nuppude_arv(0) {
    leiaNuppudeArv();
    looJuhuarvuGeneraator();
}

// Konstruktor, mis kasutab standardset koti sisu. Lisaks seab valmis juhuarvu generaatori.
Kott::Kott() : m_nupud(m_vaike_kott), m_nuppude_arv(0) {
    leiaNuppudeArv();
    looJuhuarvuGeneraator();
}

// Tagastab kotist juhusliku nupu. Kui nuppe pole tagastab nullptr.
shared_ptr<Nupp> Kott::getJuhuslikNupp() {
    if (m_nuppude_arv <= 0) {
        cerr << "Kott on juba tühi! Nuppu ei tagastatud.\n";
        return nullptr;
    }

    // https://stackoverflow.com/questions/27024269/select-random-element-in-an-unordered-map
    auto random_it = next(begin(m_nupud), m_juhuslik_arv(m_rng));
    while (random_it->second <= 0)
        random_it = next(begin(m_nupud), m_juhuslik_arv(m_rng));
    random_it->second--;
    m_nuppude_arv--;

    return random_it->first;
}

// Seab valmis juhuarvu generaatori.
void Kott::looJuhuarvuGeneraator() {
    // https://stackoverflow.com/questions/13445688/how-to-generate-a-random-number-in-c
    random_device rd;
    mt19937::result_type seed = rd() ^ (
            (mt19937::result_type)
                    chrono::duration_cast<chrono::seconds>(
                            chrono::system_clock::now().time_since_epoch()
                    ).count() +
            (mt19937::result_type)
                    chrono::duration_cast<chrono::microseconds>(
                            chrono::high_resolution_clock::now().time_since_epoch()
                    ).count());
    m_rng = mt19937(seed);
    m_juhuslik_arv = uniform_int_distribution<mt19937::result_type>(0, m_nupud.size() - 1);
}

// Koti ekraanile kuvamiseks.
ostream &operator<<(ostream &os, const Kott &kott) {
    os << "Kott: nuppude arv kotis = " << kott.m_nuppude_arv << ",\n{";
    for (const auto &it: kott.m_nupud)
        os << " " << *it.first << ": " << it.second << ", ";
    return os << "}";
}

// Arvutab kotis olevate nuppude arvu ja salvestab selle privaatsesse muutujasse m_nuppude_arv.
void Kott::leiaNuppudeArv() {
    for (const auto &it: m_nupud)
        m_nuppude_arv += it.second;
}

// Tagastab tõeväärtuse, kas kott on tühi või mitte.
bool Kott::kas_on_tuhi() const {
    return m_nuppude_arv <= 0;
}

// Lisab vana nupu kirje kotti ja annab uue juhusliku nupu.
shared_ptr<Nupp> Kott::vahetaNupp(const shared_ptr<Nupp> &vana_nupp) {
    shared_ptr<Nupp> uus_nupp = getJuhuslikNupp();
    m_nupud[vana_nupp]++;
    m_nuppude_arv++;
    return uus_nupp;
}

// Tagastab kotis olevate nuppude arvu.
int Kott::getNuppudeArv() const {
    return m_nuppude_arv;
}
