#include "KGH.h"
//TODO skomentowanie
//TODO wprowadzanie do odkrycia sekretu
KGH::KGH()
{
	int pomoc = 0;
	while (pomoc!= 1 && pomoc != 2) {
		std::cout << "Czy chcesz przygotowac i rozprowadzic KGH (1), czy odkryc sekret (2):" << std::endl;
		std::cin >> pomoc;
	}
	if (pomoc == 1) przygotowanieKGH();
}

KGH::~KGH()
{
}

mInt KGH::randomValue(mInt modulo)
{
	mInt wartosc = (rand()*rand()*rand()) % modulo;
	if (wartosc < 0) wartosc = wartosc + modulo;
	if (wartosc == 0) wartosc = 1;
	return wartosc;
}

void KGH::przygotowanieKGH()
{
	srand(time(NULL));
	prog = 0;
	udzial = -1;
	while (udzial <= prog) {
		std::cout << "Ilu potrzeba udzialow, by odzyskac sekret? mniej niz prog-Ponowienie pytania:" << std::endl;
		std::cin >> udzial;
	}
	if (prog == 0) prog = udzial;

	/*Tworzenie macierzy V1..Vn*/
	matrix<mInt> m(prog, prog);
	for (int i = 0; i < m.size1(); i++) {
		for (int j = 0; j < m.size2(); j++) {
			if(j >= i) m(i, j) = randomValue(999);
		}
	}

	/*Tworzenie wektoraR*/
	vector<mInt> wektorR(prog);
	/*wektorV - wektor V0*/
	vector<mInt> wektorV(prog);
	for (int i = 0; i < m.size2(); i++) {
		wektorR[i] = randomValue(999);
		wektorV[i] = 0;
	}
	/*Tworzenie wektoraV0*/
	/*help - przetrzymuje wartosci a1...an*/
	vector<mInt> help(prog);
	for (int i = 0; i < prog; i++) {
		help[i] = randomValue(10);
		for (int j = 0; j < prog; j++) {
			wektorV[j] = wektorV[j] + (help[i]*m(i, j));
		}
	}

	sekret = MnozenieVV(wektorR, wektorV);
	std::cout << "Sekret: " << sekret << std::endl;

	dystrybucjaSekretow(m, wektorR, wektorV, help);
}

void KGH::dystrybucjaSekretow(matrix<mInt> m, vector<mInt> wektorR, vector<mInt> wektorV, vector<mInt> wynik)
{
	std::ofstream myfile;
	myfile.open("cienieKGH.txt");
	myfile << "V0:\n";
	myfile << wektorV << "\n";
	myfile << "a1...an\n";
	myfile << wynik << "\n";

	vector<mInt> wynikS = MnozenieMV(m, wektorR);

	myfile << "M:\n";
	myfile << m << "\n";

	for (int i = 0; i < wynikS.size(); i++) {
		myfile << "(V" << i+1 << ", " << wynikS[i] << ")\n";
	}
	myfile.close();

	//std::cout << "size wynik - " << wynik.size() << ", size wynikS - " << wynikS.size() << std::endl;

	std::cout << "Zakonczono etap dystrybucji udzialow, czy chcesz odzyskac sekret (1)? - ";
	int we = 0;
	std::cin >> we;
	if (we == 1) odzyskajSekret(wynik, wynikS);
}

vector<mInt> KGH::MnozenieMV(matrix<mInt> m, vector<mInt> wektor)
{
	vector<mInt> wy(prog);
	if (m.size2() != wektor.size()) {
		std::cout << "Zla wielkosc przy mnozeniu macierz*wektor!" << std::endl;
		return vector<mInt>();
	}
	else {
		mInt wynik = 0;
		for (int i = 0; i < m.size1(); i++) {
			wynik = 0;
			for (int j = 0; j < m.size2(); j++) {
				mInt a = m.operator()(i,j);
				mInt b = wektor[j];
				wynik = wynik + (a * b);
			}
			wy[i] = wynik;
		}
	}
	return wy;
}

mInt KGH::MnozenieVV(vector<mInt> w1, vector<mInt> w2)
{
	if (w1.size() != w2.size()) {
		std::cout << "w1.size() != w2.size()!!" << std::endl;
		return mInt();
	}
	else {
		mInt wy = 0;
		for (int i = 0; i < w1.size(); i++) {
			wy = wy + (w1[i] * w2[i]);
		}
		return wy;
	}
}

void KGH::odzyskajSekret(vector<mInt> wektorA, vector<mInt> wektorS)
{
	mInt wynik = MnozenieVV(wektorA, wektorS);

	std::cout << "Sekret: " << wynik << std::endl;
}
