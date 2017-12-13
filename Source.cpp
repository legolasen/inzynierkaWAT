#include "Header.h"

int main() {
	int odpowiedz = 0;
	std::cout << "Wybierz opcje:" << std::endl;
	std::cout << "1 - Protokol Shamira" << std::endl;
	std::cout << "2 - Protokol Asmutha-Blooma" << std::endl;
	std::cout << "3 - Protokol Karnina-Greene'a-Hellmana" << std::endl;
	std::cout << "else - Wyjscie z programu" << std::endl;
	std::cin >> odpowiedz;
	if (odpowiedz == 1) {
		Shamir pS = Shamir();
	}
	else {
		if (odpowiedz == 2) {
			AsmuthBloom pAB = AsmuthBloom();
		}
		else {
			if (odpowiedz == 3) {
				KGH pKGH = KGH();
			}
		}
	}
	system ("pause");
	return 0;
}