#include "Mangija.h"

// Mängija konstruktor, küna suurus on 7
Mangija::Mangija(shared_ptr<Kott> &kott, string nimi) : mp_kott(kott),
                                                        m_kuna(make_shared<Kuna>(7, kott)),
                                                        m_punktid(0),
                                                        m_nimi(std::move(nimi)) {}

// Mängija ekraanile kuvamiseks
ostream &operator<<(ostream &os, const Mangija &mangija) {
    os << mangija.m_nimi << " punktid: " << mangija.m_punktid << ", " << *mangija.m_kuna;
    return os;
}

// Mängija nuppude vahetamiseks
bool Mangija::vahetaNupud(vector<char> &tahed) {
    return m_kuna->vahetaNupp(tahed, mp_kott);
}

const string &Mangija::getNimi() const {
    return m_nimi;
}

void Mangija::lisaPunktid(int punktid) {
    m_punktid += punktid;
}

bool Mangija::taidaKuna() {
    for (int i = m_kuna->mituNuppuKunal(); i < m_kuna->getMaxArvNuppeKunal(); i++) {
        shared_ptr<Nupp> uus_nupp = mp_kott->getJuhuslikNupp();
        if (uus_nupp == nullptr) {
            cerr << "Kott sai tühjaks. Küna ei saa rohkem täita.\n";
            return false;
        }
        m_kuna->lisaNupp(uus_nupp);
    }
    return true;
}

bool Mangija::kasNupudKunal(const shared_ptr<Kaik> &kaik) {
    return m_kuna->kasSisaldabKaiku(kaik);
}

const shared_ptr<Kuna> &Mangija::getKuna() const {
    return m_kuna;
}

void Mangija::eemaldaNupud(const shared_ptr<Kaik> &kaik) {
    m_kuna->eemaldaNupud(kaik);
}

void Mangija::eemaldaPunktid(int punktid) {
    m_punktid -= punktid;
}
