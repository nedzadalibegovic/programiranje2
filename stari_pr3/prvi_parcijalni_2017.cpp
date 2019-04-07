#include <iostream>
using namespace std;
/****************************************************************************
1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU
RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U
TESTNOM CODE-U, OSIM U SLUČAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE,
POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
5. BEZ OBZIRA NA TO DA LI SU ISPITNI ZADACI URAĐENI, SVI STUDENTI KOJI SU PRISTUPILI ISPITU
MORAJU PREDATI SVOJ RAD
6. ZA POTREBE TESTIRANJA, UNUTAR MAIN FUNKCIJE MOZETE DODAVATI NOVE TESTNE PODATKE
****************************************************************************/
//narednu liniju code-a ignorisite, osim u slucaju da vam bude predstavljala smetnje u radu
#pragma warning(disable:4996)
const char* crt = "\n----------------------------------------------------\n";

char* charAlloc(const char* src) {
	if (src == nullptr)
		return nullptr;
	int len = strlen(src) + 1;
	char* temp = new char[len];
	strcpy_s(temp, len, src);
	return temp;
}

class Datum {
	int* _dan, * _mjesec, * _godina;
public:
	Datum(int d, int m, int g) {
		_dan = new int(d);
		_mjesec = new int(m);
		_godina = new int(g);
	}

	Datum(const Datum& src) {
		_dan = new int(*src._dan);
		_mjesec = new int(*src._mjesec);
		_godina = new int(*src._godina);
	}

	~Datum() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}

	friend ostream& operator<<(ostream& COUT, Datum obj) {
		COUT << *obj._dan << "/" << *obj._mjesec << "/" << *obj._godina;
		return COUT;
	}

	friend void zamjeni(Datum& lhs, Datum& rhs) {
		swap(lhs._dan, rhs._dan);
		swap(lhs._mjesec, rhs._mjesec);
		swap(lhs._godina, rhs._godina);
	}

	// copy-and-swap
	Datum& operator=(Datum src) {
		zamjeni(*this, src);
		return *this;
	}
};

template<class T, int velicina>
class FITArray {
	T _niz[velicina];
	int _trenutno;
	bool _dozvoliDupliciranje;

	bool isDuplicate(const T& item) {
		for (size_t i = 0; i < velicina; i++) {
			if (item == _niz[i])
				return true;
		}
		return false;
	}
public:
	//OSTALE FUNKCIJE CLANICE DEFINISATI VAN TEMPLATE KLASE
	FITArray(bool dozvoliDupliciranje = true) {
		_dozvoliDupliciranje = dozvoliDupliciranje;
		_trenutno = 0;
	}

	bool operator+=(const T & item) {
		// provjeri ima li mjesta
		if (_trenutno + 1 < velicina) {
			// je li dozvoljeno dupliciranje?
			if (_dozvoliDupliciranje) {
				_niz[_trenutno] = item;
				_trenutno += 1;
				return true;
				// ako nije, je li duplikat?
			} else if (isDuplicate(item)) {
				return false;
				// ako nije duplikat, dodaj
			} else {
				_niz[_trenutno] = item;
				_trenutno += 1;
				return true;
			}
		}
	}

	FITArray& operator=(FITArray src) {
		swap(_niz, src._niz);
		swap(_trenutno, src._trenutno);
		swap(_dozvoliDupliciranje, src._dozvoliDupliciranje);
		return *this;
	}

	void operator-=(const T & item) {
		bool change = false;
		for (size_t i = 0; i < GetTrenutno(); i++) {
			if (item == _niz[i]) {
				swap(_niz[i], _niz[i + 1]);
				change = true;
			}
		}
		if (change)
			_trenutno -= 1;
	}
	
	FITArray operator()(const int& start, const int& end) {
		FITArray temp(_dozvoliDupliciranje);
		int stop = GetTrenutno() - 1;

		if (end < _trenutno)
			stop = end;

		for (size_t i = start; i <= stop; i++)
			temp += _niz[i];

		return temp;
	}

	int GetTrenutno() { return _trenutno; }

	T* GetNiz() { return _niz; }

	friend ostream& operator<<(ostream& COUT, FITArray obj) {
		for (size_t i = 0; i < obj.GetTrenutno(); i++)
			COUT << obj.GetNiz()[i] << ", ";
		return COUT;
	}
};

class PolozeniPredmet {
	char* _naziv;
	int _ocjena;
	Datum _datumPolaganja;
public:
	PolozeniPredmet() :_datumPolaganja(1,1,1) {}

	PolozeniPredmet(Datum datumPolaganja, const char* naziv, int ocjena) : _datumPolaganja(datumPolaganja) {
		_naziv = charAlloc(naziv);
		_ocjena = ocjena;
	}

	PolozeniPredmet(const PolozeniPredmet& src) : _datumPolaganja(src._datumPolaganja) {
		_naziv = charAlloc(src._naziv);
		_ocjena = src._ocjena;
	}

	~PolozeniPredmet() { delete[] _naziv; _naziv = nullptr; }

	friend ostream& operator<<(ostream& COUT, PolozeniPredmet& obj) {
		COUT << obj._naziv << "(" << obj._ocjena << ")" << obj._datumPolaganja << endl;
		return COUT;
	}

	bool operator==(const PolozeniPredmet& rhs) const {
		if (!strcmp(_naziv, rhs._naziv))
			return true;
		return false;
	}

	friend void zamjeni(PolozeniPredmet& lhs, PolozeniPredmet& rhs) {
		swap(lhs._naziv, rhs._naziv);
		swap(lhs._ocjena, rhs._ocjena);
		lhs._datumPolaganja = rhs._datumPolaganja;
	}

	PolozeniPredmet& operator=(PolozeniPredmet src) {
		zamjeni(*this, src);
		return *this;
	}

	int getOcjena() { return _ocjena; }
};

class Student {
	static int _indeksCounter; //sluzi za odredjivanje narednog broja indeksa koji ce biti dodijeljen studentu, pocevsi od 160000
	const int _indeks;
	char* _imePrezime;
	FITArray<PolozeniPredmet, 40> _polozeniPredmeti;
public:
	Student(const char* imePrezime) : _indeks(_indeksCounter++) {
		_imePrezime = charAlloc(imePrezime);
	}

	Student(const Student& src) : _polozeniPredmeti(src._polozeniPredmeti), _indeks(src._indeks) {
		_imePrezime = charAlloc(src._imePrezime);
	}

	~Student() {
		delete[] _imePrezime; _imePrezime = nullptr;
	}
	friend ostream& operator<<(ostream& COUT, Student& obj) {
		COUT << obj._indeks << " " << obj._imePrezime << endl << obj._polozeniPredmeti;
		return COUT;
	}

	void DodajPredmet(PolozeniPredmet predmet) {
		_polozeniPredmeti += predmet;
	}

	float GetProsjek() {
		float prosjek = 0.0f;
		for (size_t i = 0; i < _polozeniPredmeti.GetTrenutno(); i++) {
			prosjek += _polozeniPredmeti.GetNiz()[i].getOcjena();
		}
		return prosjek / _polozeniPredmeti.GetTrenutno();
	}

	friend void zamjeni(Student& lhs, Student& rhs) {
		//swap(lhs._indeks, rhs._indeks);
		swap(lhs._imePrezime, rhs._imePrezime);
		lhs._polozeniPredmeti = rhs._polozeniPredmeti;
	}

	Student& operator=(Student src) {
		zamjeni(*this, src);
		return *this;
	}
};

int Student::_indeksCounter = 180000;

int main() {
	const int max = 20;
	Datum jucer(20, 11, 2017), danas(21, 11, 2017), sutra(22, 11, 2017);

	cout << jucer << danas << sutra << endl;
	jucer = danas;
	cout << jucer << danas << sutra << endl;

	//parametar tipa bool odredjuje da li je u nizu dozvoljeno dupliciranje elemenata
	FITArray<int, max> nizIntegera(false);
	for (size_t i = 0; i < max - 1; i++)
		nizIntegera += i;//dodaje novog clana niza
	if (!(nizIntegera += 6))//pokusavamo dodati dupli clan niza
		cout << "Element nije dodan u niz" << endl;
	cout << crt << nizIntegera << crt; //ispisuje sve clanove niza
	nizIntegera -= 9; //uklanja clan niza sa vrijednoscu 9
	nizIntegera -= 17;
	FITArray<int, max> noviNizIntegera(nizIntegera);
	cout << crt << noviNizIntegera << crt;

	/*parametri odredjuju lokacije (indekse u nizu) elemenata OD - DO koje je potrebno vratiti. u
	slucaju da u nizu ne postoji trazeni broj elemenata funkcija treba da vrati sve element od
	lokacije OD pa do posljednje dostupnog elementa */
	cout << "Clanovi niza od lokacije 2 do lokacije 5 su -> " << noviNizIntegera(2, 5) << crt;
	cout << noviNizIntegera(2, 5) << endl;

	Student adel("Adel Handzic"), jasmin("Jasmin Azemovic");
	PolozeniPredmet prII(jucer, "PRII", 8), prIII(sutra, "PRIII", 7);
	adel.DodajPredmet(prII);
	adel.DodajPredmet(prIII);
	cout << adel << endl;
	//vraca prosjecnu ocjenu studenta
	cout << "Prosjecna ocjena -> " << adel.GetProsjek() << crt;
	jasmin = adel;
	cout << jasmin << endl;
	cout << "Prosjecna ocjena -> " << jasmin.GetProsjek() << crt;
}