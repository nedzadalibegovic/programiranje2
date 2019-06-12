#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <regex>
#include <thread>

using namespace std;

const char* crt = "\n-------------------------------------------\n";
enum GodinaStudija { PRVA = 1, DRUGA, TRECA };

ostream& operator<<(ostream& out, const GodinaStudija& godina) {
	static const char* ispis[] = { "I", "II", "III" };
	out << ispis[godina];
	return out;
}

char* Alociraj(const char* sadrzaj) {
	if (sadrzaj == nullptr)return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

template<class T1, class T2>
class Dictionary {
	T1* _elementi1;
	T2* _elementi2;
	int* _trenutno;
public:
	Dictionary() {
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_trenutno = new int(0);
	}

	Dictionary(const Dictionary& src) {
		_trenutno = new int(*src._trenutno);

		_elementi1 = new T1[*_trenutno];
		_elementi2 = new T2[*_trenutno];

		for (size_t i = 0; i < *_trenutno; i++) {
			_elementi1[i] = src._elementi1[i];
			_elementi2[i] = src._elementi2[i];
		}
	}

	friend void swap(Dictionary& lhs, Dictionary& rhs) {
		using std::swap;

		swap(lhs._elementi1, rhs._elementi1);
		swap(lhs._elementi2, rhs._elementi2);
		swap(lhs._trenutno, rhs._trenutno);
	}

	Dictionary& operator=(Dictionary src) {
		swap(*this, src);
		return *this;
	}

	void AddElement(const T1& el1, const T2& el2) {
		T1* temp1 = new T1[(*_trenutno) + 1];
		T2* temp2 = new T2[(*_trenutno) + 1];

		for (size_t i = 0; i < *_trenutno; i++) {
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];
		}

		temp1[*_trenutno] = el1;
		temp2[*_trenutno] = el2;

		delete[] _elementi1;
		delete[] _elementi2;

		_elementi1 = temp1;
		_elementi2 = temp2;

		temp1 = nullptr;
		temp2 = nullptr;

		(*_trenutno) += 1;
	}

	~Dictionary() {
		delete[]_elementi1; _elementi1 = nullptr;
		delete[]_elementi2; _elementi2 = nullptr;
		delete _trenutno; _trenutno = nullptr;
	}
	T1& getElement1(int lokacija)const { return _elementi1[lokacija]; }
	T2& getElement2(int lokacija)const { return _elementi2[lokacija]; }
	int getTrenutno() { return *_trenutno; }
	friend ostream& operator<< (ostream& COUT, const Dictionary& obj) {
		for (size_t i = 0; i < *obj._trenutno; i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		return COUT;
	}

	Dictionary getRange(int start, int end) {
		if (end < start)
			throw exception("Vrijednost posljednje lokacije manja od pocetne");

		if (start < 0 || end > * _trenutno)
			throw exception("Lokacija ne postoji");

		Dictionary temp;

		for (size_t i = start; i < end; i++) {
			temp.AddElement(_elementi1[i], _elementi2[i]);
		}

		return temp;
	}
};

class DatumVrijeme {
	int* _dan, * _mjesec, * _godina, * _sati, * _minuti;
public:
	DatumVrijeme(int dan = 1, int mjesec = 1, int godina = 2000, int sati = 0, int minuti = 0) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
		_sati = new int(sati);
		_minuti = new int(minuti);
	}

	DatumVrijeme(const DatumVrijeme& src) {
		_dan = new int(*src._dan);
		_mjesec = new int(*src._mjesec);
		_godina = new int(*src._godina);
		_sati = new int(*src._sati);
		_minuti = new int(*src._minuti);
	}

	friend void swap(DatumVrijeme& lhs, DatumVrijeme& rhs) {
		using std::swap;

		swap(lhs._dan, rhs._dan);
		swap(lhs._mjesec, rhs._mjesec);
		swap(lhs._godina, rhs._godina);
		swap(lhs._sati, rhs._sati);
		swap(lhs._minuti, rhs._minuti);
	}

	DatumVrijeme& operator=(DatumVrijeme src) {
		swap(*this, src);
		return *this;
	}

	~DatumVrijeme() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
		delete _sati; _sati = nullptr;
		delete _minuti; _minuti = nullptr;
	}

	char* ToCharArray() const {
		stringstream obj;

		if (*_dan < 10) {
			obj << 0;
		}

		obj << *_dan << "/";

		if (*_mjesec < 10) {
			obj << 0;
		}

		obj << *_mjesec << "/" << *_godina << " " << *_sati << ":" << *_minuti;

		return Alociraj(obj.str().c_str()); // memory leak
	}

	friend ostream& operator<< (ostream& COUT, const DatumVrijeme& obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << " " << *obj._sati << ":" << *obj._minuti << endl;
		return COUT;
	}

	friend bool razmakManjiOdJedanSat(const DatumVrijeme& lhs, const DatumVrijeme& rhs) {
		int timeL = (*lhs._sati) * 60 + (*lhs._minuti);
		int timeR = (*rhs._sati) * 60 + (*rhs._minuti);
		int rezultat = timeL - timeR;

		if (rezultat < 0)
			rezultat *= -1;

		return rezultat < 60;
	}

	int uMinute() {
		int minute = 0;

		for (size_t i = 1; i < *_mjesec; i++) {
			switch (i) {
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:
					minute += 44640;
					break;
				case 2:
					minute += 40320;
					break;
				case 4:
				case 6:
				case 9:
				case 11:
					minute += 43200;
					break;
				default:
					break;
			}
		}

		minute += (*_dan) * 1440;
		minute += (*_sati) * 60;

		return minute;
	}

	friend bool operator<(DatumVrijeme& lhs, DatumVrijeme& rhs) {
		return lhs.uMinute() < rhs.uMinute();
	}

	friend bool operator>(DatumVrijeme& lhs, DatumVrijeme& rhs) {
		return !operator<(lhs, rhs);
	}
};

class Predmet {
	char* _naziv;
	int _ocjena;
	string _napomena;
public:
	Predmet(const char* naziv = "", int ocjena = 0, string napomena = "") {
		_naziv = Alociraj(naziv);
		_ocjena = ocjena;
		_napomena = napomena;
	}

	Predmet(const Predmet& src) : _napomena(src._napomena) {
		_naziv = Alociraj(src._naziv);
		_ocjena = src._ocjena;
	}

	friend void swap(Predmet& lhs, Predmet& rhs) {
		using std::swap;

		swap(lhs._naziv, rhs._naziv);
		swap(lhs._ocjena, rhs._ocjena);
		swap(lhs._napomena, rhs._napomena);
	}

	Predmet& operator=(Predmet src) {
		swap(*this, src);
		return *this;
	}

	~Predmet() {
		delete[] _naziv;
		_naziv = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, Predmet& obj) {
		COUT << obj._naziv << " (" << obj._ocjena << ") " << obj._napomena << endl;
		return COUT;
	}
	string GetNapomena() { return _napomena; }
	char* GetNaziv() { return _naziv; }
	int GetOcjena() { return _ocjena; }

	friend bool operator==(const Predmet& lhs, const Predmet& rhs) {
		return !strcmp(lhs._naziv, rhs._naziv);
	}

	void DodajNapomenu(string napomena) {
		_napomena += " " + napomena;
	}
};

class Uspjeh {
	GodinaStudija* _godina;
	//datumvrijeme se odnosi na vrijeme evidentiranja polozenog predmeta
	Dictionary<Predmet, DatumVrijeme> _predmeti;
public:
	Uspjeh(GodinaStudija godina) {
		_godina = new GodinaStudija(godina);
	}

	Uspjeh(const Uspjeh& src) : _predmeti(src._predmeti) {
		_godina = new GodinaStudija(*src._godina);
	}

	friend void swap(Uspjeh& lhs, Uspjeh& rhs) {
		using std::swap;

		swap(lhs._godina, rhs._godina);
		swap(lhs._predmeti, rhs._predmeti);
	}

	Uspjeh& operator=(Uspjeh src) {
		swap(*this, src);
		return *this;
	}

	~Uspjeh() { delete _godina; _godina = nullptr; }

	Dictionary<Predmet, DatumVrijeme>* GetPredmeti() { return &_predmeti; }
	GodinaStudija* GetGodinaStudija() { return _godina; }
	friend ostream& operator<< (ostream& COUT, const Uspjeh& obj) {
		COUT << *obj._godina << " " << obj._predmeti << endl;
		return COUT;
	}
};

class Student {
	char* _imePrezime;
	string _emailAdresa;
	string _brojTelefona;
	vector<Uspjeh> _uspjeh;

	static bool checkEmail(const string& email) {
		static string pravilo = R"(\b\w+\.\w+@(hotmail.com|fit.ba|outlook.com)\b)";
		return regex_match(email, regex(pravilo));
	}

	void email(GodinaStudija godina) {
		cout << "FROM: info@fit.ba\n";
		cout << "TO : " << _emailAdresa << "\n";
		cout << "Postovani " << _imePrezime << ", evidentirali ste uspjeh za " << godina << " godinu studija.\nPozdrav.\nFIT Team.\n";
	}

	void sms(Uspjeh& obj, GodinaStudija godina) {
		float prosjek = 0;

		for (size_t i = 0; i < obj.GetPredmeti()->getTrenutno(); i++) {
			prosjek += obj.GetPredmeti()->getElement1(i).GetOcjena();
		}

		prosjek /= obj.GetPredmeti()->getTrenutno();

		if (prosjek > 8) {
			cout << "Svaka cast za uspjeh " << prosjek << " ostvaren u " << godina << " godini studija\n";
		}
	}

public:
	Student(const char* imePrezime, string emailAdresa, string brojTelefona) {
		_imePrezime = Alociraj(imePrezime);

		if (checkEmail(emailAdresa)) {
			_emailAdresa = emailAdresa;
		} else {
			_emailAdresa = "notSet@fit.ba";
		}

		_brojTelefona = brojTelefona;
	}

	Student(const Student& src) : _emailAdresa(src._emailAdresa), _brojTelefona(src._brojTelefona), _uspjeh(src._uspjeh) {
		_imePrezime = Alociraj(src._imePrezime);
	}

	friend void swap(Student& lhs, Student& rhs) {
		using std::swap;

		swap(lhs._imePrezime, rhs._imePrezime);
		swap(lhs._emailAdresa, rhs._emailAdresa);
		swap(lhs._brojTelefona, rhs._brojTelefona);
		swap(lhs._uspjeh, rhs._uspjeh);
	}

	Student& operator=(Student src) {
		swap(*this, src);
		return *this;
	}

	~Student() {
		delete[] _imePrezime;
		_imePrezime = nullptr;
	}

	friend ostream& operator<< (ostream& COUT, Student& obj) {
		COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._brojTelefona << endl;
		return COUT;
	}
	vector<Uspjeh>* GetUspjeh() { return &_uspjeh; }
	string GetEmail() { return _emailAdresa; }
	string GetBrojTelefona() { return _brojTelefona; }
	char* GetImePrezime() { return _imePrezime; }

	bool AddPredmet(const Predmet& predmet, GodinaStudija godina, const DatumVrijeme& datum) {
		for (size_t i = 0; i < _uspjeh.size(); i++) {
			if (*_uspjeh[i].GetGodinaStudija() == godina) {
				for (size_t j = 0; j < _uspjeh[i].GetPredmeti()->getTrenutno(); j++) {
					if (_uspjeh[i].GetPredmeti()->getElement1(j) == predmet) {
						cout << "Postoji istoimeni predmet!\n";
						return false;
					}
				}

				for (size_t j = 0; j < _uspjeh[i].GetPredmeti()->getTrenutno(); j++) {
					if (razmakManjiOdJedanSat(_uspjeh[i].GetPredmeti()->getElement2(j), datum)) {
						cout << "Razmak izmedju dodatih predmeta je manji od jedan sat!\n";
						return false;
					}
				}

				thread worker1(&Student::sms, ref(*this), ref(_uspjeh[i]), godina);
				thread worker2(&Student::email, ref(*this), godina);
				_uspjeh[i].GetPredmeti()->AddElement(predmet, datum);
				worker1.join();
				worker2.join();
				return true;
			}
		}

		thread worker2(&Student::email, ref(*this), godina);
		_uspjeh.push_back(Uspjeh(godina));
		_uspjeh[0].GetPredmeti()->AddElement(predmet, datum);
		thread worker1(&Student::sms, ref(*this), ref(_uspjeh[0]), godina);
		worker2.join();
		worker1.join();
		return true;
	}

	int BrojPonavljanjaRijeci(string pravilo) {
		int brPonavljanja = 0;
		regex trazilica(pravilo);

		for (size_t i = 0; i < _uspjeh.size(); i++) {
			for (size_t j = 0; j < _uspjeh[i].GetPredmeti()->getTrenutno(); j++) {
				string napomena = _uspjeh[i].GetPredmeti()->getElement1(j).GetNapomena();
				sregex_iterator begin(napomena.begin(), napomena.end(), trazilica);
				sregex_iterator end;
				while (begin != end) {
					brPonavljanja += 1;
					begin++;
				}
			}
		}

		return brPonavljanja;
	}

	vector<Predmet> operator()(DatumVrijeme* datumOD, DatumVrijeme* datumDO) {
		vector<Predmet> var;

		for (size_t i = 0; i < _uspjeh.size(); i++) {
			for (size_t j = 0; j < _uspjeh[i].GetPredmeti()->getTrenutno(); j++) {
				DatumVrijeme& datum = _uspjeh[i].GetPredmeti()->getElement2(j);
				if (datum > * datumOD && datum < *datumDO) {
					var.push_back(_uspjeh[i].GetPredmeti()->getElement1(j));
				}
			}
		}

		delete datumOD;
		delete datumDO;

		return var;
	}

	Uspjeh* operator[](const char* godina) {
		GodinaStudija trazena;

		if (!strcmp(godina, "PRVA")) {
			trazena = PRVA;
		} else if (!strcmp(godina, "DRUGA")) {
			trazena = DRUGA;
		} else {
			trazena = TRECA;
		}

		for (size_t i = 0; i < _uspjeh.size(); i++) {
			if (*_uspjeh[i].GetGodinaStudija() == trazena) {
				return &_uspjeh[i];
			}
		}

		return nullptr;
	}
};

int main() {
	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
	3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKOĐER NALAZI U FAJLU CODE.TXT
	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUČAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAČENO.
	****************************************************************************/
	cout << "NA KRAJU ISPITA, RAD PREDAJTE U ODGOVARAJUCI FOLDER NA FTP SERVERU (INTEGRALNI)!" << endl;
	DatumVrijeme temp,
		datum19062019_1015(19, 6, 2019, 10, 15),
		datum20062019_1115(20, 6, 2019, 11, 15),
		datum30062019_1215(30, 6, 2019, 12, 15),
		datum05072019_1231(5, 7, 2019, 12, 31);
	//funkcija ToCharArray vraca datum i vrijeme kao char *. konverziju izvrsiti koristeci stringstream objekat.
	//voditi racuna o tome da se izmedju datuma i vremena nalazi samo jedan razmak, te da su vrijednosti dana i mjeseca iskazane kao dvije cifre
	cout << datum19062019_1015.ToCharArray() << endl;//treba ispisati: 19/06/2019 10:15
	temp = datum05072019_1231;
	cout << temp.ToCharArray() << endl;//treba ispisati: 05/07/2019 12:31

	const int DictionaryTestSize = 9;
	Dictionary<int, int> Dictionary1;
	for (size_t i = 0; i < DictionaryTestSize; i++)
		Dictionary1.AddElement(i + 1, i * i);

	try {
		//vraca elemente kolekcije koji se nalaze na lokacijama definisanim vrijednostima parametara (npr. 2 - 7). 
		//funkcija baca izuzetak u slucaju da se zahtijeva lokacija koja ne postoji ili je vrijednost posljednje lokacije manja od pocetne
		Dictionary<int, int> opseg = Dictionary1.getRange(2, 7);
		cout << opseg << endl;
		Dictionary1.getRange(7, 11);
	} catch (exception& err) {
		cout << err.what() << endl;
	}
	cout << Dictionary1 << endl;

	Dictionary<int, int> Dictionary2 = Dictionary1;
	cout << Dictionary2 << crt;

	Dictionary<int, int> Dictionary3;
	Dictionary3 = Dictionary1;
	cout << Dictionary3 << crt;

	//napomena se moze dodati i prilikom kreiranja objekta
	Predmet MAT("Matematika", 7, "Ucesce na takmicenju"),
		UIT("Uvod u informacijske tehnologije", 9),
		RM("Racunarske mreze", 8),
		EN("Engleski jezik", 6);
	UIT.DodajNapomenu("Pohvala za ostvareni uspjeh");
	cout << MAT << endl;

	/*
	email adresa mora biti u formatu: text-text@ nakon cega slijedi neka od sljedecih domena: hotmail.com ili outlook.com ili fit.ba. Pod text se podrazumijeva bilo koje slovo, malo ili veliko.
	u slucaju da email adresa nije validna, postaviti je na defaultnu: notSet@fit.ba
	za provjeru koristiti regex
	*/
	Student jasmin("Jasmin Azemovic", "jasmin.azemovic@hotmail.com", "033 281 172");
	Student adel("Adel Handzic", "adel.handzic@fit.ba", "033 281 170");
	Student emailNotValid("Ime Prezime", "korisnik@lazna.ba", "033 281 170");

	/*
	uspjeh se dodaje za svaki predmet na nivou godine studija.
	tom prilikom onemoguciti:
	- dodavanje istoimenih predmeta na nivou jedne godine,
	- dodavanje vise predmeta u kratkom vremenskom periodu (na nivou jedne godine, razmak izmedju dodavanja pojedinih predmeta mora biti najmanje 1 sat).
	godine (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za drugu godinu, pa onda za prvu godinu i sl.).
	Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
	*/
	if (jasmin.AddPredmet(UIT, DRUGA, datum20062019_1115))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(RM, DRUGA, datum30062019_1215))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(EN, PRVA, datum19062019_1015))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(MAT, PRVA, datum20062019_1115))
		cout << "Predmet uspjesno dodan!" << crt;
	//ne treba dodati MAT jer je vec dodana u prvoj godini
	if (jasmin.AddPredmet(MAT, PRVA, datum05072019_1231))
		cout << "Predmet uspjesno dodan!" << crt;
	//ne treba dodati UIT jer nije prosao 1 sat od dodavanja posljednjeg predmeta
	if (jasmin.AddPredmet(UIT, PRVA, datum20062019_1115))
		cout << "Predmet uspjesno dodan!" << crt;
	/*nakon evidentiranja uspjeha na bilo kojem predmetu tj. prilikom uspjesno izvrsene funkcije AddPredmet, Studentu se salje email sa sadrzajem:
	FROM:info@fit.ba
	TO: emailStudenta
	Postovani ime i prezime, evidentirali ste uspjeh za X godinu studija.
	Pozdrav.
	FIT Team.

	ukoliko je, nakon dodavanja predmeta, prosjek na nivou te godine veci od 8.0 Studentu se, pored email-a, salje i SMS sa sadrzajem: "Svaka cast za uspjeh X.X ostvaren u X godini studija".
	slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
	*/
	cout << "USPJEH ISPISATI KORISTEĆI OSTREAM_ITERATOR" << endl;
	cout << jasmin << endl;
	//vraca broj ponavljanja odredjene rijeci u napomenama, koristiti sregex_iterator
	cout << "Rijec takmicenje se pojavljuje " << jasmin.BrojPonavljanjaRijeci("takmicenju") << " puta." << endl;

	//vraca niz predmeta koji su evidentiranih u periodu izmedju vrijednosti proslijedjenih parametara
	vector<Predmet> jasminUspjeh = jasmin(new DatumVrijeme(18, 06, 2019, 10, 15), new DatumVrijeme(21, 06, 2019, 10, 10));
	for (Predmet u : jasminUspjeh)
		cout << u << endl;

	Uspjeh* uspjeh_I_godina = jasmin["PRVA"];//vraca uspjeh Studenta ostvaren u prvoj godini studija
	if (uspjeh_I_godina != nullptr)
		cout << *uspjeh_I_godina << endl;
}