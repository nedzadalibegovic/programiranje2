#include <iostream>
#include <memory>
using namespace std;

void main() {

	int red, kolona;

	cout << "Broj redova i kolona: ";
	cin >> red >> kolona;

	// kreiranje niza pokazivaca od kojih svaki sadrzi niz integera
	// make_shared<Type>() se ne moze koristiti za kreiranje nizova
	//        ------- tipa -------         ---- pokazuje na niz pok ----
	shared_ptr<shared_ptr<int[]>[]> matrica(new shared_ptr<int[]>[red]);

	// kreiranje niz integera u svakom od pokazivaca
	for (int i = 0; i < red; i++) {
		matrica[i] = shared_ptr<int[]>(new int[kolona]);
	}

	// standardni unos
	for (int i = 0; i < red; i++) {
		for (int j = 0; j < kolona; j++) {
			cin >> matrica[i][j];
		}
	}

	// standardni ispis
	for (int i = 0; i < red; i++) {
		for (int j = 0; j < kolona; j++) {
			cout << matrica[i][j] << " ";
		}
		cout << endl;
	}
}