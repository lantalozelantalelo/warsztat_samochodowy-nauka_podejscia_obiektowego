#include <iostream>
#include <string>
#include <map>
#include <random>
#include <vector>
#include "Warsztat.h"

int main()
{
    std::string* Rekordy = nullptr;
    size_t rozmiar = 0;
    size_t wybor = 0;
    size_t ind = 0;
    size_t ind1 = 0;
    size_t num = 0;

    while (1)
    {
        std::cout << "\nMenu:\n";
        std::cout << "0 - Zakoncz dzialanie 1 - Wypisz dane 2 - Dodaj klienta 3 - Usun klienta 4 - Srednia cena czesci dla naprawy 5 - Posortuj czesci \n";
        std::cin >> wybor;

        switch (wybor)
        {
        case 1:
            std::cout << *Warsztat::get_warsztat();
            break;
        case 2:
            Warsztat::get_warsztat()->dodaj_klienta();
            break;
        case 3:
            Warsztat::get_warsztat()->usun_klienta();
            break;
        case 4:
            Warsztat::get_warsztat()->zatrudnij_mechanika();
            break;
        case 5:
            std::cout << "indeks: ";
            std::cin >> ind;
            //Warsztat::get_warsztat()->srednia_cena(Warsztat::get_warsztat()->getKlienciTab()->getKlient(ind), ind);
            ind = 0;
            break;
        case 6:
            //Warsztat::get_warsztat()->posortuj_czesci();
            std::cout << "Czesci zostaly posortowane" << std::endl;
            break;
        case 7:
            std::cout << "Indeks mechanika: ";
            std::cin >> ind1;
            std::cout << "Indeks klienta: ";
            std::cin >> ind;
            //Warsztat::get_warsztat()->klient_do_mechanika(ind, ind1);
            ind = 0;
            ind1 = 0;
            break;
        case 8:
            if (Warsztat::get_warsztat()->get_mechanik() != nullptr) Warsztat::get_warsztat()->get_mechanik()->diagnoza();
            break;
        case 9:
            Warsztat::get_warsztat()->wypisz_naprawy();
            break;
        case 10:
            Warsztat::get_warsztat()->get_klient()->diagnoza();
            break;
        case 11:
            Warsztat::get_warsztat()->get_mechanik()->obliczPremie();
            break;
        case 12:
            Warsztat::get_warsztat()->wypisz_naprawy_map();
            break;
        default: std::cout << "\n";
        }
        if (wybor == 0) break;
    }
    delete Rekordy;
    delete Warsztat::get_warsztat();

    return 0;
}
