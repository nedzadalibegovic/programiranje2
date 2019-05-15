#include<iostream>
using namespace std;

template<class T1, class T2>
class Kolekcija {
	T1* _elementi1;
	T2* _elementi2;
	int _trenutno;
public:
	Kolekcija() {
		_trenutno = 0;
		_elementi1 = nullptr;
		_elementi2 = nullptr;
	}

	Kolekcija(const Kolekcija& src) {
		_trenutno = src._trenutno;

		_elementi1 = new T1[_trenutno];
		_elementi2 = new T2[_trenutno];

		for (size_t i = 0; i < _trenutno; i++) {
			_elementi1[i] = src._elementi1[i];
			_elementi2[i] = src._elementi2[i];
		}
	}

	~Kolekcija() {
		delete[] _elementi1;
		_elementi1 = nullptr;
		delete[] _elementi2;
		_elementi2 = nullptr;
	}

	Kolekcija& operator=(const Kolekcija& src) {
		if (this == &src)
			return *this;

		_trenutno = src._trenutno;

		delete[] _elementi1;
		delete[] _elementi2;

		_elementi1 = new T1[_trenutno];
		_elementi2 = new T2[_trenutno];

		for (size_t i = 0; i < _trenutno; i++) {
			_elementi1[i] = src._elementi1[i];
			_elementi2[i] = src._elementi2[i];
		}

		return *this;
	}

	void DodajElemente(const T1& el1, const T2& el2) {
		T1* temp1 = new T1[_trenutno + 1];
		T2* temp2 = new T2[_trenutno + 1];

		for (int i = 0; i < _trenutno; i++) {
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];
		}

		delete[] _elementi1;
		delete[] _elementi2;

		_elementi1 = temp1;
		_elementi2 = temp2;

		_elementi1[_trenutno] = el1;
		_elementi2[_trenutno] = el2;

		_trenutno++;
	}

	int getTrenutno() const { return _trenutno; }
	T1& getElement1(int index) const { return _elementi1[index]; }
	T2& getElement2(int index) const { return _elementi2[index]; }

	friend ostream& operator<<(ostream& out, const Kolekcija& kol) {
		for (size_t i = 0; i < kol._trenutno; i++) {
			out << kol._elementi1[i] << "\t" << kol._elementi2[i] << endl;
		}
		return out;
	}
};

char* AlocirajNizKaraktera(const char* sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

class Datum {
	int _dan, _mjesec, _godina;
public:
	Datum() {
		_dan = 0;
		_mjesec = 0;
		_godina = 0;
	}

	Datum(int dan, int mjesec, int godina) {
		_dan = dan;
		_mjesec = mjesec;
		_godina = godina;
	}

	int getMjesec() const { return _mjesec; }

	friend ostream& operator<<(ostream& out, const Datum& obj) {
		out << obj._dan << "." << obj._mjesec << "." << obj._godina;
		return out;
	}
};

//U programu implementirati nasljeđivanje između odgovarajućih klasa
//Klasu Osoba deklarisati kao apstraktnu .
class Osoba {
	char* _ime;
	char* _prezime;
	char* _adresa;
	char* _telefon;
public:
	Osoba(const char* ime, const char* prezime, const char* adresa, const char* telefon) {
		_ime = AlocirajNizKaraktera(ime);
		_prezime = AlocirajNizKaraktera(prezime);
		_adresa = AlocirajNizKaraktera(adresa);
		_telefon = AlocirajNizKaraktera(telefon);
	}

	Osoba(const Osoba& o) {
		_ime = AlocirajNizKaraktera(o._ime);
		_prezime = AlocirajNizKaraktera(o._prezime);
		_adresa = AlocirajNizKaraktera(o._adresa);
		_telefon = AlocirajNizKaraktera(o._telefon);
	}

	char* getIme() const { return _ime; }
	char* getPrezime() const { return _prezime; }

	virtual ~Osoba() {
		delete[] _ime;
		_ime = nullptr;

		delete[] _prezime;
		_prezime = nullptr;

		delete[] _adresa;
		_adresa = nullptr;

		delete[] _telefon;
		_telefon = nullptr;
	}

	virtual void info() = 0 {
		cout << "Ime i prezime: " << _ime << " " << _prezime << endl;
		cout << "Adresa: " << _adresa << endl;
		cout << "Telefon: " << _telefon << endl;
	}
};

class Proizvod {
	char* _naziv;
	char* _opis;
	double _cijena;
public:
	Proizvod() {
		_naziv = nullptr;
		_opis = nullptr;
		_cijena = 0;
	}

	Proizvod(const Proizvod& src) {
		_naziv = AlocirajNizKaraktera(src._naziv);
		_opis = AlocirajNizKaraktera(src._opis);
		_cijena = src._cijena;
	}

	Proizvod(const char* naziv, const char* opis, double cijena) {
		_naziv = AlocirajNizKaraktera(naziv);
		_opis = AlocirajNizKaraktera(opis);
		_cijena = cijena;
	}

	Proizvod& operator=(Proizvod src) {
		swap(_naziv, src._naziv);
		swap(_opis, src._opis);
		swap(_cijena, src._cijena);
		return *this;
	}

	~Proizvod() {
		delete[] _naziv;
		_naziv = nullptr;

		delete[] _opis;
		_opis = nullptr;
	}

	double getCijena() const { return _cijena; }

	friend ostream& operator<<(ostream& out, const Proizvod& p) {
		cout << "Naziv: " << p._naziv << endl;
		cout << "Opis: " << p._opis << endl;
		cout << "Cijena: " << p._cijena << endl;
		return out;
	}
};

class Narudzba {
	Datum _datum; //Format: dd.MM.yyyy.
	Kolekcija<Proizvod, int> _proizvodi; //Podaci o naručenim proizvodima i količinama
public:
	//Potrebne osnovne funkcije za rad sa klasom
	Narudzba() {}
	Narudzba(int dan, int mjesec, int godina) : _datum(dan, mjesec, godina) {}
	Narudzba(const Narudzba& src) : _datum(src._datum), _proizvodi(src._proizvodi) {}

	Narudzba& operator=(Narudzba src) {
		swap(_datum, src._datum);
		_proizvodi = src._proizvodi;
		return *this;
	}

	Datum getDatum() const { return _datum; }

	//Funkciju GetIznosNarudzbe koja vraća ukupan iznos narudžbe na osnovu
	//podataka o cijenama proizvoda i naručenim količinama. Funkcija prima neobavezni parametar popust
	//koji inicijalno ima vrijednost 0, što znači da ne postoji popust na postojeće cijene proizvoda.
	double getIznosNarudzbe(double popust = 0) const {
		double iznos = 0;
		for (size_t i = 0; i < _proizvodi.getTrenutno(); i++) {
			iznos += _proizvodi.getElement1(i).getCijena() * _proizvodi.getElement2(i);
		}
		return iznos - (iznos * popust / 100);
	}

	void dodajProizvod(const Proizvod & proizvod, const int& kolicina) {
		_proizvodi.DodajElemente(proizvod, kolicina);
	}

	//Funkciju za ispis svih vrijednosti atributa klase.
	void info() {
		cout << _datum << "\n" << _proizvodi
			<< "\nUkupna cijena: " << getIznosNarudzbe() << "\n";
	}
};

class Klijent : public Osoba {
	int _id;
	char* _email;
	Kolekcija<Narudzba, double> _narudzbe; //Podaci o narudžbama sa ukupnim utrošenim iznosom u KM
public:
	//Potrebne konstruktor i destruktor funkcije.
	Klijent(const char* ime, const char* prezime,
			const char* adresa, const char* telefon,
			int id, const char* email)
		: Osoba(ime, prezime, adresa, telefon) {
		_id = id;
		_email = AlocirajNizKaraktera(email);
	}

	~Klijent() {
		delete[] _email;
		_email = nullptr;
	}

	Kolekcija<Narudzba, double>& getNarudzbe() { return _narudzbe; }

	//Funkciju za evidenciju nove narudžbe.
	virtual void addNarudzba(Narudzba& nova) {
		_narudzbe.DodajElemente(nova, nova.getIznosNarudzbe());
	}

	//Funkciju koja vraća logičku vrijednost true ukoliko je klijent za odabrani mjesec u godini imao
	//potrošnju veću od zadate. Prototip funkcije: bool IsPotrosnjaVeca(int mjesec, double potrosnja);
	//Za pronalazak potrosnje po mjesecima koristiti podatak o datumu narudžbe.
	bool isPotrosnjaVeca(int mjesec, double potrosnja) {
		for (size_t i = 0; i < _narudzbe.getTrenutno(); i++) {
			if (_narudzbe.getElement1(i).getDatum().getMjesec() == mjesec &&
				_narudzbe.getElement2(i) > potrosnja)
				return true;
		}
		return false;
	}

	bool isPotrosnjaJednaka(int mjesec, double potrosnja) {
		for (size_t i = 0; i < _narudzbe.getTrenutno(); i++) {
			if (_narudzbe.getElement1(i).getDatum().getMjesec() == mjesec &&
				_narudzbe.getElement2(i) == potrosnja)
				return true;
		}
		return false;
	}

	//Funkciju za izmjenu e-mail adrese.
	void setAdresa(const char* email) {
		delete[] _email;
		_email = AlocirajNizKaraktera(email);
	}
	//Funkciju za ispis svih vrijednosti atributa klase.
	void info() override {
		Osoba::info();
		cout << "ID: [" << _id << "]\n" <<
			"E-mail: " << _email << "\n";
	}
};

class VIP_Klijent : public Klijent {
	char* _parkingOznaka;
	double _popust;
public:
	//Potrebne konstruktor i destruktor funkcije
	VIP_Klijent(const char* ime, const char* prezime,
				const char* adresa, const char* telefon,
				int id, const char* email, const char* parkingOznaka,
				double popust)
		: Klijent(ime, prezime, adresa, telefon, id, email) {
		_parkingOznaka = AlocirajNizKaraktera(parkingOznaka);
		_popust = popust;
	}

	~VIP_Klijent() {
		delete[] _parkingOznaka;
		_parkingOznaka = nullptr;
	}

	//Funkciju za evidenciju nove narudžbe sa zaračunatim popustom na sve proizvode.
	void addNarudzba(Narudzba& nova) override {
		Klijent::getNarudzbe().DodajElemente(nova, nova.getIznosNarudzbe(_popust));
	}

	//Funkciju koja posljednjoj narudžbi klijenta dodaje gratis proizvod proslijeđen kao parametar.
	void dodajGratis(const Proizvod& novi) {
		Klijent::getNarudzbe().getElement1(Klijent::getNarudzbe().getTrenutno() - 1).dodajProizvod(novi, 1);
	}

	//Funkciju za ispis svih vrijednosti atributa klase
	void info() override {
		Klijent::info();
		cout << "Parking oznaka: " << _parkingOznaka <<
			"\nPopust: " << _popust << "\n";
	}
};

//Funkcija treba da pronađe sve one klijente koji su za odabrani mjesec ostvarili potrošnju veću
//od zadate. Ispisati njihove podatke i vratiti ukupan broj pronađenih klijenata.
int PronadjiKlijentePoPotrosnji(Osoba* niz[], int max) {
	int trazeniMjesec = 12;
	double trazenaPotrosnja = 29.880000000000003;

	int pronadjeni = 0;

	for (size_t i = 0; i < max; i++) {
		Klijent* ptr = dynamic_cast<Klijent*>(niz[i]);
		if (ptr) {
			if (ptr->isPotrosnjaJednaka(trazeniMjesec, trazenaPotrosnja)) {
				++pronadjeni;
				ptr->info();
			}
		}
	}
	return pronadjeni;
}

//Pronaći sve VIP klijente, te im dodati gratis proizvod proslijeđen kao parametar.
void UkljuciGratisProizvodVIPKlijentima(Osoba* niz[], int max, Proizvod& p) {
	for (size_t i = 0; i < max; i++) {
		VIP_Klijent* ptr = dynamic_cast<VIP_Klijent*>(niz[i]);
		if (ptr)
			ptr->dodajGratis(p);
	}
}

//Svim klijentima postaviti mail adresu u formatu: ime.prezime@fit.ba.
void GenerisiMailAdreseKlijentima(Osoba* niz[], int max) {
	for (size_t i = 0; i < max; i++) {
		Klijent* ptr = dynamic_cast<Klijent*>(niz[i]);
		if (ptr) {
			int len = strlen(ptr->getIme()) + strlen(ptr->getPrezime()) + 9;
			char* temp = new char[len];
			strcpy_s(temp, len, ptr->getIme());
			strcat_s(temp, len, ".");
			strcat_s(temp, len, ptr->getPrezime());
			strcat_s(temp, len, "@fit.ba");
			ptr->setAdresa(temp);
		}
	}
}

//Omogućiti pretragu klijenata po imenu ili prezimenu (ispisati informacije
//o svim klijentima koji sadrže uneseni tekst u dijelu imena ili prezimena.
void PronadjiKlijentePoImenuPrezimenu(Osoba* niz[], int max) {
	const char* trazeniString = "Doe";
	bool uslov = false;

	for (size_t i = 0; i < max; i++)
		if (strstr(niz[i]->getIme(), trazeniString) || strstr(niz[i]->getPrezime(), trazeniString))
			niz[i]->info();
}

int main() {
	//Testirati sve dostupne funkcionalnosti uz obaveznu provjeru globalnih funkcija.
	//VIP klijentima sve narudžbe kreirati uz zaračunati popust
	Proizvod kola("Coca-Cola", "Bezalkoholno Pice", 2.15);
	Proizvod fanta("Fanta", "Bezalkoholno Pice", 2.05);
	Proizvod pizza("Pizza", "Hrana", 6.00);
	Proizvod cevapi("Cevapi", "Desetka brate", 6.50);

	Narudzba narudzba(12, 12, 1990);
	narudzba.dodajProizvod(kola, 2);
	narudzba.dodajProizvod(fanta, 1);
	narudzba.dodajProizvod(pizza, 3);
	narudzba.dodajProizvod(cevapi, 2);

	narudzba.info();

	cout << "<============01============>\n";

	Klijent john("John", "Doe", "Rnd Ave 2", "1800555777", 2, "john.doe@email.com");
	john.addNarudzba(narudzba);
	john.info();
	cout << "isPotrosnjaVeca: " << boolalpha << john.isPotrosnjaVeca(12, 37) << "\n";

	VIP_Klijent jane("Jane", "Doe", "Rnd Street 3", "123456789", 3, "jane.doe@email.com", "2DFA", 20);
	jane.addNarudzba(narudzba);

	Proizvod gratis("Jana", "Voda", 0);
	Osoba* niz[2] = { &john,&jane };

	cout << "<============02============>\n";
	jane.info();
	cout << "isPotrosnjaVeca: " << boolalpha << jane.isPotrosnjaVeca(12, 37) << "\n";


	cout << "<============03============>\n";
	cout << "PronadjiKlijentePoPotrosnji: " << PronadjiKlijentePoPotrosnji(niz, 2) << "\n";

	cout << "<============04============>\n";
	UkljuciGratisProizvodVIPKlijentima(niz, 2, gratis);

	cout << "<============05============>\n";
	GenerisiMailAdreseKlijentima(niz, 2);
	jane.info();

	cout << "<============06============>\n";
	PronadjiKlijentePoImenuPrezimenu(niz, 2);

	system("pause");
	return 0;
}