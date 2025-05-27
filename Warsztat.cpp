#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <map>
#include "Warsztat.h"
#include "Osoba.h"
#include "Naprawa.h"
#include "Dane.h"

Warsztat* Warsztat::warsztat = Warsztat::get_warsztat();

Warsztat* Warsztat::get_warsztat()
{
    if (!warsztat) {
        warsztat = new Warsztat;
    }
    return warsztat;
}

Warsztat::Warsztat() : ilosc_klientow{ generujLiczbeLosowa(2, 4) }
{
    size_t id = 0;
    for (size_t ind = 0; ind < ilosc_klientow; ind++)
    {
        Osoby::Klient* klient = new Osoby::Klient;
        klient->gen_data(klient);
        klient->stworz(klient);
        dodaj(klient);
        klient->set_typ(0);
        klient->setId(id);
        id++;
    }
    ilosc_osob = ilosc_klientow;
}

Warsztat::~Warsztat()
{
    if (!warsztat) delete warsztat;
    warsztat = nullptr;
    for (Naprawy::Naprawa* naprawa : naprawy)
        delete naprawa;
    for (Osoby::Osoba* osoba : osoby)
        delete osoba;
}

void Warsztat::dodaj(Osoby::Osoba* nowy)
{
    osoby.push_back(nowy);
}

void Warsztat::usun(size_t index)
{
    if (index < osoby.size())
    {
        delete osoby[index];
        osoby.erase(osoby.begin() + index);
    }
    else
    {
        std::cout << "ERROR: Index jest nieprawidlowy ! " << std::endl;
    }
}

void Warsztat::dodaj_klienta()
{
    size_t id = ilosc_klientow;
    Osoby::Klient* klient = new Osoby::Klient;
    klient->gen_data(klient);
    klient->stworz(klient);
    dodaj(klient);
    klient->set_typ(0);
    klient->setId(id);
    ilosc_klientow++;
    ilosc_osob++;
}

Naprawy::Naprawa* Warsztat::stworz_naprawe()
{
    Osoby::Klient* klient = get_klient();
    if (klient != nullptr)
    {
        size_t index_samochodu = generujLiczbeLosowa(0, klient->getLiczbaSamochodow() - 1);
        Naprawy::Naprawa* nowaNaprawa = new Naprawy::Naprawa(klient->getSamochody1(index_samochodu));
        nowaNaprawa->dodajNaprawe();
        nowaNaprawa->kosztNaprawy();
        klient->getSamochody1(index_samochodu)->setNaprawa(nowaNaprawa);
        dodaj_naprawe(nowaNaprawa);
        return nowaNaprawa;
    }
    else return nullptr;
}

void Warsztat::dodaj_naprawe(Naprawy::Naprawa* nowaNaprawa)
{
    const std::string& numerRejestracyjny = nowaNaprawa->getSamochod()->getRejestracja();
    if (naprawy_map.find(numerRejestracyjny) == naprawy_map.end())
    {
        naprawy.push_back(nowaNaprawa);
        naprawy_map[numerRejestracyjny] = nowaNaprawa;
        ilosc_napraw++;
    }
    else
    {
        std::cout << "Naprawa dla samochodu o numerze rejestracyjnym " << numerRejestracyjny << " juz istnieje." << std::endl;
    }
}

Naprawy::Naprawa* Warsztat::znajdz_naprawe(const std::string& numerRejestracyjny) const
{
    auto it = naprawy_map.find(numerRejestracyjny);
    if (it != naprawy_map.end())
    {
        return it->second;
    }
    return nullptr;
}

void Warsztat::usun_naprawe(Samochod* samochod)
{
    size_t i = 0;
    while (i < naprawy.size())
    {
        if (naprawy[i]->getSamochod() == samochod)
        {
            delete naprawy[i];
            naprawy.erase(naprawy.begin() + i);
        }
        else
        {
            ++i;
        }
    }
}

void Warsztat::usun_klienta()
{
    for (size_t i = 0; i < osoby.size(); ++i)
    {
        if (osoby[i]->get_typ() == 0 && osoby[i]->getId() == ilosc_klientow - 1)
        {
            for (size_t j = 0; j < dynamic_cast<Osoby::Klient*>(osoby[i])->getLiczbaSamochodow(); j++)
            {
                usun_naprawe(dynamic_cast<Osoby::Klient*>(osoby[i])->getSamochody1(j));
            }
            usun(i);
            ilosc_klientow--;
        }
    }
}

Osoby::Klient* Warsztat::get_klient() const
{
    size_t klient = 0;
    size_t ind = 0;
    for (size_t i = 0; i < osoby.size(); i++)
        if (osoby[i]->get_typ() == 0)
            klient++;
    if (klient > 1)
    {
        size_t numer = generujLiczbeLosowa(1, klient);
        klient = 0;
        for (size_t i = 0; i < osoby.size(); i++)
            if (osoby[i]->get_typ() == 0)
            {
                klient++;
                if (numer == klient)
                    ind = i;
            }
    }
    if (klient != 0)
    {
        if (klient == 1)
        {
            for (size_t i = 0; i < osoby.size(); i++)
            {
                if (osoby[i]->get_typ() == 0)
                {
                    ind = i;
                    break;
                }
            }
        }
        Osoby::Klient* klientPtr = dynamic_cast<Osoby::Klient*>(osoby[ind]);
        return klientPtr;
    }
    return nullptr;
}

Osoby::Mechanik* Warsztat::get_mechanik() const
{
    size_t mechanik = 0;
    size_t ind = 0;
    for (size_t i = 0; i < osoby.size(); i++)
        if (osoby[i]->get_typ() == 1)
            mechanik++;
    if (mechanik > 1)
    {
        size_t numer = generujLiczbeLosowa(1, mechanik);
        mechanik = 0;
        for (size_t i = 0; i < osoby.size(); i++)
            if (osoby[i]->get_typ() == 1)
            {
                mechanik++;
                if (numer == mechanik)
                    ind = i;
            }
    }
    if (mechanik != 0)
    {
        if (mechanik == 1)
        {
            for (size_t i = 0; i < osoby.size(); i++)
            {
                if (osoby[i]->get_typ() == 1)
                {
                    ind = i;
                    break;
                }
            }
        }
        Osoby::Mechanik* mechanikPtr = dynamic_cast<Osoby::Mechanik*>(osoby[ind]);
        return mechanikPtr;
    }
    return nullptr;
}

void Warsztat::zatrudnij_mechanika()
{
    Osoby::Mechanik* mechanik = new Osoby::Mechanik;
    mechanik->gen_data(mechanik);
    dodaj(mechanik);
    mechanik->set_typ(1);
    ilosc_osob++;
    ilosc_mechanikow++;
}

std::ostream& operator<<(std::ostream& output, const Warsztat& warsztat)
{
    output << "===================== Warsztat ====================================" << std::endl;
    output << "1.-------------------- Klienci --------------------" << std::endl;
    for (size_t i = 0; i < warsztat.osoby.size(); ++i)
    {
        if (warsztat.osoby[i]->get_typ() == 0)
        {
            output << *warsztat.osoby[i] << std::endl;
        }
    }
    output << "2.-------------------- Mechanicy --------------------" << std::endl;
    for (size_t i = 0; i < warsztat.osoby.size(); ++i)
    {
        if (warsztat.osoby[i]->get_typ() == 1)
        {
            output << *warsztat.osoby[i];
        }
    }
    return output;
}

void Warsztat::wypisz_naprawy()
{
    for (size_t i = 0; i < naprawy.size(); ++i)
    {
        naprawy[i]->getSamochod()->pokaz();
        naprawy[i]->pokaz();
    }
}

void Warsztat::wypisz_naprawy_map()
{
    for (const auto& para : naprawy_map)
    {
        std::cout << "Numer rejestracyjny: " << para.first << "\nNaprawa: " << *(para.second) << std::endl;
    }
}