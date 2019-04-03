/*
Potrebno je kreirati aplikaciju za dijeljenje znanja putem razmjene članaka među korisnicima.

Izdvojene su sljedeće funkcionalnosti:
- Administrator sistema je zadužen za upravljanje korisničkim nalozima (Ime, Prezime, Email, DatumRegistracije, KorisnickoIme, Lozinka).
- Svaki članak (Naslov, Sadrzaj, Datum, Satnica, BrojPregleda) može sadržavati više tagova, ali pripada samo jednoj oblasti.
- Članke mogu dodavati svi registrovani korisnici.
- Korisnici aplikacije također mogu ostaviti komentar (Tekst, Datum, Popularnost) na određeni članak.
*/

/*
Na osnovu datih klasa implementirati opisane funkcionalnosti sistema. Po potrebi dopuniti klase novim atributima i/ili funkcijama.
*/
#include <iostream>
using namespace std;

char* charAlloc(const char* src) {
	int len = strlen(src) + 1;
	char* ret = new char[len];
	strcpy_s(ret, len, src);
	return ret;
}

class Datum {
	int _dan;
	int _mjesec;
	int _godina;

public:
	// constructor
	Datum(int dan, int mjesec, int godina) {
		_dan = dan;
		_mjesec = mjesec;
		_godina = godina;
	}

	// funckija
	void info() {
		cout << _dan << "." << _mjesec << "." << _godina << "\n";
	}
};

enum TipKorisnika { Administrator, Guest };

class Korisnik {
	char _ime[30];
	char _korisnickoIme[20];
	char* _lozinka;
	TipKorisnika _tipKorisnika; // Administrator, Guest

public:
	// constructor
	Korisnik(char ime[], char korisnickoIme[], const char* lozinka, TipKorisnika tipKorisnika) {
		strcpy_s(_ime, 30, ime);
		strcpy_s(_korisnickoIme, 20, korisnickoIme);
		_lozinka = charAlloc(lozinka);
		_tipKorisnika = tipKorisnika;
	}

	// destructor
	~Korisnik() {
		delete _lozinka;
	}

	// funkcija za promjenu korisničke lozinke
	void promjeniLozinku(const char* lozinka) {
		_lozinka = charAlloc(lozinka);
	}

	// funkcija info
	void info() {
		cout << "Ime: " << _ime << "\n";
		cout << "Korisnicko ime: " << _korisnickoIme << "\n";
		cout << "Lozinka: " << _lozinka << "\n";
		cout << "Tip korisnika: " << _tipKorisnika << "\n";
	}

};

class Komentar {
	char* _tekst;
	Datum _datum;
	Vrijeme _satnica;
	int _popularnost;
	Korisnik* _autor;
public:
	//Potrebne konstruktor i destruktor funkcije

	//Funkciju za izmjenu popularnosti komentara

	//Funkciju Info

};

class Clanak {
	char _naslov[150];
	char* _sadrzaj;
	Datum _datum;
	Vrijeme _satnica;
	int _brojPregleda;
	char* _tagovi[10];
	char _oblast[100];
	Korisnik* _autor;
	Komentar* _komentari;
	int _brojKomentara;
public:

	//Funkciju za dodavanje tagova za članak

	/*Funkciju za promjenu sadržaja i vremena promjene članka. Kao verifikaciju dozvole potrebno je proslijediti korisničko ime autora članka.
	Samo kreator članka ima permisije da mijenja njegov sadržaj.
	*/

	//Funkciju za dodavanje komentara

	//Funkciju Info

};

int main() {
	//Kreirati testni program koji demonstrira implementirane funckionalnosti


	return 0;
}
