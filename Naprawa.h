#pragma once
#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <algorithm>
#include <iterator>
#include <memory>
#include "Osoba.h"
#include "Samochod.h"
#include "Dane.h"

class Osoba;
class Mechanik;
class Samochod;
namespace Osoby { class Mechanik; }
namespace Naprawy {
    class Naprawa
    {
        class Czesc
        {
            friend class Naprawa;
            friend struct SumaCen;
            std::string nazwa;
            size_t cena = 0;
            double suma = 0;
        public:
            std::string getNazwa() const
            {
                return nazwa;
            }
            size_t getCena() const
            {
                return cena;
            }
            void setNazwa(const std::string& nazwa1)
            {
                nazwa = nazwa1;
            }
            void setCena(const size_t& cena1)
            {
                cena = cena1;
            }
            Czesc(const std::string& nazwa1, size_t cena1 = 0) : nazwa{ nazwa1 }, cena{ cena1 } {}
            friend std::ostream& operator<<(std::ostream& output, const Czesc& czesc)
            {
                std::cout << "nazwa: " << czesc.nazwa << " cena: " << czesc.cena;
                return output;
            }
        };
        size_t ilosc_czesci = 0;
        mutable double koszt = 0;
        std::vector<std::unique_ptr<Czesc>> czesci;
        Samochod* samochod = nullptr;
        Osoby::Mechanik* mechanik = nullptr;
        void stworzCzesci();
        friend struct SumaCen;

    public:

        Naprawa(Samochod* samochod1) : samochod(samochod1) {}
        ~Naprawa();
        void pokaz() const;
        void dodajNaprawe();
        void dodajCzesc();
        void usunCzesc(size_t indeksCzesci);
        double sumaCzesci();
        double sredniaCzesci();
        void posortujCzesciPoCenie();
        double kosztNaprawy();
        void setIlosc(const size_t& ilosc_czesci1)
        {
            ilosc_czesci = ilosc_czesci1;
        }
        size_t getIlosc() const
        {
            return ilosc_czesci;
        }
        Samochod* getSamochod() const
        {
            return samochod;
        }
        Czesc* getCzesc(size_t i) const
        {
            return czesci[i].get();
        }
        void setKoszt(const size_t& koszt1) const
        {
            koszt = koszt1;
        }
        double getKoszt() const
        {
            return koszt;
        }
        void setMechanik(Osoby::Mechanik* mechanik1)
        {
            mechanik = mechanik1;
        }
        Osoby::Mechanik* getMechanik() const
        {
            return mechanik;
        }
        friend std::ostream& operator<<(std::ostream& output, const Naprawa& naprawa);
    };
    std::ostream& operator<<(std::ostream& output, const Naprawa& naprawa);

    struct SumaCen
    {
        double suma;
        SumaCen() : suma(0) {}
        void operator()(const std::unique_ptr<Naprawa::Czesc>& czesc)
        {
            suma += czesc->getCena();
        }
    };
}

