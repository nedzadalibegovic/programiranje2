#include<iostream>
using namespace std;

//globalna funkcija za alociranje niza karaktera
char* AlocirajNizKaraktera(const char* sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

// Genericka klasa kolekcija
template <class T>
class Kolekcija {
	T* _sadrzaj; // sadrzaj kolekcija
	int _velicina; // trenutna velicina kolekcije – broj elemenata
	int _kapacitet; // kapacitet (koji ce se automatski prosirivati)
public:
	// defaultni konstruktor
	Kolekcija() {
		_velicina = 0;
		_kapacitet = 10;
		_sadrzaj = new T[_kapacitet];
	}

	// destruktor
	~Kolekcija() {
		delete[] _sadrzaj;
	}

	// dodavanje elementa u kolekciju
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


	// izbacivanje zadnjeg elementa iz kolekcije
	T Izbaci() {
		T* temp = new T[_kapacitet];
		T retr = _sadrzaj[_velicina--];

		for (size_t i = 0; i < _velicina; i++)
			temp[i] = _sadrzaj[i];

		delete[] _sadrzaj;
		_sadrzaj = temp;

		return retr;
	}

	// operator kojim pristupamo pojedinom elementu iz kolekcije preko indeksa
	T operator[](int index) const { return _sadrzaj[index]; }

	// vraca velicinu kolekcije
	int GetVelicina() const { return _velicina; }

	friend ostream& operator<<(ostream & COUT, const Kolekcija & obj) {
		for (size_t i = 0; i < obj._velicina; i++)
			cout << obj._sadrzaj[i] << "\n";
		return COUT;
	}
};

enum Status { redovan, dl, vanredan }; // enumeracija – pobrojani tip podatka
const char* StatusOut[] = { "Redovan", "DL", "Vanredan" };

ostream& operator<<(ostream& COUT, const Status& obj) {
	COUT << StatusOut[obj];
	return COUT;
}

class Student {
	int brojIndeksa;
	char* imePrezime; // koristiti funkciju AlocirajNizKaraktera
	Status S; // moguce vrijednosti redovan, dl, vanredan

public:
	Kolekcija <int> ocjene; // studentove ocjene su tipa kolekcija

	// kreirati potrebne konstruktore i destruktor
	Student(int brojIndeksa, const char* imePrezime, Status S = redovan) {
		this->brojIndeksa = brojIndeksa;
		this->imePrezime = AlocirajNizKaraktera(imePrezime);
		this->S = S;
	}

	~Student() {
		delete[] imePrezime;
	}

	// preklopiti operator << za ispis obilježja objekta student 
	friend ostream& operator<<(ostream& COUT, const Student& obj) {
		COUT << "IB " << obj.brojIndeksa << " " << obj.imePrezime << " " << obj.S << "\n";
	}
};

int main() {
	//demonstrirati rad svih kreiranih metoda

	system("pause>0");
	return 0;
}

