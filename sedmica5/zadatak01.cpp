#include <iostream>
#include <string>
using namespace std;

class Vrijeme {
	int* _sati;
	int* _minute;
	int* _sekunde;
public:
	Vrijeme(int sati, int minute, int sekunde = 0) {
		cout << "Vrijeme constructor\n";
		_sati = new int(sati);
		_minute = new int(minute);
		_sekunde = new int(sekunde);
	}

	Vrijeme(const Vrijeme& v) {
		cout << "Vrijeme copy constructor\n";
		_sati = new int(*v._sati);
		_minute = new int(*v._minute);
		_sekunde = new int(*v._sekunde);
	}

	Vrijeme(Vrijeme&& v) {
		cout << "Vrijeme move constructor\n";
		_sati = v._sati;
		v._sati = nullptr;

		_minute = v._minute;
		v._minute = nullptr;

		_sekunde = v._sekunde;
		v._sekunde = nullptr;
	}


	//preklopiti operator << za ispis objekata tipa Vrijeme 
	friend ostream& operator<<(ostream&, const Vrijeme&);

	//preklopiti operator + u klasi Vrijeme  tako da da omoguæava zbrajanje objekata tipa "Vrijeme" i cijelog broja, pri èemu se kao rezultat dobiva novi objekat tipa "Vrijeme", u kojem je vrijeme pomjereno unaprijed za iznos odreðen drugim operandom (drugi operand je u minutama) 
	Vrijeme operator+(int minute) const {
		Vrijeme temp(*this);

		while (*temp._minute + minute > 59) {
			minute -= 60;

			if (*temp._sati == 23)
				* temp._sati = 0;
			else
				*temp._sati += 1;
		}
		*temp._minute += minute;

		return temp;
	}

	Vrijeme& operator+=(int minute) {
		while (*_minute + minute > 59) {
			minute -= 60;

			if (*_sati == 23)
				* _sati = 0;
			else
				*_sati += 1;
		}
		*_minute += minute;

		return *this;
	}

	bool operator<(const Vrijeme & rhs) const {
		if (*_sati > * rhs._sati)
			return false;
		else if (*_minute > * rhs._minute)
			return false;
		else if (*_sekunde > * rhs._sekunde)
			return false;

		return true;
	}

	bool operator>(const Vrijeme & rhs) const {
		return !operator<(rhs);
	}
};

char* AlocirajChar(const char* sadrzaj) {
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

class Let {
	string _oznaka;
	char* _odrediste;
	int _brIzlazneKapije;
	Vrijeme _vrijemePolijetanja; //sati i minute
	int _trajanje; //izraeno u minutama
	int _kasnjenje; //izraeno u minutama

public:

	//kreirati potrebne konstruktore i destruktor 
	Let(string oznaka, const char* odrediste, int brIzlazneKapije, Vrijeme vrijemePolijetanja,
		int trajanje, int kasnjenje = 0) : _vrijemePolijetanja(vrijemePolijetanja) {
		cout << "Let constructor\n";
		_oznaka = oznaka;
		_odrediste = AlocirajChar(odrediste);
		_brIzlazneKapije = brIzlazneKapije;
		_trajanje = trajanje;
		_kasnjenje = kasnjenje;
	}

	Let(const Let& src) : _vrijemePolijetanja(src._vrijemePolijetanja) {
		cout << "Let copy constructor\n";
		_oznaka = src._oznaka;
		_odrediste = AlocirajChar(src._odrediste);
		_brIzlazneKapije = src._brIzlazneKapije;
		_trajanje = src._trajanje;
		_kasnjenje = src._kasnjenje;
	}

	~Let() {
		delete[] _odrediste;
	}


	//kreirati metodu sa jednim parametrom koja postavlja informaciju o eventualnom kanjenju na vrijednost zadanu parametrom.
	void setKasnjenje(const int& minute) {
		_kasnjenje = minute;
	}


	/*
	Preklopiti unarni operator "!" putem kojeg je moguæe saznati kasni li odgovarajuæi let ili ne (vratiti logièku
		vrijednost "true" u sluèaju kanjenja, u suprotnom vratiti "false").
	*/
	bool operator!() const {
		return _kasnjenje;
	}


	//kreirati metodu koja kao rezultat vraæa trajanje leta u minutama
	int getTrajanje() const {
		return _trajanje;
	}



	/*
	Preklopiti operator + na naèin da omoguæava zbrajanje
	objekata tipa "Let" i cijelog broja, pri 	èemu se kao rezultat dobiva novi objekat tipa "Let", u kojem je vrijeme polijetanja pomjereno unaprijed za iznos odreðen drugim operandom (raèunato u minutama);
	Takoðer preklopiti i operator "+=" koji osigurava da izraz oblika "X += Y uvijek ima isto znaèenje kao i izraz
		"X = X + Y"
	*/
	Let operator+(const int& minute) const {
		Let temp(*this);
		temp._vrijemePolijetanja += minute;
		return temp;
	}

	Let& operator+=(const int& minute) {
		_vrijemePolijetanja += minute;
		return *this;
	}



	/*
	kreirati metodu kojom je moguæe saznati oèekivano vrijeme polijetanja kada se uraèuna iznos kanjenja u odnosu na predviðeno vrijeme polijetanja (preklopiti operator + u klasi Vrijeme).
	*/
	Vrijeme getVrijemePolijetanjaSaKasnjenjem() const {
		return _vrijemePolijetanja + _kasnjenje;
	}


	//kreirati metodu koja vraæa oèekivano vrijeme slijetanja
	Vrijeme getVrijemeSlijetanja() const {
		return _vrijemePolijetanja + _trajanje;
	}

	Vrijeme getVrijemePolijetanja() const {
		return _vrijemePolijetanja;
	}

	/*
	Preklopiti operator "++" na naèin da pomijera vrijeme polaska za jedan sat unaprijed.
	Potrebno je podrati i prefiksnu i postfiksnu verziju ovog operatora.
	*/

	// ++obj
	Let& operator++() {
		_vrijemePolijetanja += 60;
		return *this;
	}

	// obj++
	Let operator++(int) {
		Let temp(*this);
		_vrijemePolijetanja += 60;
		return temp;
	}

	/*
	Preklopiti operator "<<" koji treba da podri ispis objekata tipa "Let" na ekran. U sluèaju da
			se radi o polijetanju bez kanjenja, ispis bi trebao da izgleda kako slijedi:

				JFK 156 Atalanta    12:50   19:30   5

			Podaci predstavljaju redom: oznaku leta, naziv odredita, vrijeme polijetanja, oèekivano
			vrijeme slijetanja i broj izlazne kapije.

			U sluèaju da se radi o letu koji kasni, ispis bi trebao izgledati kako slijedi:

				ZGK 932 Zagreb    15:50 (Planirano 15:30, Kasni 20 min)
	*/
	friend ostream& operator<<(ostream&, const Let&);
};

class RasporedLetova {
	int _brojRegistrovanihLetova;
	const int _maksimalanBrojLetova;
	Let** _letovi;

	void sort() {
		bool zamjena = true;
		while (zamjena) {
			for (int i = 0; i < _brojRegistrovanihLetova; i++) {
				if (_letovi[i]->getVrijemePolijetanja() > _letovi[i + 1]->getVrijemePolijetanja()) {
					swapLetove(_letovi[i], _letovi[i + 1]);
				} else {
					zamjena = false;
					break;
				}
			}
		}
	}

	void swapLetove(Let * lhs, Let * rhs) {
		Let* temp = lhs;
		lhs = rhs;
		rhs = temp;
	}

public:
	RasporedLetova(int maksimalanBrojLetova) : _maksimalanBrojLetova(maksimalanBrojLetova),
		_letovi(new Let * [_maksimalanBrojLetova]), _brojRegistrovanihLetova(0) {}


	/*Preklopiti operator "+=" na naèin da registruje novi let u raspored. Raspored letova u svakom momentu treba biti sortiran
	  prema vremenu polijetanja. Voditi raèuna o maksimalnom broju letova.  Za potrebe poreðenja vremena polaska letova preklopiti odgovarajuæe operatore u klasi Vrijeme.*/
	void operator+=(const Let & let) {
		_letovi[_brojRegistrovanihLetova++] = new Let(let);
		sort();
	}

	/*Preklopiti operator "-=" na naèin da ukljanja registrovani let sa oznakom definisanom putem desnog operanda.
	   Pri tome saèuvati redoslijed prethodno registrovanih letova. */
	void operator-=(const int& indeks) {
		_letovi[indeks]->~Let();
		delete _letovi[indeks];
		_letovi[indeks] = nullptr;
		sort();
		_brojRegistrovanihLetova--;
	}

	//Preklopiti operator "[]" na naèin da vraæa objekat tipa Let na osnovu proslijeðene pozicije u rasporedu (pozicije kreæu od 1).
	Let operator[](const int& indeks) {
		return *_letovi[indeks - 1];
	}

	/*Preklopiti operator "()" na naèin da letu sa definisanom oznakom pomjeri vrijeme polijetanja za vrijednost drugog parametra izraenog
	u minutama. */

	//Funkciju koja daje prosjeèno trajanje svih pohranjenih letova.
	float prosjecnoTrajanje() {
		float avg = 0.f;
		for (int i = 0; i < _brojRegistrovanihLetova; i++) {
			avg += _letovi[i]->getTrajanje();
		}
		return avg / _brojRegistrovanihLetova;
	}

	/*Preklopiti operator "<<" koji ispisuje kompletan spisak svih letova, sortiran po oèekivanim vremenima polazaka.
	Za potrebe poreðenja vremena polaska letova preklopiti odgovarajuæe operatore u klasi Vrijeme. */
};

ostream& operator<<(ostream& COUT, const Vrijeme& v) {
	COUT << *v._sati << ":" << *v._minute << ":" << *v._sekunde;
	return COUT;
}

ostream& operator<<(ostream& COUT, const Let& l) {
	if (!l)
		COUT << l._oznaka << " " << l._odrediste << " " << l.getVrijemePolijetanjaSaKasnjenjem() << " (Planirano " << l._vrijemePolijetanja << ", Kasni " << l._kasnjenje << " min)";
	else
		COUT << l._oznaka << " " << l._odrediste << " " << l._vrijemePolijetanja << " " << l.getVrijemeSlijetanja() << " " << l._brIzlazneKapije;

	return COUT;
}

int main() {

	//kreirati dva objekta tipa vrijeme;
	Vrijeme v1(23, 40, 20), v2(12, 50);
	//upotrijebiti preklopljeni operator << za ispis objekta
		//varijanta I  cout<<V1; - svaki objekt posebno
				//cout<<V2;
		//varijanta II: cout<<V1<<V2; - oba objekta zajedno
	cout << v1 << "\n" << v2 << "\n";
	//kreirati treæi object tipa Vrijeme koji æe imati vrijednost vrijeme objekta V1+ uneseno vrijeme kasnjenja (u  minutama);
	//demostrirati rad konstruktora kopije
	Vrijeme v3 = v1 + 30;
	cout << v1 << "\n" << v2 << "\n" << v3 << "\n";

	Let l1("JFK 156", "Atlanta", 5, v2, 400, 0);

	cout << l1 << "\n";

	cout << l1++ << "\n";
	cout << ++l1 << "\n";

	Let l2 = l1 + 60;
	l2 += 60;

	cout << l2 << "\n";
}