#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <boost\multiprecision\cpp_int.hpp>
	//max mINT: 9999999999999999999 = 10^19 - 1
#include <boost\multiprecision\cpp_dec_float.hpp>

	//obsluguje wektory
#include <vector>
	//obsluguje pliki
#include <fstream>


using namespace boost::numeric::ublas;
typedef boost::multiprecision::cpp_int mInt;

class Shamir
{
public:
	Shamir();
	~Shamir();
		//Metoda - generowanie rownania wielomianowego, na podstawie zadanego progu i sekretu w trakcie wykonywania metody
		//wyniki zapisuja sie w: std::vector<mInt> rownanie
	void przygotowanieShamir();
		//Metoda - generuje zadana liczbe udzialow w rownaniu wielomianowym std::vector<mInt> rownanie
		//liczba - liczba udzialow do wygenerowania
		//wyniki zapisuja sie w: std::vector<mInt> cienie; - wartosci xi, std::vector<mInt> wCienie - wartosci f(xi), gdzie i = <0;liczba-1>
	void generowanieCieniShamir(int liczba);
		//Metoda - odzyskuje sekret
		//liczba - liczba potrzebnych cieni
		//test - false - nie pobiera danych z std::vector<mInt> cienie, std::vector<mInt> wCienie, lecz wprowadzamy je recznie
		//test - true - pobiera dane z std::vector<mInt> cienie, std::vector<mInt> wCienie
	void odzyskanieSekretuShamir(int liczba, bool test);
		//Metoda - losujaca wartosc z zakresu <0;mod-1>
	mInt randomValue(mInt modulo);
		//Metoda - dodajaca dwie liczby modulo mod
		//a,b - liczby dodatnie z zakresu <0;mod-1>
	mInt dodawanieModulo(mInt a, mInt b);
		//Metoda - odejmujaca dwie liczby modulo mod
		//a,b - liczby dodatnie z zakresu <0;mod-1>
	mInt odejmowanieModulo(mInt a, mInt b);
		//Metoda - mnozy dwie liczby modulo mod
		//a,b - liczby dodatnie z zakresu <0;mod-1>
	mInt mnozenieModulo(mInt a, mInt b);
		//Metoda - dzieli dwie liczby modulo mod
		//a,b - liczby dodatnie z zakresu <0;mod-1>
	mInt dzielenieModulo(mInt a, mInt b);
		//Metoda - algorytm euklidesa - sluzy do znalezenie odwrotnej liczby w ciele Z(mod)
		//a - liczba dodatnia z zakresu <0;mod-1>
	mInt euklides(mInt x);
private:
		//ile minimum ma byc udzialow w progu (2,maxmInt)
	int prog = 0;
		//ilu ma byc udzialowcow (prog,maxmInt)
	int udzial = 0;
		//deklaracja rozmiaru ciala Fp
	const mInt mod = 9973;
		//Zapisany sekret
	mInt sekret = 0;
		//wartosci rownania wielomianowego
	std::vector<mInt> rownanie;
		//argumenty wygenerowanych cieni w trakcie generowaniaCieniShamir
	std::vector<mInt> cienie;
		//wartosci argumentow wygenerowanych cieni
	std::vector<mInt> wCienie;
		//funkcja przeszukuje wektor cieni:
		//we - wejsciowy cien, ktory musi byc unikalny w wektorze cieni
		//-> true - znaleziono duplikat
		//-> false - nie znaleziono duplikatu
	bool wyszukajCien(mInt we);
};

