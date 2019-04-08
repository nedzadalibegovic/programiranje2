// 1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
// 2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR CE BITI OZNACENO KAO "RE"
// 3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA
#include <iostream>
#include <algorithm>

using namespace std;

char* charAlloc(const char* ptr) {
	int size = strlen(ptr) + 1;
	char* temp = new char[size];
	strcpy_s(temp, size, ptr);
	return temp;
}

template<class T1, class T2>
class Kolekcija {
	T1* _elementi1;
	T2* _elementi2;
	int _trenutnoElemenata;

	void zamjena(Kolekcija& rhs) {
		swap(_elementi1, rhs._elementi1);
		swap(_elementi2, rhs._elementi2);
		swap(_trenutnoElemenata, rhs._trenutnoElemenata);
	}
public:
	Kolekcija(T1* elementi1 = nullptr, T2* elementi2 = nullptr, int trenutnoElemenata = 0) {
		_elementi1 = elementi1;
		_elementi2 = elementi2;
		_trenutnoElemenata = trenutnoElemenata;
	}

	Kolekcija(const Kolekcija& src) {
		_trenutnoElemenata = src._trenutnoElemenata;
		_elementi1 = new T1[src._trenutnoElemenata];
		_elementi2 = new T2[src._trenutnoElemenata];

		for (size_t i = 0; i < _trenutnoElemenata; i++) {
			_elementi1[i] = src._elementi1[i];
			_elementi2[i] = src._elementi2[i];
		}
	}

	Kolekcija(Kolekcija&& src) {
		_elementi1 = src._elementi1;
		src._elementi1 = nullptr;

		_elementi2 = src._elementi2;
		src._elementi2 = nullptr;

		_trenutnoElemenata = src._trenutnoElemenata;
	}

	~Kolekcija() {
		delete[] _elementi1; _elementi1 = nullptr;
		delete[] _elementi2; _elementi2 = nullptr;
	}

	void AddElement(const T1& a, const T2& b) {
		T1* temp1 = new T1[_trenutnoElemenata + 1];
		T2* temp2 = new T2[_trenutnoElemenata + 1];

		for (size_t i = 0; i < _trenutnoElemenata; i++) {
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];
		}

		temp1[_trenutnoElemenata] = a;
		temp2[_trenutnoElemenata] = b;
		_trenutnoElemenata += 1;

		delete[] _elementi1;
		delete[] _elementi2;

		_elementi1 = temp1;
		_elementi2 = temp2;
	}

	void RemoveElement(const int& last) {
		T1* temp1 = new T1[_trenutnoElemenata - last];
		T2* temp2 = new T2[_trenutnoElemenata - last];

		for (size_t i = 0; i < _trenutnoElemenata - last; i++) {
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];
		}

		_trenutnoElemenata -= last;

		delete[] _elementi1;
		delete[] _elementi2;

		_elementi1 = temp1;
		_elementi2 = temp2;

	}

	int getTrenutno() const { return _trenutnoElemenata; }
	T1* getNiz1() const { return _elementi1; }
	T2* getNiz2() const { return _elementi2; }

	Kolekcija& operator=(Kolekcija src) {
		zamjena(src);
		return *this;
	}

	friend ostream& operator<<(ostream& COUT, const Kolekcija& obj) {
		for (size_t i = 0; i < obj.getTrenutno(); i++) {
			COUT << obj.getNiz1()[i] << " " << obj.getNiz2()[i] << "\n";
		}
		return COUT;
	}
};

class Datum {
	int* _dan, * _mjesec, * _godina;

	void zamjeni(Datum& lhs) {
		swap(_dan, lhs._dan);
		swap(_mjesec, lhs._mjesec);
		swap(_godina, lhs._godina);
	}
public:
	Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
	}

	Datum(const Datum& src) {
		_dan = new int(*src._dan);
		_mjesec = new int(*src._mjesec);
		_godina = new int(*src._godina);
	}

	Datum(Datum&& src) noexcept {
		_dan = src._dan;
		src._dan = nullptr;

		_mjesec = src._mjesec;
		src._mjesec = nullptr;

		_godina = src._godina;
		src._godina = nullptr;
	}

	~Datum() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}

	Datum& operator=(Datum src) {
		zamjeni(src);
		return *this;
	}

	friend ostream& operator<< (ostream& COUT, Datum& obj) {
		COUT << *obj._dan << " " << *obj._mjesec << " " << *obj._godina;
		return COUT;
	}
};

class Student {
	char* _imePrezime;
	Datum* _datumRodjenja;

	void zamjeni(Student& lhs) {
		swap(_imePrezime, lhs._imePrezime);
		swap(_datumRodjenja, lhs._datumRodjenja);
	}
public:
	Student(const char* imePrezime = "---", Datum d = Datum()) {
		int size = strlen(imePrezime) + 1;
		_imePrezime = new char[size];
		strcpy_s(_imePrezime, size, imePrezime);
		_datumRodjenja = new Datum(d);
	}

	Student(const Student& src) {
		_imePrezime = charAlloc(src._imePrezime);
		_datumRodjenja = new Datum(*src._datumRodjenja);
	}

	Student(Student&& src) noexcept {
		_imePrezime = src._imePrezime;
		src._imePrezime = nullptr;

		_datumRodjenja = src._datumRodjenja;
		src._datumRodjenja = nullptr;
	}

	Student& operator=(Student src) {
		zamjeni(src);
		return *this;
	}

	bool operator==(const Student& lhs) const {
		if (!strcmp(_imePrezime, lhs._imePrezime))
			return true;
		return false;
	}

	~Student() {
		delete[] _imePrezime;
		_imePrezime = nullptr;
		delete _datumRodjenja;
		_datumRodjenja = nullptr;
	}

	friend ostream& operator<<(ostream& COUT, const Student& obj) {
		COUT << obj._imePrezime;
		return COUT;
	}
};

class Ispit {
	Datum _datumOdrzavanja;
	char* _opisIspita;
	Kolekcija<Student, Datum> _prijave;
	Kolekcija<Student, int> _rezultati;
public:
	Ispit(const char* opis, Datum datum) : _datumOdrzavanja(datum) {
		_opisIspita = charAlloc(opis);
	}

	Ispit(const Ispit& src) : _datumOdrzavanja(src._datumOdrzavanja), _prijave(src._prijave), _rezultati(src._rezultati) {
		_opisIspita = charAlloc(src._opisIspita);
	}

	bool DodajPrijavu(const Student& student, const Datum& datum) {
		for (size_t i = 0; i < _prijave.getTrenutno(); i++) {
			if (_prijave.getNiz1()[i] == student) {
				return false;
			}
		}
		_prijave.AddElement(student, datum);
		return true;
	}

	void DodajRezultat(const Student& student, const int& ocjena) {
		bool pronadjen = false;

		// provjeri je li student prijavljen
		for (size_t i = 0; i < _prijave.getTrenutno(); i++) {
			if (_prijave.getNiz1()[i] == student) {
				pronadjen = true;
			}
		}

		if (pronadjen) {
			// provjeri ima li student vec dodan rezultat
			for (size_t i = 0; i < _rezultati.getTrenutno(); i++) {
				if (_rezultati.getNiz1()[i] == student) {
					return;
				}
			}
			// ako nije, dodaj ga
			_rezultati.AddElement(student, ocjena);
		}
	}

	// uzeto sa githuba
	void Sortiraj() {
		for (int i = 0; i < _rezultati.getTrenutno() - 1; i++)
			for (int j = i + 1; j < _rezultati.getTrenutno(); j++)
				if (_rezultati.getNiz2()[i] < _rezultati.getNiz2()[j]) {
					int tempO = _rezultati.getNiz2()[i];
					Student tempS = _rezultati.getNiz1()[i];

					_rezultati.getNiz2()[i] = _rezultati.getNiz2()[j];
					_rezultati.getNiz1()[i] = _rezultati.getNiz1()[j];

					_rezultati.getNiz2()[j] = tempO;
					_rezultati.getNiz1()[j] = tempS;
				}
	}

	// uzeto sa githuba
	void ZakljuciRezultate() {
		for (int i = 0; i < _prijave.getTrenutno(); i++) {
			bool pronaden = false;
			for (int j = 0; j < _rezultati.getTrenutno(); j++)
				if (_prijave.getNiz1()[i] == _rezultati.getNiz1()[j]) {
					pronaden = true;
					break;
				}

			if (!pronaden) {
				_rezultati.AddElement(_prijave.getNiz1()[i], 5);
			}
		}
	}

	friend ostream& operator<<(ostream& COUT, const Ispit& ispit) {
		COUT << ispit._rezultati;
		return COUT;
	}
};

const char* crt = "\n--------------------------------------------------\n";

void main() {
	//REGIONI olaksavaju organizaciju programskog code-a, te ih mozete ukloniti ukoliko vam otezavaju preglednost

#pragma region TestiranjeKolekcije
	Kolekcija<int, double> kolekcija1;
	for (size_t i = 0; i < 50; i++)
		kolekcija1.AddElement(i, i + 0.3);
	cout << kolekcija1 << endl;
	cout << crt;

	Kolekcija<int, double> kolekcija2;
	kolekcija2 = kolekcija1;
	kolekcija1.RemoveElement(2);//UMANJITI VELI�INU NIZA
	cout << kolekcija2 << crt;

	if (kolekcija1.getTrenutno() == kolekcija2.getTrenutno())
		cout << "ISTI BROJ ELEMENATA" << endl;

	Kolekcija<int, double> kolekcija3(kolekcija2);
	cout << kolekcija3 << crt;
#pragma endregion

#pragma region TestiranjeDatuma
	Datum danas(26, 11, 2015);
	Datum sutra(danas);
	Datum prekosutra;
	prekosutra = danas;
	cout << danas << endl << sutra << endl << prekosutra << crt;
#pragma endregion

#pragma region TestiranjeStudenta
	Student denis("Denis Music", Datum(26, 11, 1990));
	Student jasmin("Jasmin Azemovic", Datum(22, 11, 1990));
	Student goran;
	goran = jasmin;
	Student adel("Adel Handzic", Datum(25, 8, 1990));
	Student marija("Marija Herceg", Datum(15, 6, 1990));
#pragma endregion

#pragma region TestiranjeIspita
	Ispit prIII("PRIII::26.11.2015", danas);
	//DodajPrijavu - dodaje novog studenta u listu prijavljenih za ispti. 
	//onemoguciti dodavanje dva ista studenta
	if (prIII.DodajPrijavu(denis, danas))
		cout << denis << " DODAT na spisak" << endl;
	if (prIII.DodajPrijavu(jasmin, danas))
		cout << jasmin << " DODAT na spisak" << endl;
	if (prIII.DodajPrijavu(goran, danas))
		cout << jasmin << " DODAT na spisak" << endl;
	if (prIII.DodajPrijavu(adel, danas))
		cout << adel << " DODAT na spisak" << endl;
	if (prIII.DodajPrijavu(marija, danas))
		cout << adel << " DODAT na spisak" << endl;

	cout << crt << endl;
	/*DodajRezultat - dodaje ocjenu koju je student ostvario na ispitu.
	za dodavanje ocjene student je prethodno trebao biti prijavljen na ispit
	*/
	prIII.DodajRezultat(goran, 7);
	prIII.DodajRezultat(jasmin, 6);
	prIII.DodajRezultat(adel, 8);
	prIII.DodajRezultat(marija, 9);

	/*Sortiraj - sortira rezultate ispita prema ocjeni*/
	prIII.Sortiraj();
	/*ZakljuciRezultate - dodaje ocjenu 5 svim studentima koji su prijavili ispit
	a nije im evidentirana ocjena*/
	prIII.ZakljuciRezultate();
	//rezultati ispita se smiju ispisivati jedino ukoliko su prethodno zakljuceni
	cout << prIII << crt;

	Ispit prIII_2(prIII);
	cout << prIII_2 << crt;
#pragma endregion
}