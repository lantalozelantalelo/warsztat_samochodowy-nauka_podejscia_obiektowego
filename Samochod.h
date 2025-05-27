#pragma once
#include <iostream>
#include <string>
#include <random>
#include <vector>
#include "Osoba.h"
#include "Naprawa.h"

class Osoba;
class Klient;
class Naprawa;
namespace Osoby { class Klient; }
namespace Naprawy { class Naprawa; }
class Samochod
{
    std::string rejestracja;
    std::string marka;
    size_t rok_produkcji = 0;
    size_t przebieg = 0;
    Osoby::Klient* klient = nullptr;
    Naprawy::Naprawa* naprawa = nullptr;
public:
    void setRejestracja(const std::string& rejestracja1)
    {
        rejestracja = rejestracja1;
    }
    std::string getRejestracja() const
    {
        return rejestracja;
    }
    void setMarka(const std::string& marka1)
    {
        marka = marka1;
    }
    std::string getMarka() const
    {
        return marka;
    }
    void setRokProdukcji(const size_t& rok_produkcji1)
    {
        rok_produkcji = rok_produkcji1;
    }
    size_t getRokProdukcji() const
    {
        return rok_produkcji;
    }
    void setPrzebieg(const size_t& przebieg1)
    {
        przebieg = przebieg1;
    }
    size_t getPrzebieg() const
    {
        return przebieg;
    }
    void setKlient(Osoby::Klient* const klient1)
    {
        klient = klient1;
    }
    void setKlient(Osoby::Klient*&& klient1)
    {
        klient = klient1;
    }
    Osoby::Klient* getKlient() const
    {
        return klient;
    }
    void setNaprawa(Naprawy::Naprawa* naprawa1)
    {
        naprawa = naprawa1;
    }
    Naprawy::Naprawa* getNaprawa()
    {
        return naprawa;
    }
    void pokaz() const;
    Samochod(std::string rejestracja1 = "", std::string marka1 = "", size_t rok_produkcji1 = 0, size_t przebieg1 = 0, Osoby::Klient* klient1 = nullptr)
    {
        rejestracja = rejestracja1;
        marka = marka1;
        rok_produkcji = rok_produkcji1;
        przebieg = przebieg1;
        klient = klient1;
    }
    friend std::ostream& operator<<(std::ostream& output, const Samochod& samochod);
    friend std::istream& operator>>(std::istream& input, Samochod& samochod);
};