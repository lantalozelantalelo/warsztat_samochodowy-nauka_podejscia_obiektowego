#include <iostream>
#include <string>
#include <random>
#include <vector>
#include "Dane.h"

std::string_view Imiona[szImiona]{ "sara", "jacek", "dariusz", "lukasz", "maksymilian",
                        "szymon", "kamila", "marta", "patryk", "piotr",
                        "bartosz", "michal", "ruslan", "jakub", "agata",
                        "jan", "andrzej", "mateusz", "krzysztof" };

std::string_view Nazwiska[szNazwiska]{ "iwaszkiewicz", "jakubowski", "kozlowski", "tusk", "przygodzki",
                        "pawlak", "winiarski", "wojtczak", "wolska", "zawalski",
                        "znamirowski", "banasik", "bodnar", "daszewski" };

std::string_view Rejestracja[szRejestracja]{ "BI", "CT", "DW", "EL", "FG", "GD", "KK", "LUB", "NO", "OP", "PO", "RZ", "SK", "TK", "WE", "ZS", "WP", "GA", "GSP", "KR" };

std::string_view Marka[szMarka]{ "Audi", "BMW", "Citroen", "Dacia", "Fiat", "Ford", "Hyundai", "Kia", "Mercedes", "Nissan", "Opel", "Peugeot", "Renault", "Seat", "Skoda",
"Subaru", "Tesla", "Toyota", "Volkswagen", "Volvo" };

std::string_view NazwaCzesci[szNazwaCzesci]{ "Filtr powietrza", "Alternator", "Akumulator", "Blok silnika", "Przewody hamulcowe", "Wal rozrzadu", "Kolo zebate walu rozrzadu",
"Plyta silnika", "Rura wydechowa", "Tlumik wydechowy", "Pompa paliwowa", "Skrzynia biegow", "Filtr oleju", "Tlok", "Chlodnica", "Rozrusznik", "Kolumna kierownicy",
"Drazek kierownicy", "Lancuch rozrzadu", "Pompa wody" };

size_t generujLiczbeLosowa(size_t pierwsza, size_t ostatnia)
{
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution<size_t> uniformDist(pierwsza, ostatnia);

    return uniformDist(engine);
}

std::string gen_data0()
{
    static std::random_device rd;
    static std::default_random_engine dfe(rd());
    static std::uniform_int_distribution<int> numDistImie(0, szImiona - 1);
    static std::uniform_int_distribution<int> numDistNazwisko(0, szNazwiska - 1);

    size_t index_imienia = numDistImie(dfe);
    size_t index_nazwiska = numDistNazwisko(dfe);

    return std::string(Imiona[index_imienia]) + " " + std::string(Nazwiska[index_nazwiska]);
}

size_t gen_data1()
{
    static std::random_device rd;
    static std::default_random_engine dfe(rd());
    static std::uniform_int_distribution<int> nrtelDist(111111111, 999999999);

    return nrtelDist(dfe);
}

size_t gen_data2()
{
    static std::random_device rd;
    static std::default_random_engine dfe(rd());
    static std::uniform_int_distribution<int> l_samochodowDist(1, 3);

    return l_samochodowDist(dfe);
}

void duzaLitera(std::string& tekst)
{
    tekst[0] = std::toupper(tekst[0]);
}

size_t gen_dataIloscCzesci()
{
    static std::random_device rd;
    static std::default_random_engine dfe(rd());
    static std::uniform_int_distribution<int> czesci(1, 6);
    return czesci(dfe);
}

std::string gen_dataNazwaCzesci()
{
    static std::random_device rd;
    static std::default_random_engine dfe(rd());
    static std::uniform_int_distribution<int> numDistNazwaCzesci(0, szNazwaCzesci - 1);
    size_t index_nazwa = numDistNazwaCzesci(dfe);
    return std::string(NazwaCzesci[index_nazwa]);
}

size_t gen_dataCenaCzesci()
{
    static std::random_device rd;
    static std::default_random_engine dfe(rd());
    static std::uniform_int_distribution<int> cenaDist(50, 10000);
    return cenaDist(dfe);
}

void gen_data(size_t& num)
{
    // bez static pocz�tkowy stan random_device b�dzie takim sam przy ka�dym uruchomieniu
    static std::random_device rd;
    static std::default_random_engine dfe(rd());
    static std::uniform_int_distribution<int> rozmiar(50, 100);
    num = rozmiar(dfe);
}

void rekord(std::string*& Rekordy, int num)
{
    static std::random_device rd;
    static std::default_random_engine dfe(rd());
    static std::uniform_int_distribution<int> numDistImie(0, szImiona - 1);
    static std::uniform_int_distribution<int> numDistNazwisko(0, szNazwiska - 1);
    static std::uniform_int_distribution<int> nrtelDist(111111111, 999999999);
    for (int i = 0; i < num; i++) {
        std::string imiona = std::string(Imiona[numDistImie(dfe)]);
        std::string nazwiska = std::string(Nazwiska[numDistNazwisko(dfe)]);
        std::string nr_tel = std::to_string(nrtelDist(dfe));
        duzaLitera(imiona);
        duzaLitera(nazwiska);
        std::string godnosc = imiona + " " + nazwiska;
        std::string rekord = "Klient " + godnosc + " " + nr_tel;
        Rekordy[i] = rekord;
        std::cout << rekord << std::endl;
    }
}