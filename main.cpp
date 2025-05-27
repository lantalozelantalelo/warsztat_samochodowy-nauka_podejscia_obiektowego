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
        std::cout << "0 - Zakoncz dzialanie 1 - Wypisz dane 2 - Dodaj klienta 3 - Usun klienta 4 - Zatrudnij mechanika 5 - Stworz naprawe 6 - Wypisz naprawy 7 - Wypisz koszty napraw dla klienta 8 - Oblicz premie dla mechanika 9 - Wypisz napawy ze szczegolami\n";
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
            if (Warsztat::get_warsztat()->get_mechanik() != nullptr) Warsztat::get_warsztat()->get_mechanik()->diagnoza();
            break;
        case 6:
            Warsztat::get_warsztat()->wypisz_naprawy();
            break;
        case 7:
            Warsztat::get_warsztat()->get_klient()->diagnoza();
            break;
        case 8:
            Warsztat::get_warsztat()->get_mechanik()->obliczPremie();
            break;
        case 9:
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
