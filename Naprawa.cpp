#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <algorithm>
#include <iterator>
#include <memory>
#include "Naprawa.h"
#include "Dane.h"

std::ostream& Naprawy::operator<<(std::ostream& output, const Naprawy::Naprawa& naprawa)
{
    output << "Ilosc czesci: " << naprawa.getIlosc() << std::endl;
    for (size_t i = 0; i < naprawa.getIlosc(); ++i)
    {
        output << "Czesc " << i + 1 << ": " << *naprawa.getCzesc(i) << std::endl;
    }
    output << "Koszt: " << naprawa.getKoszt() << std::endl;
    output << "Samochod: " << *naprawa.getSamochod() << std::endl;

    return output;
}

Naprawy::Naprawa::~Naprawa()
{
    delete samochod;
    samochod = nullptr;
    ilosc_czesci = 0;
}

void Naprawy::Naprawa::pokaz() const
{
    if (ilosc_czesci > 0)
    {
        std::cout << "=> Czesci do naprawy:" << std::endl;
        for (size_t i = 0; i < ilosc_czesci; ++i)
            std::cout << "Czesc : " << czesci[i]->nazwa << " " << czesci[i]->cena << "zl" << std::endl;
    }
}

void Naprawy::Naprawa::stworzCzesci()
{
    size_t ilosc = gen_dataIloscCzesci();
    setIlosc(ilosc);
    czesci.clear();
    std::generate_n(std::back_inserter(czesci), ilosc, []() {return std::make_unique<Czesc>(gen_dataNazwaCzesci(), gen_dataCenaCzesci());});
}

void Naprawy::Naprawa::dodajCzesc()
{
    czesci.push_back(std::make_unique<Czesc>(gen_dataNazwaCzesci(), gen_dataCenaCzesci()));
    ++ilosc_czesci;
}

void Naprawy::Naprawa::usunCzesc(size_t indeksCzesci)
{
    czesci.erase(std::next(czesci.begin(), indeksCzesci));
}

void Naprawy::Naprawa::dodajNaprawe()
{
    stworzCzesci();
}

double Naprawy::Naprawa::sumaCzesci()
{
    Naprawy::SumaCen suma_cen;
    std::for_each(czesci.begin(), czesci.end(), [&suma_cen](const std::unique_ptr<Naprawa::Czesc>& czesc) { suma_cen(czesc); });
    return suma_cen.suma;
}

double Naprawy::Naprawa::sredniaCzesci()
{
    double srednia = 0;
    srednia = sumaCzesci() / getIlosc();
    return srednia;
}

void Naprawy::Naprawa::posortujCzesciPoCenie()
{
    for (size_t i = 0; i < getIlosc(); i++)
    {
        for (size_t j = 1; j < getIlosc() - i; j++)
        {
            if (czesci[j - 1]->getCena() > czesci[j]->getCena())
                std::swap(czesci[j - 1], czesci[j]);
        }
    }
}

double Naprawy::Naprawa::kosztNaprawy()
{
    static std::random_device rd;
    static std::default_random_engine dfe(rd());
    static std::uniform_int_distribution<int> robociznaDist(50, 1000);
    koszt = sumaCzesci() + static_cast<double>(robociznaDist(dfe));

    return koszt;
}