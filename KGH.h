#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <boost\numeric\ublas\matrix.hpp>
//size1 - wiersz
//size2 - kolumna
#include <boost\numeric\ublas\io.hpp>

#include <boost\multiprecision\cpp_int.hpp>
//max mINT: 9999999999999999999 = 10^19 - 1
#include <boost\multiprecision\cpp_dec_float.hpp>

//obsluguje pliki
#include <fstream>

using namespace boost::numeric::ublas;
//typedef boost::multiprecision::cpp_dec_float_100 mInt;
typedef boost::multiprecision::cpp_int mInt;

class KGH
{
public:
	KGH();
	~KGH();
	//Funkcja - odpowiadajaca za losowanie wartosci z zakresu <1,modulo-1>
	//modulo - wartosc do definicji zakresu losowania
	mInt randomValue(mInt modulo);
	//Funkcja - przygotowywuje algorytm KGH
	void przygotowanieKGH();
	//Funkcja - dystrybuuje udzialy
	//m - macierz M
	//wektorR - wektor r (czyli ten, ktory odpowiada za generowanie udzialow)
	//wektorV - wektor v0 (czyli ten, ktory odpowiada za generowanie sekretu)
	//wynik - wektor wartosci ai (ai generuja wektor V0)
	void dystrybucjaSekretow(matrix<mInt> m, vector<mInt> wektorR, vector<mInt> wektorV, vector<mInt> wynik);
	//Funkcja - odpowiada za lewostronne mnozenie macierzy, z wektorem
	//m - macierz
	//wektor - wektor
	//wyjscie - wektor kolumnowy
	vector<mInt> MnozenieMV(matrix<mInt> m, vector<mInt> wektor);
	//Funkcja - mnozy wektor z wektorem
	//w1, w2 - wektory
	//wyjscie wartosc mInt
	mInt MnozenieVV(vector<mInt> w1, vector<mInt> w2);
	//Funkcja - odpowiada za odzyskanie sekretu
	//wektorA - wektor przetrzymujacy wartosci ai
	//wektorS - wektor przetrzymujacy wartosci udzialo si
	void odzyskajSekret(vector<mInt> wektorA, vector<mInt> wektorS);
private:
	//ile minimum ma byc udzialow w progu (2,maxmInt)
	int prog = 0;
	//ilu ma byc udzialowcow (prog,maxmInt)
	int udzial = 0;
	//zapisany sekret
	mInt sekret = 0;
};

