#pragma once
#include <iostream>
#include <string>
#include <random>
#include <vector>

const size_t szImiona = 19;
const size_t szNazwiska = 14;
const size_t szRejestracja = 20;
const size_t szMarka = 20;
const size_t szNazwaCzesci = 20;

std::string_view Imiona[];
std::string_view Nazwiska[];
std::string_view Rejestracja[];
std::string_view Marka[];
std::string_view NazwaCzesci[];

size_t generujLiczbeLosowa(size_t pierwsza, size_t ostatnia);

std::string gen_data0();

size_t gen_data1();

size_t gen_data2();

void duzaLitera(std::string& tekst);

size_t gen_dataIloscCzesci();

std::string gen_dataNazwaCzesci();

size_t gen_dataCenaCzesci();

void gen_data(size_t& num);

void rekord(std::string*& Rekordy, int num);