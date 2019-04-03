// PRIII - Ispitni zadatak - Prvi parcijalni
// https://youtu.be/SULoYxj6Jd4

#include <iostream>
using namespace std;

const char* crt = "\n--------------------------\n";

char* charAlloc(const char* src) {
	int len = strlen(src) + 1;
	char* rt = new char[len];
	strcpy_s(rt, len, src);
	return rt;
}

class KupljeniArtikal {
	char* _naziv;
	float _cijena;
	int _kolicina;
	// konstruktor, destruktor i potrebne funkcije

	// swap-and-copy idiom
	friend void zamjeni(KupljeniArtikal& desni, KupljeniArtikal& lijevi) {
		swap(desni._naziv, lijevi._naziv);
		swap(desni._cijena, lijevi._cijena);
		swap(desni._kolicina, desni._kolicina);
	}
public:
	KupljeniArtikal() {
		_naziv = nullptr;
		_cijena = 0;
		_kolicina = 0.0f;
	}

	KupljeniArtikal(const char* naziv, float cijena, int kolicina = 1) {
		_naziv = charAlloc(naziv);
		_cijena = cijena;
		_kolicina = kolicina;
	}

	KupljeniArtikal(const KupljeniArtikal& src) {
		_naziv = charAlloc(src._naziv);
		_cijena = src._cijena;
		_kolicina = src._kolicina;
	}

	KupljeniArtikal(KupljeniArtikal&& src) {
		_naziv = src._naziv;
		src._naziv = nullptr;
		_cijena = src._cijena;
		_kolicina = src._kolicina;
	}

	~KupljeniArtikal() {
		delete[] _naziv;
	}

	// swap-and-copy idiom
	KupljeniArtikal& operator=(KupljeniArtikal src) {
		zamjeni(*this, src);
		return *this;
	}

	KupljeniArtikal& operator+=(const int& iznos) {
		_cijena += iznos;
		return *this;
	}

	KupljeniArtikal& operator++() {
		_kolicina += 1;
		return *this;
	}
};

class Racun {
	static int _brojacRacuna;
	const int _brojRacuna; // brojevi racuna krecu od 1
	KupljeniArtikal* _artikli; // niz povecavamo prilikom svakog dodavanja artikla
	int _trenutno;
public:
	Racun() : _brojRacuna(++_brojacRacuna) {
		_artikli = nullptr;
		_trenutno = 0;
	}

	Racun(const Racun& src) : _brojRacuna(++_brojacRacuna) {
		KupljeniArtikal* temp = new KupljeniArtikal[_trenutno + 1];
		_trenutno = src._trenutno;
		for (size_t i = 0; i < src._trenutno; i++) {
			temp[i] = src._artikli[i];
		}
	}
};

int Racun::_brojacRacuna = 0;

int main() {
	KupljeniArtikal cokolada("Milka", 2.29); // naziv i cijena artikla
	KupljeniArtikal sok("Jucy", 1.38);
	KupljeniArtikal cigarete("Drina", 4.32);
	KupljeniArtikal mlijeko("Meggle", 2.87);

	cokolada += 0.27; // povecavamo cijenu artikla, sada je cijena 2.56 BAM
	++cokolada; // povecavamo kolicinu artikla, sada je kolicina 2
	++sok;

	Racun racun;
	racun += cokolada; // dodajemo 2 cokolade po cijeni od 2.56 BAM
	racun += sok;
	racun += sok; // ako vise puta pokusamo dodati isti artikal, treba da se uveca samo njegova kolicina na racunu tj. artikli se ne smiju ponavljati
	racun += cigarete;
	racun += mlijeko;
	cout << racun << endl; // ispis racuna mozete vidjeti na slici

	int brojPronadjenih = 0;
	float ukupnaCijena = 5.10;

	cout << crt << "Artikli skuplji od >> " << ukupnaCijena << crt;
	// treba da vrati sve artikle cija je ukupna cijena na racunu (cijena * kolicina) veca od poslane tj. 5.10 BAM
	KupljeniArtikal* artikli = racun(ukupnaCijena, brojPronadjenih);
	if (artikli != nullptr) {
		for (size_t i = 0; i < brojPronadjenih; i++) {
			cout << artikli[i] << endl;
		}
	}


	delete[] artikli;
	artikli = nullptr;

}