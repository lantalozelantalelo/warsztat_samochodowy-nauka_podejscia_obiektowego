#pragma once
#include <iostream>
#include <string>
#include <random>
#include <vector>
#include "Samochod.h"
#include "Naprawa.h"

class Samochod;
class Naprawa;
namespace Osoby {
    class Osoba
    {
        std::string godnosc = "";
        int32_t nr_telefonu = 0;
        int64_t pesel = 0;
        size_t id = 0;

    protected:

        size_t typ = 0;

    public:

        Osoba(std::string godnosc1 = "", int32_t nr_telefonu1 = 0, int64_t pesel1 = 0)
        {
            godnosc = godnosc1;
            nr_telefonu = nr_telefonu1;
            pesel = pesel1;
        }
        void setGodnosc(std::string& godnosc1)
        {
            godnosc = godnosc1;
        }
        std::string getGodnosc() const
        {
            return godnosc;
        }
        void setNrTelefonu(int32_t nr_telefonu1)
        {
            nr_telefonu = nr_telefonu1;
        }
        int32_t getNrTelefonu() const
        {
            return nr_telefonu;
        }
        void setPesel(int64_t pesel1)
        {
            pesel = pesel1;
        }
        int64_t getPesel() const
        {
            return pesel;
        }
        void setId(size_t id1)
        {
            id = id1;
        }
        size_t getId() const
        {
            return id;
        }
        void set_typ(size_t t) { typ = t; }
        inline size_t get_typ() { return typ; }
        void genData(Osoba* osoba);
        friend std::ostream& operator<<(std::ostream& output, const Osoba& osoba);
        virtual void diagnoza() = 0;
    };
    class Klient : public Osoba
    {
        size_t liczba_samochodow = 0;
        std::vector<Samochod*> samochody;
    public:
        ~Klient();
        const std::vector<Samochod*>& getSamochody() const
        {
            return samochody;
        }
        Samochod* getSamochody1(size_t i) const
        {
            return samochody[i];
        }
        size_t getLiczbaSamochodow() const
        {
            return liczba_samochodow;
        }
        void setLiczbaSamochodow(size_t liczba1)
        {
            liczba_samochodow = liczba1;
        }
        void gen_data(Klient* klient);
        void gen_data1(Klient* klient, size_t nrsamochodu);
        void stworz(Klient* klient);
        void sparsujKlient(Klient* klient, std::string tekst);
        void sparsujGetline(Klient* klient, std::string tekst);
        void print(Klient** klienci, size_t rozmiar);
        friend std::ostream& operator<<(std::ostream& output, const Klient& klient);
        void diagnoza() override;
    };
    class Mechanik : public Osoba
    {
        size_t ilosc_napraw = 0;
        uint32_t placa = 4000;
        std::vector<Naprawy::Naprawa*> naprawy;

    public:

        ~Mechanik();
        void gen_data(Mechanik* mechanik);
        void setNaprawa(Naprawy::Naprawa* naprawa1, size_t i)
        {
            naprawy[i] = naprawa1;
        }
        Naprawy::Naprawa* getNaprawa(size_t i)
        {
            return naprawy[i];
        }
        void setIloscNapraw(size_t ilosc1)
        {
            ilosc_napraw = ilosc1;
        }
        size_t getIloscNapraw() const
        {
            return ilosc_napraw;
        }
        int32_t getPlaca() const
        {
            return placa;
        }
        void dodaj_naprawe(Naprawy::Naprawa* nowy);
        friend std::ostream& operator<<(std::ostream& output, const Mechanik& mechanik);
        void obliczPremie();
        void diagnoza() final;
    };
    std::ostream& operator<<(std::ostream& output, const Klient& klient);
    std::ostream& operator<<(std::ostream& output, const Mechanik& mechanik);
    std::ostream& operator<<(std::ostream& output, const Osoba& osoba);
}