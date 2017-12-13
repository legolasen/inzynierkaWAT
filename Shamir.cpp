#include "Shamir.h"

Shamir::Shamir()
{
	int pomoc = 0;
	while (pomoc != 1 && pomoc != 2) {
		std::cout << "Czy chcesz przygotowac i rozprowadzic Shamir'a (1), czy odkryc sekret (2):" << std::endl;
		std::cin >> pomoc;
	}
	if (pomoc == 1) przygotowanieShamir();
	else {
		std::cout << "Wpisz ile cieni jest potrzebnych do odzyskania sekretu: ";
		int we;
		std::cin >> we;
		odzyskanieSekretuShamir(we,false);
	}
}

Shamir::~Shamir()
{
}

void Shamir::przygotowanieShamir()
{
	srand(time(NULL));
	prog = -1;
	while (prog < 0) {
		std::cout << "Czy ma to byc system progowy, jesli tak to podaj liczbe progowa? 0-Nie" << std::endl;
		std::cin >> prog;
	}
	udzial = -1;
	while (udzial < prog) {
		std::cout << "Ilu potrzeba udzialow, by odzyskac sekret? mniej niz prog-Ponowienie pytania:" << std::endl;
		std::cin >> udzial;
	}
	if (prog == 0) prog = udzial;
	sekret = -1;
	while (sekret < 0) {
		std::cout << "Podaj sekret większy od 0 i mniejszy od p:" << std::endl;
		std::cin >> sekret;
		if (sekret > mod - 1) sekret = -1;
	}
	rownanie.clear();
	rownanie.push_back(sekret);
	for (int i = 0; i < prog - 1; i++) {
		rownanie.push_back(randomValue(mod));
	}
	cienie.clear();
	wCienie.clear();
	generowanieCieniShamir(udzial);
}

void Shamir::generowanieCieniShamir(int liczba)
{
	std::cout << "\nGewnerowanie cieni..." << std::endl;
	std::ofstream myfile;
	bool straznik = true;
	mInt argument = 0;
	myfile.open("cienieShamir.txt");
	myfile << "Sekret: " << this->sekret << ", prog cieni: " << this->prog << "\n";
	myfile << "Rownanie wielomianowe (0...n-1): ( ";
	for (int i = 0; i < prog; i++) {
		myfile << rownanie[i] << ", ";
	}
	myfile << ")\n";
	for (int j = 0; j < liczba; j++) {
		std::cout << "Gewnerowanie cienia nr. " << j+1 << std::endl;
		straznik = true;
		argument = 0;
		while (straznik == true) {
			argument = randomValue(mod);
			if (j == 0) {
				cienie.push_back(argument);
				straznik = false;
			}
			else {
				if (j == 1) {
					if (argument != cienie[0]) {
						cienie.push_back(argument);
						straznik = false;
					}
				}
				else {
					if (wyszukajCien(argument) == false) {
						cienie.push_back(argument);
						straznik = false;
					}
				}
			}
		}
		mInt wynik = rownanie[0];
		mInt x = 1;
		for (int i = 1; i < rownanie.size(); i++) {
			x = mnozenieModulo(x, argument);
			wynik = dodawanieModulo(wynik, mnozenieModulo(rownanie[i], x));
		}
		wCienie.push_back(wynik);
		myfile << j + 1 << ": x = " << argument << ", f(x) = " << wynik << "\n";
	}
	myfile.close();
	int we = 0;
	std::cout << "Jesli chcesz odzyskac ten sekret - wybierz 1, else wyjscie:" << std::endl;
	std::cin >> we;
	if (we == 1) odzyskanieSekretuShamir(prog, true);
}

void Shamir::odzyskanieSekretuShamir(int liczba, bool test)
{
	if (test == false) {
		int uX, uFx;
		cienie.clear();
		wCienie.clear();
		for (int i = 0; i < liczba; i++) {
			std::cout << "Udzial nr. " << i + 1 << ": x=";
			std::cin >> uX;
			std::cout << "f(x)=";
			std::cin >> uFx;
			if (i == 0) {
				cienie.push_back(uX);
				wCienie.push_back(uFx);
				std::cout << "Poprawnie wczytano dane." << std::endl;
			}
			else {
				if (wyszukajCien(uX) == false) {
					cienie.push_back(uX);
					wCienie.push_back(uFx);
					std::cout << "Poprawnie wczytano dane." << std::endl;
				}
				else {
					std::cout << "Znaleziono duplikat! Sprobuj wprowadzic jeszcze raz udzial." << std::endl;
					i = i - 1;
				}
			}

		}
		std::cout << "Trwa wyliczanie sekretu." << std::endl;
	}
	mInt suma = 0;
	mInt mnozenie = 0;
	std::cout << "Rozpoczynamy odzyskiwanie sekretu:" << std::endl;
	for (int i = 0; i < liczba; i++) {
		mnozenie = 1;
		for (int j = 0; j < liczba; j++) {
			if (j != i) {
				mnozenie = mnozenieModulo(dzielenieModulo(mod-cienie[j], odejmowanieModulo(cienie[i], cienie[j])),mnozenie);
			}
		}
		suma = dodawanieModulo(suma, mnozenieModulo(wCienie[i], mnozenie));
	}
	std::cout << "Sekret: " << suma << std::endl;
	std::cout << "Powtorzyc generowanie sekretu? 1 - tak, else - koniec programu: " << std::endl;
	int we = 0;
	std::cin >> we;
	if (we == 1) przygotowanieShamir();
}

mInt Shamir::randomValue(mInt modulo)
{
	mInt wartosc = 0;
	while (wartosc == 0) {
		wartosc = rand() % modulo;
		wartosc = mnozenieModulo(wartosc, rand());
		wartosc = mnozenieModulo(wartosc, rand());
		if (wartosc < 0) wartosc = wartosc + modulo;
	}
	return wartosc;
}

mInt Shamir::odejmowanieModulo(mInt a, mInt b)
{
	mInt wy = a - b;
	if (wy < 0) wy = wy + mod;
	return wy;
}

mInt Shamir::dzielenieModulo(mInt a, mInt b)
{
	return mnozenieModulo(a,euklides(b));
}

mInt Shamir::euklides(mInt x) // x - liczba, n - liczba pierwsza (dostaje potege odwrotnosci)
{
	mInt n = mod;
	mInt t, q, b, a;
	mInt alfa = 0;
	mInt beta = 1;
	b = x;
	a = n;
	do
	{
		t = 0;
		q = a / b;
		t = a;
		a = b;
		b = t - q*b;
		t = alfa;
		alfa = beta;
		beta = t - q*beta;
	} while (b != 0);
	if (alfa < 0) alfa = alfa + n;
	return alfa;
}

mInt Shamir::dodawanieModulo(mInt a, mInt b)
{
	mInt wy = 0;
	wy = (a+b)%mod;
	if (wy < 0) wy = wy + mod;
	return wy;
}

mInt Shamir::mnozenieModulo(mInt a, mInt b)
{
	mInt wyjscie = a;
	if (a < 0) std::cout << "a<0!!" << std::endl;
	if (b < 0) std::cout << "b<0!!" << std::endl;
	for (int i = 1; i < b; i++) {
		wyjscie = dodawanieModulo(wyjscie, a);
	}
	if (b == 0) wyjscie = 0;
	return wyjscie;
}

bool Shamir::wyszukajCien(mInt we)
{
	for (int i = 0; i < cienie.size(); i++) {
		if (we == cienie[i]) return true;
	}
	return false;
}
