#include "AsmuthBloom.h"



AsmuthBloom::AsmuthBloom()
{
	int we = 0;
	std::cout << "Czy przygotowac alogrytm? 1-Tak, Else - odkryj sekret" << std::endl;
	std::cin >> we;
	if (we == 1) {
		przygotowanieAB();
	}
	else {
		std::cout << "Ile sektretow uzyjesz do odkrycia sekretow (0 - wyjscie):" << std::endl;
		std::cin >> we;
		if (we != 0) {
			odkryjSekret(we,false);
		}	
	}
	
}


AsmuthBloom::~AsmuthBloom()
{
}

void AsmuthBloom::przygotowanieAB()
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
	//Jesli to nie jest schemat progowy
	if (prog == 0) prog = udzial;
	cienied.clear();
	cieniek.clear();
	p = 0;
	sekret = 0;
	generujCRT();
}

void AsmuthBloom::generujCRT()
{
	int lp = zbiorLiczbP.size();
	int pomoc = 0;
	bool straznikPomoc = false;
	while (straznikPomoc == false) {
		cienied.clear();
		pomoc = pomoc + 5;
		//sprawdzenie, czy nie wyszla funkcja za dopuszczalny zakres
		if (pomoc + udzial > lp) {
			straznikPomoc == true;
			std::cout << "WYJSCIE Z ZAKRESU parametru: pomoc+udzial > lp" << std::endl;
		}
		else {
			int zakresLiczb = lp / (udzial + pomoc);
			int parametr = 0;
			//jesli to nie jest schemat progowy, else schemat progowy
			if (udzial == prog) {
				mInt wynikL = 1;
				mInt wynikP = 1;
				//generowanie di, gdzie i = <0,udzial-2>
				for (int i = 0; i < udzial - 1; i++) {
					parametr = losujZZakresu(i*zakresLiczb, (i + 1)*zakresLiczb);
					cienied.push_back(zbiorLiczbP[parametr]);
					wynikL = wynikL * cienied[i];
				}
				bool straznik = false;
				int i = 0;
				//generowanie di, gdzie i = udzial-1, oraz p tak, aby spelnial nierownosc
				while (straznik == false) {
					parametr = losujZZakresu((udzial + pomoc - 2)*zakresLiczb, (udzial + pomoc - 1)*zakresLiczb);
					cienied.push_back(zbiorLiczbP[parametr]);
					parametr = losujZZakresu((udzial + pomoc - 1)*zakresLiczb, (lp - 1));
					p = zbiorLiczbP[parametr];
					wynikP = p * cienied[udzial - 1];
					//jesli spelniona jest nierownosc
					if (wynikL < wynikP) {
						straznik = true;
						straznikPomoc = true;
						std::cout << "Liczba p: " << p << std::endl;
						std::cout << "Powodzenie generowania di..." << std::endl;
					}
					//Po 20 probach zmieniamy zakres losowania liczb
					if (i == 20) straznik = true;
					i++;
				}
			}
			else {
				mInt wynikL = 1;
				mInt wynikP = 1;
				//generowanie di, gdzie i = <0,udzial-1>
				for (int i = 0; i < udzial; i++) {
					parametr = losujZZakresu(i*zakresLiczb, (i + 1)*zakresLiczb);
					cienied.push_back(zbiorLiczbP[parametr]);
					if (i < prog) {
						wynikL = wynikL * cienied[i];
					}
					else {
						wynikP = wynikP * cienied[i];
					}
				}
				bool straznik = false;
				int i = 0;
				//generowanie p tak, aby spelnial nierownosc
				while (straznik == false) {
					parametr = losujZZakresu(udzial*zakresLiczb, (udzial+1)*zakresLiczb);
					p = zbiorLiczbP[parametr];
					wynikP = p * wynikP;
					//jesli spelniona jest nierownosc
					if (wynikL > wynikP) {
						straznik = true;
						straznikPomoc = true;
						std::cout << "Liczba p: " << p << std::endl;
						std::cout << "Powodzenie generowania di..." << std::endl;
					}
					//Po 20 probach zmieniamy zakres losowania liczb
					if (i == 20) straznik = true;
					i++;
				}
			}
		}
	}
	generujCienieK();
}

int AsmuthBloom::losujZZakresu(int poczatek, int koniec)
{
	int wartosc = 0;
	//std::cout << "Losowanie z zakresu: " << poczatek << ", " << koniec << std::endl;
	while (wartosc == 0) {
		wartosc = rand() % (koniec-poczatek);
		if (wartosc < 0) wartosc = wartosc * (-1);
		wartosc = wartosc + poczatek;
	}
	return wartosc;
}

void AsmuthBloom::generujCienieK()
{
	std::cout << "Wprowadz wiadomosc < od p - " << p << ": ";
	bool straznik = false;
	while (straznik == false) {
		std::cin >> sekret;
		if(sekret>p) std::cout << "Za duza wiadomosc! Wprowadz wiadomosc < od p: " << p;
		else straznik = true;
	}
	mInt pomoc = rand() % cienied[0];
	pomoc = sekret + pomoc*p;
	std::ofstream myfile;
	myfile.open("cienieAB.txt");
	mInt d = 0;
	mInt k = 0;
	for (int i = 0; i < cienied.size(); i++) {
		d = cienied[i];
		k = pomoc%d;
		cieniek.push_back(k);
		myfile << i + 1 << ": d = " << d << ", k = " << k << "\n";
	}
	myfile << "p = " << p << "\n";
	myfile << "sekret = " << sekret << "\n";
	myfile.close();
	std::cout << "Cienie zostaly zapisane w pliku cienieAB.txt." << std::endl;
	std::cout << "Jesli chcesz odkryc ten sekret kliknij 1, else wyjscie" << std::endl;
	int we = 0;
	std::cin >> we;
	if (we == 1) odkryjSekret(prog, true);
}

void AsmuthBloom::odkryjSekret(int liczbaSekretow, bool info)
{
	if (info == false) {
		mInt we = 0;
		for (int i = 0; i < liczbaSekretow; i++) {
			std::cout << "Wprowadz d" << i + 1 << std::endl;
			std::cin >> we;
			cienied.push_back(we);
			std::cout << "Wprowadz k" << i + 1 << std::endl;
			std::cin >> we;
			cieniek.push_back(we);
		}
		//std::cout << "size d: " << cienied.size() << "size k: " << cieniek.size() << std::endl;
	}
	std::cout << "Rozpoczecie odzyskiwania sekretu." << std::endl;
	mInt N = 1;
	for (int i = 0; i < liczbaSekretow; i++) {
		N = N * cienied[i];
	}
	std::vector<mInt> l;
	std::vector<mInt> y;
	mInt x = 0;
	mInt pomoc = 0;
	mInt pomoc2 = 0;
	for (int i = 0; i < liczbaSekretow; i++) {
		std::cout << "Przeliczam udzial nr. " << i+1 << "..." << std::endl;
		l.push_back(N / cienied[i]);
		pomoc2 = l[i] % cienied[i];
		y.push_back(euklides(pomoc2, cienied[i]));
		pomoc = mnozenieModulo(cieniek[i], y[i], N);
		pomoc = mnozenieModulo(pomoc, l[i], N);
		x = (x + pomoc) % N;
	}
	std::cout << "Sekret = " << x%p << std::endl;
	std::cout << "Zakonczono odzyskiwanie sekretu!" << std::endl;
}

mInt AsmuthBloom::euklides(mInt x, mInt mod)
{
	//std::cout << "We euklides: " << x << std::endl;
	mInt n = mod;
	mInt t, q, b, a;
	mInt alfa = 0;
	mInt beta = 1;
	b = x;
	a = n;
	do
	{
		t = 0;
		q = a / b; //(powinien byc floor, ale dla dod dziala poprawnie)
		t = a;
		a = b;
		b = t - q*b;
		t = alfa;
		alfa = beta;
		beta = t - q*beta;
	} while (b != 0);
	if (alfa < 0) alfa = alfa + n;
	//std::cout << "Wy euklides: " << alfa << std::endl;
	return alfa;
}

mInt AsmuthBloom::dodawanieModulo(mInt a, mInt b, mInt mod)
{
	return (a + b) % mod;
}

mInt AsmuthBloom::mnozenieModulo(mInt a, mInt b, mInt mod)
{
	mInt wyjscie = a;
	for (int i = 1; i < b; i++) {
		wyjscie = dodawanieModulo(wyjscie, a, mod);
	}
	return wyjscie;
}
