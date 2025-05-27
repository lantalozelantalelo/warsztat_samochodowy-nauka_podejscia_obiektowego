#include <iostream>
#include <string>
#include <random>
#include <vector>
#include "Osoba.h"
#include "Warsztat.h"
#include "Dane.h"

void Osoby::Mechanik::dodaj_naprawe(Naprawy::Naprawa* nowy)
{
    if (ilosc_napraw == 0)
    {
        naprawy.push_back(nowy);
    }
    else
    {
        std::vector<Naprawy::Naprawa*> temp(naprawy);
        temp.push_back(nowy);
        naprawy = temp;
    }
}

void Osoby::Mechanik::diagnoza()
{
    Naprawy::Naprawa* nowaNaprawa = Warsztat::get_warsztat()->stworz_naprawe();
    this->dodaj_naprawe(nowaNaprawa);
    this->setIloscNapraw(Warsztat::get_warsztat()->getIloscNapraw());
    nowaNaprawa->setMechanik(this);
}

void Osoby::Klient::diagnoza()
{
    double suma_cen = 0;
    double suma_kosztow = 0;
    for (size_t i = 0; i < Warsztat::get_warsztat()->getIloscNapraw(); i++)
    {
        for (size_t j = 0; j < getLiczbaSamochodow(); j++)
        {
            if (getSamochody1(j) == Warsztat::get_warsztat()->getNaprawa(i)->getSamochod())
            {
                suma_cen += Warsztat::get_warsztat()->getNaprawa(i)->sumaCzesci();
                suma_kosztow += Warsztat::get_warsztat()->getNaprawa(i)->getKoszt();
            }
        }
    }
    std::cout << "Suma cen czesci dla klienta " << getGodnosc() << " wynosi " << suma_cen << "zl" << std::endl;
    std::cout << "Suma kosztow napraw " << getGodnosc() << " wynosi " << suma_kosztow << "zl" << std::endl;
}

Osoby::Mechanik::~Mechanik()
{
    for (Naprawy::Naprawa* naprawa : naprawy)
    {
        delete naprawa;
    }
    ilosc_napraw = 0;
}

void Osoby::Mechanik::obliczPremie()
{
    static bool po_podwyzce0 = false;
    static bool po_podwyzce1 = false;
    if (ilosc_napraw > 4 && ilosc_napraw <= 10 && po_podwyzce0 == false)
    {
        placa += 1000;
        po_podwyzce0 = true;
        std::cout << "Placa z premia dla mechanika " << getGodnosc() << ": " << placa << std::endl;
    }
    else if (ilosc_napraw > 10 && po_podwyzce1 == false)
    {
        placa += 5000;
        po_podwyzce1 = true;
        std::cout << "Placa z premia dla mechanika " << getGodnosc() << ": " << placa << std::endl;
    }
    else std::cout << "Mechanik " << getGodnosc() << " nie dostal premii, a jego placa wynosi " << ": " << placa << std::endl;
}

std::ostream& Osoby::operator<<(std::ostream& output, const Klient& klient) 
{
    output << klient.getGodnosc() << " | Nr telefonu: " << klient.getNrTelefonu()
        << " | Liczba samochodow: " << klient.getLiczbaSamochodow() << std::endl;
    for (size_t i = 0; i < klient.getLiczbaSamochodow(); i++)
        output << *klient.getSamochody1(i) << std::endl;
    return output;
}

std::ostream& Osoby::operator<<(std::ostream& output, const Mechanik& mechanik) 
{
    output << mechanik.getGodnosc() << " | PESEL: " << mechanik.getPesel()
        << " | Nr telefonu: " << mechanik.getNrTelefonu()
        << " | Placa: " << mechanik.getPlaca()
        << " | Ilosc napraw: " << mechanik.getIloscNapraw() << std::endl;
    return output;
}

std::ostream& Osoby::operator<<(std::ostream& output, const Osoba& osoba) 
{
    if (const auto* klient_ptr = dynamic_cast<const Klient*>(&osoba))
        output << *klient_ptr;
    else if (const auto* mechanik_ptr = dynamic_cast<const Mechanik*>(&osoba)) 
        output << *mechanik_ptr;
    else
        output << "Nieznany typ osoby";
    return output;
}

/*
Klient& Osoby::Klient::operator=(const Osoby::Klient& right)
{
    if (this != &right)
    {
        this->Klient::~Klient();
        this->Klient::Klient(right);
    }

    return *this;
}

Klient::Klient(const Klient& right)
{
    godnosc = right.godnosc;
    nr_telefonu = right.nr_telefonu;
    liczba_samochodow = right.liczba_samochodow;
    samochody = new Samochod * [liczba_samochodow];
    for (size_t i = 0; i < liczba_samochodow; i++) {
        samochody[i] = new Samochod(*right.samochody[i]);
    }
}
*/
Osoby::Klient::~Klient()
{
    for (Samochod* samochod : samochody)
    {
        delete samochod;
    }
    liczba_samochodow = 0;
}

void Osoby::Osoba::genData(Osoby::Osoba* osoba)
{
    static std::random_device rd;
    static std::default_random_engine dfe(rd());
    static std::uniform_int_distribution<int> numDistImie(0, szImiona - 1);
    static std::uniform_int_distribution<int> numDistNazwisko(0, szNazwiska - 1);
    static std::uniform_int_distribution<int> nrtelDist(111111111, 999999999);
    static std::uniform_int_distribution<int64_t> peselDist(11111111111, 99999999999);

    size_t index_imienia = numDistImie(dfe);
    size_t index_nazwiska = numDistNazwisko(dfe);
    std::string imie = std::string(Imiona[index_imienia]);
    std::string nazwisko = std::string(Nazwiska[index_nazwiska]);
    duzaLitera(imie);
    duzaLitera(nazwisko);
    std::string godnosc = imie + " " + nazwisko;

    osoba->setGodnosc(godnosc);
}

void Osoby::Mechanik::gen_data(Osoby::Mechanik* mechanik)
{
    static std::random_device rd;
    static std::default_random_engine dfe(rd());
    static std::uniform_int_distribution<int> numDistImie(0, szImiona - 1);
    static std::uniform_int_distribution<int> numDistNazwisko(0, szNazwiska - 1);
    static std::uniform_int_distribution<int> nrtelDist(111111111, 999999999);
    static std::uniform_int_distribution<int64_t> peselDist(11111111111, 99999999999);

    size_t index_imienia = numDistImie(dfe);
    size_t index_nazwiska = numDistNazwisko(dfe);
    std::string imie = std::string(Imiona[index_imienia]);
    std::string nazwisko = std::string(Nazwiska[index_nazwiska]);
    duzaLitera(imie);
    duzaLitera(nazwisko);
    std::string godnosc = imie + " " + nazwisko;

    mechanik->setGodnosc(godnosc);
    mechanik->setNrTelefonu(nrtelDist(dfe));
    mechanik->setPesel(peselDist(dfe));
}

void Osoby::Klient::gen_data(Osoby::Klient* klient)
{
    static std::random_device rd;
    static std::default_random_engine dfe(rd());
    static std::uniform_int_distribution<int> numDistImie(0, szImiona - 1);
    static std::uniform_int_distribution<int> numDistNazwisko(0, szNazwiska - 1);
    static std::uniform_int_distribution<int> nrtelDist(111111111, 999999999);
    static std::uniform_int_distribution<int> l_samochodowDist(1, 3);

    size_t index_imienia = numDistImie(dfe);
    size_t index_nazwiska = numDistNazwisko(dfe);
    std::string imie = std::string(Imiona[index_imienia]);
    std::string nazwisko = std::string(Nazwiska[index_nazwiska]);
    duzaLitera(imie);
    duzaLitera(nazwisko);
    std::string godnosc = imie + " " + nazwisko;

    klient->setGodnosc(godnosc);
    klient->setNrTelefonu(nrtelDist(dfe));
    klient->liczba_samochodow = l_samochodowDist(dfe);
}

void Osoby::Klient::gen_data1(Osoby::Klient* klient, size_t nrsamochodu)
{
    static std::random_device rd;
    static std::default_random_engine dfe(rd());
    static std::uniform_int_distribution<int> numDistRejestracja(0, szRejestracja - 1);
    static std::uniform_int_distribution<int> rejestracjaDist(10000, 99999);
    static std::uniform_int_distribution<int> numDistMarka(0, szMarka - 1);
    static std::uniform_int_distribution<int> rokprodukcjiDist(1980, 2024);
    static std::uniform_int_distribution<int> przebiegDist(0, 1000000);

    size_t index_rejestracji = numDistRejestracja(dfe);
    size_t index_marki = numDistMarka(dfe);

    klient->samochody[nrsamochodu]->setRejestracja(std::string(Rejestracja[index_rejestracji]) + std::to_string(rejestracjaDist(dfe)));
    klient->samochody[nrsamochodu]->setMarka(std::string(Marka[index_marki]));
    klient->samochody[nrsamochodu]->setRokProdukcji(rokprodukcjiDist(dfe));
    klient->samochody[nrsamochodu]->setPrzebieg(przebiegDist(dfe));
}

void Osoby::Klient::sparsujKlient(Osoby::Klient* klient, std::string tekst)
{
    size_t pozycja = tekst.find("Klient ");
    if (pozycja != std::string::npos) {
        pozycja += 7;
        size_t pozycja1 = tekst.find(" ", pozycja);
        pozycja1 += 1;
        size_t pozycja2 = tekst.find(" ", pozycja1);
        std::string godnosc = tekst.substr(pozycja, pozycja2 - pozycja);
        klient->setGodnosc(godnosc);
        pozycja = pozycja2 + 1;
        pozycja1 = tekst.find(" ", pozycja);
        klient->setNrTelefonu(std::stoi(tekst.substr(pozycja, pozycja1 - pozycja)));
    }
}

void Osoby::Klient::sparsujGetline(Osoby::Klient* klient, std::string tekst)
{
    size_t pozycja = 0;
    size_t pozycja1 = tekst.find(" ", pozycja);
    pozycja1 += 1;
    size_t pozycja2 = tekst.find(" ", pozycja1);
    std::string godnosc = tekst.substr(pozycja, pozycja2 - pozycja);
    klient->setGodnosc(godnosc);
    pozycja = pozycja2 + 1;
    pozycja1 = tekst.find(" ", pozycja);
    klient->setNrTelefonu(std::stoi(tekst.substr(pozycja, pozycja1 - pozycja)));
}

void Osoby::Klient::print(Osoby::Klient** klienci, size_t rozmiar)
{
    std::cout << "<========== klienci ==========>" << std::endl;
    for (size_t ind = 0; ind < rozmiar; ind++) {
        std::cout << klienci[ind]->getGodnosc() << "\t" << klienci[ind]->getNrTelefonu() << "\t" << klienci[ind]->liczba_samochodow << std::endl;
    }
}

void Osoby::Klient::stworz(Osoby::Klient* klient)
{
    samochody.resize(liczba_samochodow);
    for (size_t i = 0; i < liczba_samochodow; i++)
    {
        samochody[i] = new Samochod;
        samochody[i]->setKlient(klient);
        gen_data1(klient, i);
    }
}

