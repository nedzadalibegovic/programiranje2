#include <iostream>
using namespace std;

char* AlocirajNizKaraktera(const char* sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

class datum {
	int dan, mjesec, godina;
public:
	//default-ni konstruktor
	datum() {
		dan = 0;
		mjesec = 0;
		godina = 0;
	}
	//korisnicki konstruktor
	datum(int d, int m, int g) {
		dan = d;
		mjesec = m;
		godina = g;

	}
	//konstruktor kopije
	datum(const datum& d) {
		dan = d.dan;
		mjesec = d.mjesec;
		godina = d.godina;
	}
	//destruktor
	~datum() {}
	//operator <<
	friend ostream& operator << (ostream& COUT, const datum& obj) {
		COUT << obj.dan << "." << obj.mjesec << "." << obj.godina << "." << " ";
		return COUT;

	}

};
//Klasa Viza je osnovna klasa � potrebno je dopisati sve metode
class Viza {
protected:
	char* _drzava;
	datum _vazenjeOD;
	datum _vazenjeDO;
	char* _napomena;
public:
	//korisni�ki konstruktor
	Viza(const char* drzava, datum _OD, datum _DO, const char* napomena = nullptr)
		: _vazenjeOD(_OD), _vazenjeDO(_DO) {
		_drzava = AlocirajNizKaraktera(drzava);
		_napomena = AlocirajNizKaraktera(napomena);
	}

	Viza(const Viza& org) : _vazenjeOD(org._vazenjeOD), _vazenjeDO(org._vazenjeDO) {
		_drzava = AlocirajNizKaraktera(org._drzava);
		_napomena = AlocirajNizKaraktera(org._napomena);
	}

	//destruktor
	~Viza() {
		delete[] _drzava;
		delete[] _napomena;
	}

	//metoda GetVazenjaOD - vraca objekt tipa datum - datum od kad va�i viza
	datum GetVazenjeOD() { return _vazenjeOD; }

	//metoda GetVazenjaDO - vraca objekt tipa datum - datum do kad va�i viza
	datum GetVazenjeDO() { return _vazenjeDO; }

	//metoda vra�a napomenu
	char* GetNapomena() { return _napomena; }

	//preklopiti operator <<
	friend ostream& operator << (ostream& COUT, Viza& obj) {
		COUT << "Drzava: " << obj._drzava << "\nVazi od " <<
			obj._vazenjeOD << "do " << obj._vazenjeDO << "\nNapomena: ";
		if (obj._napomena)
			COUT << obj._napomena << "\n";

		return COUT;
	}

};

//Klasa PoslovnaViza je izvedena klasa � potrebno je dopisati sve metode
class PoslovnaViza : public Viza {
	char* _kompanija; //naziv kompanije koja potvr�uje da posluje sa aplikantom
public:
	//korisni�ki konstruktor
	PoslovnaViza(const char* drzava, datum _OD, datum _DO, const char* kompanija, const char* napomena = nullptr)
		: Viza(drzava, _OD, _DO, napomena) {
		_kompanija = AlocirajNizKaraktera(kompanija);
	}

	PoslovnaViza(const PoslovnaViza& org) : Viza(org) {
		_kompanija = AlocirajNizKaraktera(org._kompanija);
	}

	//preklopiti operator <<
	friend ostream& operator << (ostream& COUT, PoslovnaViza& obj) {
		COUT << "Kompanija: " << obj._kompanija << "\n" << (Viza&)obj;
		return COUT;
	}
	//destruktor
	~PoslovnaViza() {
		delete[] _kompanija;
	}

};

//Klasa TuristickaViza je izvedena klasa � potrebno je dopisati sve metode

class TuristickaViza : public Viza {
	char* _adresa; //adresa hotele ili drugog smje�taja na kojoj �e aplikant boraviti
public:
	//korisni�ki konstruktor
	TuristickaViza(const char* drzava, datum _OD, datum _DO, const char* adresa, const char* napomena = nullptr)
		: Viza(drzava, _OD, _DO, napomena) {
		_adresa = AlocirajNizKaraktera(adresa);
	}

	TuristickaViza(const TuristickaViza& org) : Viza(org) {
		_adresa = AlocirajNizKaraktera(org._adresa);
	}

	//destruktor
	~TuristickaViza() {
		delete[] _adresa;
	}

	//preklopiti operator <<
	friend ostream& operator << (ostream& COUT, TuristickaViza& obj) {
		COUT << "Adresa: " << obj._adresa << "\n" << (Viza&)obj;
		return COUT;
	}

};

template<class T1, class T2, int max>
class FITKolekcija {
	int* _trenutno;
	T1* _elementi1[max] = { nullptr };
	T2* _elementi2[max] = { nullptr };
public:

	//Kreirati potrebne  konstruktore i destruktore
	FITKolekcija() { _trenutno = new int(0); }

	FITKolekcija(FITKolekcija& k) {
		_trenutno = new int(*k.trenutno);
		for (size_t i = 0; i < *_trenutno; i++) {
			_elementi1[i] = new T1(*k._elementi1[i]);
			_elementi2[i] = new T2(*k._elementi2[i]);
		}
	}

	~FITKolekcija() {
		if (_trenutno) {
			for (size_t i = 0; i < *_trenutno; i++) {
				delete _elementi1[i]; _elementi1[i] = nullptr;
				delete _elementi2[i]; _elementi2[i] = nullptr;
			}
			delete _trenutno; _trenutno = nullptr;
		}
	}

	//Preklopiti operator() na na�in da omogu�i dodavanje novih elemenata u kolekciju
	void operator () (T1 e1, T2 e2) {
		if (*_trenutno + 1 >= max)
			return;

		_elementi1[*_trenutno] = new T1(e1);
		_elementi2[*_trenutno] = new T2(e2);
		++(*_trenutno);
	}

	//metoda get za trenutni broj elemenata u kolekciji
	int trenutno() { return *_trenutno; }

	//Preklopiti operator za ispis.
	friend ostream& operator << (ostream & COUT, FITKolekcija & k) {
		if (k._trenutno) {
			for (size_t i = 0; i < *k._trenutno; i++)
				COUT << *k._elementi1[i] << " " << *k._elementi2[i] << "\n";
		}
		return COUT;
	}

	//metoda koja uklanja element na odabranoj poziciji
	void Uklonielement(int pozicija) {
		delete _elementi1[pozicija];
		delete _elementi2[pozicija];

		for (size_t i = pozicija; i < (*_trenutno) - 1; i++) {
			_elementi1[i] = _elementi1[i + 1];
			_elementi2[i] = _elementi2[i + 1];
		}

		--(*_trenutno);
	}

};

class Aplikant {
	char* _imePrezime;
	datum  _datumRodjenja;
	char* _brojPasosa;

public:
	FITKolekcija<PoslovnaViza, bool, 3> _vizePoslovne; //bool se odnosi na to da li je viza odobrena ili ne
	FITKolekcija< TuristickaViza, bool, 3> _vizeTuristicke;

	//kreirati potrebne konstruktore i destruktor
	Aplikant(const char* imePrezime, datum datumRodjenja, const char* brojPasosa)
		: _datumRodjenja(datumRodjenja) {
		_imePrezime = AlocirajNizKaraktera(imePrezime);
		_brojPasosa = AlocirajNizKaraktera(brojPasosa);
	}

	~Aplikant() {
		delete[] _imePrezime;
		delete[] _brojPasosa;
	}

	//preklopiti operator <<
	friend ostream& operator<<(ostream& COUT, Aplikant& obj) {
		COUT << "Ime i prezime: " << obj._imePrezime << "\nDatum rodjenja: "
			<< obj._datumRodjenja << "\nBroj pasosa: " << obj._brojPasosa <<
			"\nPoslovne vize: " << obj._vizePoslovne << "\nTuristicke vize: "
			<< obj._vizeTuristicke << "\n";
		return COUT;
	}

};

int main() {
	//demonstrirati rad svih kreiranih metoda;
	datum prvi(12, 12, 1990), drugi(12, 12, 1991);

	Viza obicna("BiH", prvi, drugi, "napomena primjer");
	cout << obicna;

	cout << "\n";

	PoslovnaViza poslovna("SAD", prvi, drugi, "Tesla Inc.", "Tesla Employee");
	cout << poslovna;

	cout << "\n";

	TuristickaViza turisticka("Barbados", prvi, drugi, "Downing Street 22");
	cout << turisticka;

	cout << "\n<--Aplikant-->\n";

	Aplikant Hamo("Hamo Pipa", prvi, "1029384756");
	Hamo._vizePoslovne(poslovna, true);
	Hamo._vizeTuristicke(turisticka, false);
	cout << Hamo;

	cout << "\n";

	system("pause>0");
	return 0;
}
