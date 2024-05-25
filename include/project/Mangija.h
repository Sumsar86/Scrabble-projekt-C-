#pragma once

#include <memory>
#include <utility>
#include <ostream>
#include <iostream>
#include "Kuna.h"
//#include "Kott.h"
//#include "Kaik.h"

class Mangija {
private:
    shared_ptr<Kott> mp_kott;
    shared_ptr<Kuna> m_kuna;
    int m_punktid;
    string m_nimi;

public:
    explicit Mangija(shared_ptr<Kott> &kott, string nimi);

    bool vahetaNupud(vector<char> &tahed);

    bool kasNupudKunal(const shared_ptr<Kaik>& kaik);

    void eemaldaNupud(const shared_ptr<Kaik> &kaik);

    bool taidaKuna();

    friend ostream &operator<<(ostream &os, const Mangija &mangija);

    const string &getNimi() const;

    const shared_ptr<Kuna> &getKuna() const;

    void lisaPunktid(int punktid);

    void eemaldaPunktid(int punktid);

    bool operator<(const Mangija& other) const {
        return m_punktid < other.m_punktid;
    }
};
