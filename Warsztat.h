#pragma once
#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <map>
#include "Osoba.h"
#include "Naprawa.h"

struct Komparator
{
    bool operator()(const std::string& string1, const std::string string2) const
    {
        return string1 < string2;
    }
};

class Osoba;
class Naprawa;
class Warsztat
{
    std::vector<Naprawy::Naprawa*> naprawy;
    std::map<std::string, Naprawy::Naprawa*, Komparator> naprawy_map;
    std::vector<Osoby::Osoba*> osoby;
    static Warsztat* warsztat;
    size_t ilosc_napraw = 0;
    size_t ilosc_osob = 0;
    size_t ilosc_klientow = 0;
    size_t ilosc_mechanikow = 0;
public:
    Warsztat();
    Warsztat(const Warsztat&) = delete;
    ~Warsztat();
    static Warsztat* get_warsztat();
    void dodaj(Osoby::Osoba* nowy);
    void usun(size_t index);
    void dodaj_klienta();
    void usun_klienta();
    void zatrudnij_mechanika();
    void dodaj_naprawe(Naprawy::Naprawa* nowaNaprawa);
    void usun_naprawe(Samochod* samochod);
    Naprawy::Naprawa* stworz_naprawe();
    Naprawy::Naprawa* znajdz_naprawe(const std::string& numerRejestracyjny) const;
    void wypisz_naprawy_map();
    void wypisz_naprawy();
    friend std::ostream& operator<<(std::ostream& output, const Warsztat& warsztat);
    Osoby::Klient* get_klient() const;
    Osoby::Mechanik* get_mechanik() const;
    Osoby::Osoba* getOsoba(size_t i) const
    {
        return osoby[i];
    }
    Naprawy::Naprawa* getNaprawa(size_t i) const
    {
        return naprawy[i];
    }
    size_t getIloscNapraw() const
    {
        return ilosc_napraw;
    }
};