#include <iostream>
#include <memory>
#include <string>
using namespace std;

struct Datum {
	int dan, mjesec, godina;

	void unos() {
		cout << "Dan: ";
		cin >> dan;
		cout << "Mjesec: ";
		cin >> mjesec;
		cout << "Godina: ";
		cin >> godina;
	}

	void ispis() {
		cout << "Datum: " << dan << "." << mjesec << "." << godina << ".\n";
	}
};

struct Cijepljenje {
	Datum datum;
	unique_ptr<char[]> opis;

	void unos() {
		char buffer[30];

		cout << "Unesite datum cijepljenja\n";
		datum.unos();
		cin.ignore();

		cout << "Unesite opis cijepljenja:\n";
		cin.getline(buffer, 30);

		opis = make_unique<char[]>(strlen(buffer) + 1);
		strcpy
	}
};

struct Ljubimac {
	char *ime;
	float dob;
	char *vrsta;
	char *spol;
	Cijepljenje cijepljenje;

};

int main() {

	cout << "Hello world!" << endl;

	return 0;
}