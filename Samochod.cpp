#include <iostream>
#include <string>
#include <random>
#include <vector>
#include "Samochod.h"

std::ostream& operator<<(std::ostream& output, const Samochod& samochod)
{
    output << "Rejestracja: " << samochod.getRejestracja() << " Marka: " << samochod.getMarka() << " Rok produkcji: " << samochod.getRokProdukcji() << " Przebieg: "
        << samochod.getPrzebieg();
    return output;
}

std::istream& operator>>(std::istream& input, Samochod& samochod)
{
    input >> samochod.rejestracja;
    input >> samochod.marka;
    input >> samochod.rok_produkcji;
    input >> samochod.przebieg;

    return input;
}

void Samochod::pokaz() const
{
    std::cout << "Klient " << getKlient()->getGodnosc() << " Samochod " << rejestracja << std::endl;
}