#include <iostream>
using namespace std;

char* AlocirajNizKaraktera(const char* sadrzaj) {
	if (sadrzaj == nullptr) return nullptr;
	int velicina = strlen(sadrzaj) + 1;
	char* temp = new char[velicina];
	strcpy_s(temp, velicina, sadrzaj);
	return temp;
}

/* Genericka klasa kolekcija, koja ce moci sadrzavati razlicite tipove podataka. */
template <class T>
class Kolekcija {
	T* _sadrzaj; //sadrzaj kolekcija
	int _velicina; //trenutna velicina kolekcije – broj elemenata
	int _kapacitet; //kapacitet (koji ce se automatski prosirivati)
public:
	//defaultni konstruktor
	Kolekcija() {
		_velicina = 0;
		_kapacitet = 10;
		_sadrzaj = new T[_kapacitet];
	}

	//destruktor
	~Kolekcija() {
		delete[] _sadrzaj;
	}

	//dodavanje elementa u kolekciju
	void Dodaj(T element) {
		if (_velicina >= _kapacitet) {
			_kapacitet += 10;
			T* noviSadrzaj = new T[_kapacitet];

			for (size_t i = 0; i < _velicina; i++)
				noviSadrzaj[i] = _sadrzaj[i];

			delete[] _sadrzaj;
			_sadrzaj = noviSadrzaj;
		}

		_sadrzaj[_velicina++] = element;
	}


	//izbacivanje zadnjeg elementa iz kolekcije
	T Izbaci() {
		T* temp = new T[_kapacitet];
		T retr = _sadrzaj[_velicina--];

		for (size_t i = 0; i < _velicina; i++)
			temp[i] = _sadrzaj[i];

		delete[] _sadrzaj;
		_sadrzaj = temp;

		return retr;
	}

	//operator kojim pristupamo pojedinom elementu iz kolekcije preko indeksa
	T operator[](int index) const { return _sadrzaj[index]; }

	//vraca velicinu kolekcije
	int GetVelicina() const { return _velicina; }

	friend ostream& operator<<(ostream & COUT, const Kolekcija & obj) {
		for (size_t i = 0; i < obj._velicina; i++)
			cout << obj._sadrzaj[i] << "\n";
		return COUT;
	}
};

//a)
/* Klasa student ce sluziti kao primjer za dodavanje objekata u kolekciju */
class Student {
	int brojIndeksa;

public:
	int getBrojIndeksa();
	void setBrojIndeksa(int brojIndeksa);

	Kolekcija<int> ocjene;
	void ispisOcjena();
};

//b) 
/* Klasa osoba ce sluziti kao primjer za dodavanje objekata u kolekciju */

class osoba {
	char* _imePrezime;
public:
	osoba(const char* ip);
	//za vjezbu dodajte konstruktor kopije
	~osoba();
	const char* GetImePrezime() { return _imePrezime; }
};
osoba::osoba(const char* ip) {
	_imePrezime = AlocirajNizKaraktera(ip);
}
osoba::~osoba() {
	delete[] _imePrezime;
	_imePrezime = nullptr;
};


int main() {

	//demonstrirati rad svih implementiranih metoda za:

	   //kolekcija cijelih brojeva – i cijelih brojeva (običnih) i studentskih ocjena
	   //kolekcija<osoba *> ; //kolekcija pokazivača na objekte klase "osoba"

	Kolekcija<int> test;

	for (size_t i = 0; i < 30; i++)
		test.Dodaj(i);

	test.Izbaci();

	cout << test;

	system("pause");
	return 0;
}
