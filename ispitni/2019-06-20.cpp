#include <iostream>
#include <vector>
#include <regex>
#include <thread>
#include <fstream>

using namespace std;

/****************************************************************************
1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUČAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
5. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAČENO.
****************************************************************************/

const char* nedozvoljena_operacija = "Nedozvoljena operacija";
const char* not_set = "NOT_SET";

enum Sortiranje { ASC, DESC };
enum Predmet { MATEMATIKA, FIZIKA, HEMIJA, GEOGRAFIJA, NOT_SET };
enum Razred { I = 1, II, III, IV };

char* AlocirajNizKaraktera(const char* sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

template <class T1, class T2, int max>
class Kolekcija {
	T1* _elementi1[max] = { nullptr };
	T2* _elementi2[max] = { nullptr };
	int _trenutnoElemenata;
	bool _dozvoliDupliranje;
	Sortiranje _sortiranje;

	bool isDuplicate(const T1& el1) {
		for (size_t i = 0; i < _trenutnoElemenata; i++) {
			if (*_elementi1[i] == el1) {
				return true;
			}
		}
		return false;
	}

	void sortiranje() {
		for (size_t i = 0; i < _trenutnoElemenata; i++) {
			for (size_t j = i + 1; j < _trenutnoElemenata; j++) {
				if (_sortiranje == ASC) {
					if (*_elementi1[i] > * _elementi1[j]) {
						swap(_elementi1[i], _elementi1[j]);
						swap(_elementi2[i], _elementi2[j]);
					}
				} else {
					if (*_elementi1[i] < *_elementi1[j]) {
						swap(_elementi1[i], _elementi1[j]);
						swap(_elementi2[i], _elementi2[j]);
					}
				}
			}
		}
	}
public:
	Kolekcija(Sortiranje sortiranje = ASC, bool dozvoliDupliranje = true) {
		_trenutnoElemenata = 0;
		_sortiranje = sortiranje;
		_dozvoliDupliranje = dozvoliDupliranje;
	}

	Kolekcija(const Kolekcija& src) {
		for (size_t i = 0; i < src._trenutnoElemenata; i++) {
			_elementi1[i] = new T1(*src._elementi1[i]);
			_elementi2[i] = new T2(*src._elementi2[i]);
		}

		_trenutnoElemenata = src._trenutnoElemenata;
		_dozvoliDupliranje = src._dozvoliDupliranje;
		_sortiranje = src._sortiranje;
	}

	friend void swap(Kolekcija& lhs, Kolekcija& rhs) {
		using std::swap;

		swap(lhs._elementi1, rhs._elementi1);
		swap(lhs._elementi2, rhs._elementi2);
		swap(lhs._trenutnoElemenata, rhs._trenutnoElemenata);
		swap(lhs._dozvoliDupliranje, rhs._dozvoliDupliranje);
		swap(lhs._sortiranje, rhs._sortiranje);
	}

	Kolekcija& operator=(Kolekcija src) {
		swap(*this, src);
		return *this;
	}

	~Kolekcija() {
		for (size_t i = 0; i < _trenutnoElemenata; i++) {
			delete _elementi1[i];
			_elementi1[i] = nullptr;

			delete _elementi2[i];
			_elementi2[i] = nullptr;
		}
	}

	int GetTrenutno() const { return _trenutnoElemenata; }
	int GetMax() const { return max; }

	T1& GetElement1(int lokacija) const {
		if (lokacija < 0 || lokacija >= _trenutnoElemenata)
			throw exception(nedozvoljena_operacija);
		return *_elementi1[lokacija];
	}

	T2& GetElement2(int lokacija) const {
		if (lokacija < 0 || lokacija >= _trenutnoElemenata)
			throw exception(nedozvoljena_operacija);
		return *_elementi2[lokacija];
	}

	void SetElement2(int lokacija, T2 ele2) {
		*_elementi2[lokacija] = ele2;
	}

	void AddElement(const T1& el1, const T2& el2) {
		if (isDuplicate(el1)) {
			throw exception("dupliranje elemenata nije dozvoljeno\n");
		}

		if (_trenutnoElemenata + 1 >= max) {
			throw exception("dosegnut maksimalan broj elemenata\n");
		}

		_elementi1[_trenutnoElemenata] = new T1(el1);
		_elementi2[_trenutnoElemenata] = new T2(el2);
		_trenutnoElemenata += 1;

		sortiranje();
	}

	friend ostream& operator<<(ostream& COUT, const Kolekcija& obj) {
		for (size_t i = 0; i < obj.GetTrenutno(); i++)
			COUT << obj.GetElement1(i) << " " << obj.GetElement2(i) << endl;
		return COUT;
	}
};

class Aktivnost {
	shared_ptr<Razred> _razred;
	string _opis;
	int _ocjena; //1-5
public:
	Aktivnost(Razred razred = I, int ocjena = 0, string opis = not_set) {
		_ocjena = ocjena;
		_opis = opis;
		_razred = make_shared<Razred>(razred);
	}

	int  GetOcjenu() const { return _ocjena; }
	string GetOpis() const { return _opis; }
	Razred GetRazred() const { return *_razred; }

	friend ostream& operator<<(ostream& COUT, const Aktivnost& obj) {
		COUT << *obj._razred << " " << obj._ocjena << " " << obj._opis << endl;
		return COUT;
	}
};

class Polaznik {
protected:
	char* _imePrezime;
	string _brojTelefona;
public:
	Polaznik(string imePrezime, string brojTelefona) : _imePrezime(AlocirajNizKaraktera(imePrezime.c_str())) {
		_brojTelefona = brojTelefona;
	}

	Polaznik(const Polaznik& src) : _brojTelefona(src._brojTelefona) {
		_imePrezime = AlocirajNizKaraktera(src._imePrezime);
	}

	Polaznik(Polaznik&& src) : _brojTelefona(move(src._brojTelefona)) {
		_imePrezime = src._imePrezime;
		src._imePrezime = nullptr;
	}

	friend void swap(Polaznik& lhs, Polaznik& rhs) {
		using std::swap;

		swap(lhs._imePrezime, rhs._imePrezime);
		swap(lhs._brojTelefona, rhs._brojTelefona);
	}

	~Polaznik() { delete[] _imePrezime; }

	friend bool operator==(const Polaznik& lhs, const Polaznik& rhs) {
		return !strcmp(lhs._imePrezime, rhs._imePrezime) || lhs._brojTelefona == rhs._brojTelefona;
	}

	void setTelefon(const string& tel) { _brojTelefona = tel; }
	char* GetImePrezime() { return _imePrezime; }
	string GetTelefon() { return _imePrezime; }
	virtual void PredstaviSe() = 0;
};

class Ucenik : public Polaznik {
	Kolekcija<Predmet, Aktivnost, 16> * _aktivnosti;
public:
	Ucenik(string ime = not_set, string brojTelefona = not_set) : Polaznik(ime, brojTelefona) {
		_aktivnosti = new Kolekcija< Predmet, Aktivnost, 16>();
	}

	Ucenik(const Ucenik& src) : Polaznik(src) {
		_aktivnosti = new Kolekcija<Predmet, Aktivnost, 16>(*src._aktivnosti);
	}

	Ucenik(Ucenik&& src) : Polaznik(src) {
		_aktivnosti = src._aktivnosti;
		src._aktivnosti = nullptr;
	}

	friend void swap(Ucenik& lhs, Ucenik& rhs) {
		using std::swap;

		swap(static_cast<Polaznik&>(lhs), static_cast<Polaznik&>(rhs));
		swap(lhs._aktivnosti, rhs._aktivnosti);
	}

	Ucenik& operator=(Ucenik src) {
		swap(*this, src);
		return *this;
	}

	~Ucenik() { delete _aktivnosti; _aktivnosti = nullptr; }
	Kolekcija<Predmet, Aktivnost, 16> & GetAktivnosti() { return *_aktivnosti; };

	friend ostream& operator<<(ostream& COUT, Ucenik& n) {
		COUT << "Ime i prezime: " << n._imePrezime
			<< "\nBroj Telefona: " << n._brojTelefona
			<< "\nAktivnosti:\n" << *n._aktivnosti;
		return COUT;
	}

	friend bool operator==(const Ucenik& lhs, const Ucenik& rhs) {
		return static_cast<const Polaznik&>(lhs) == static_cast<const Polaznik&>(rhs);
	}

	void PredstaviSe() override {
		cout << "Ime prezime: " << _imePrezime << "\nBroj Telefona: " << _brojTelefona << "\n";
	}

	float getProsjek() {
		float prosjek = 0;

		for (size_t i = 0; i < _aktivnosti->GetTrenutno(); i++) {
			prosjek += _aktivnosti->GetElement2(i).GetOcjenu();
		}

		return prosjek / _aktivnosti->GetTrenutno();
	}
};

class Skola {
	char* _naziv;
	vector<Ucenik> _ucenici;
public:
	Skola(const char* naziv = nullptr) {
		_naziv = AlocirajNizKaraktera(naziv);
	}

	Skola(const Skola& src) : _ucenici(src._ucenici) {
		_naziv = AlocirajNizKaraktera(src._naziv);
	}

	Skola(Skola&& src) : _ucenici(move(src._ucenici)) {
		_naziv = src._naziv;
		src._naziv = nullptr;
	}

	friend void swap(Skola& lhs, Skola& rhs) {
		using std::swap;

		swap(lhs._naziv, rhs._naziv);
		swap(lhs._ucenici, rhs._ucenici);
	}

	Skola& operator=(Skola src) {
		swap(*this, src);
		return *this;
	}

	~Skola() {
		delete[] _naziv; _naziv = nullptr;
	}

	char* GetNaziv()const { return _naziv; }
	vector<Ucenik>& GetUcenici() { return _ucenici; };

	friend ostream& operator<<(ostream& COUT, Skola& obj) {
		COUT << "Skola: " << obj._naziv << endl;
		COUT << "Ucenici: " << endl;
		for (size_t i = 0; i < obj._ucenici.size(); i++)
			COUT << obj._ucenici[i] << endl;
		return COUT;
	}

	void operator()(string ime, string brojTelefona) {
		string pravilo1 = R"(\+387\(6\d\)\d{3}\-\d{3})";
		string pravilo2 = R"(\+387 6\d \d{3}\-\d{3})";

		Ucenik temp(ime, brojTelefona);

		if (!(regex_match(brojTelefona, regex(pravilo1)) || regex_match(brojTelefona, regex(pravilo2)))) {
			temp.setTelefon(not_set);
		}

		if (find(_ucenici.begin(), _ucenici.end(), temp) != _ucenici.end()) {
			throw exception("Ucenik sa istim imenom i prezimenom ili brojem telefona!\n");
		}

		_ucenici.push_back(move(temp));
	}

	bool DodajAktivnost(string imePrezime, Predmet predmet, Aktivnost aktivnost) {
		for (size_t i = 0; i < _ucenici.size(); i++) {
			if (_ucenici.at(i).GetImePrezime() == imePrezime) {
				Ucenik& ucenik = _ucenici.at(i); // nadjeni ucenik

				// provjera postoji li aktivnost za dati predmet u istom razredu
				for (size_t j = 0; j < ucenik.GetAktivnosti().GetTrenutno(); j++) {
					if (ucenik.GetAktivnosti().GetElement1(j) == predmet) {
						if (ucenik.GetAktivnosti().GetElement2(j).GetRazred() == aktivnost.GetRazred()) {
							return false;
						}
					}
				}

				// provjera broja aktivnosti u razredu
				for (size_t j = 0; j < ucenik.GetAktivnosti().GetTrenutno(); j++) {
					int brojAktivnosti = 0;

					if (ucenik.GetAktivnosti().GetElement2(j).GetRazred() == predmet) {
						if (++brojAktivnosti >= 4) {
							return false;
						}
					}
				}

				ucenik.GetAktivnosti().AddElement(predmet, aktivnost);

				// slanje SMS poruke
				if (aktivnost.GetOcjenu() > 1 && ucenik.GetTelefon() != not_set) {
					thread worker([&]() {
						cout << "Uspjesno ste okoncali aktivnosti u okviru " << aktivnost.GetRazred() << " razreda sa prosjecnom ocjenom " << ucenik.getProsjek() << "\n";
								  });
					worker.join();
				}

				return true;
			}
		}
	}

	pair<Polaznik*, float> GetNajboljegUcenika() {
		Ucenik* najboljiUcenik = &_ucenici.at(0);
		float najboljiProsjek = najboljiUcenik->getProsjek();

		for (size_t i = 1; i < _ucenici.size(); i++) {
			if (najboljiProsjek < _ucenici.at(i).getProsjek()) {
				najboljiUcenik = &_ucenici.at(i);
				najboljiProsjek = _ucenici.at(i).getProsjek();
			}
		}

		return pair<Polaznik*, float>(najboljiUcenik, najboljiProsjek);
	}

	bool SpasiUFajl(string file, bool overwrite = false) {
		ofstream output;
		ifstream input;
		string input_string;

		if (overwrite) {
			output.open(file, ios::trunc);
		} else {
			output.open(file, ios::app);
		}

		output << *this;
		output.close();

		input.open(file);

		while (getline(input, input_string)) {
			cout << input_string << "\n";
		}

		input.close();

		return true;
	}
};

int main() {
	Kolekcija<int, int, 10> kolekcija1(DESC, false);
	try {
		kolekcija1.AddElement(1, 2);
		//dupliranje elemenata nije dozvoljeno
		kolekcija1.AddElement(1, 2);
	} catch (exception& ex) {
		cout << ex.what();
	}

	/*nakon svakog dodavanja, elemente sortirati prema T1 i vrijednosti atributa _sortiranje*/
	for (size_t i = 1; i < kolekcija1.GetMax() - 1; i++)
		kolekcija1.AddElement(rand(), rand());

	cout << kolekcija1 << endl;

	try {
		//prekoracen maksimalan broj elemenata
		kolekcija1.AddElement(rand(), rand());
	} catch (exception& ex) {
		cout << ex.what();
	}
	cout << kolekcija1 << endl;

	Kolekcija<int, int, 10> kolekcija2(kolekcija1);
	cout << kolekcija2 << endl;

	Skola gimnazijaMostar("GIMNAZIJA MOSTAR");
	//dodaje novog ucenika u skolu
	gimnazijaMostar("Jasmin Azemovic", "+387(61)111-222");
	gimnazijaMostar("Adel Handzic", "+387(61)333-444");

	/*
	koristeci regex, osigurati sljedeci format za broj telefona: +387(6X)XXX-XXX ili +387 6X XXX-XXX
	onemoguciti pojavljivanje samo jedne zagrade, a ukoliko format nije adekvatna koristiti vrijednost not_set
	*/
	gimnazijaMostar("Telefon NotValidFormat", "387 61)333-444");

	try {
		/*onemoguciti dodavanje ucenika sa istim imenom i prezimenom ili brojem telefona*/
		gimnazijaMostar("Adel Handzic", "+387(61)333-444");
	} catch (exception& ex) {
		cout << ex.what() << endl;
	}

	if (gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", MATEMATIKA, Aktivnost(I, 4, "Priprema za takmicenje iz Matematije koje se odrzava u Konjicu 07.02.2019")))
		cout << "Aktivnost uspjesno dodana" << endl;
	/*na nivou svakog razreda se mogu evidentirati maksimalno 4 aktivnosti, a takodjer, na nivou razreda se ne smiju ponavljati aktivnosti iz istog predmeta*/
	if (!gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", MATEMATIKA, Aktivnost(I, 4, "Aktivnosti iz matematike")))
		cout << "Aktivnost nije uspjesno dodana" << endl;
	if (gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", HEMIJA, Aktivnost(I, 5, "Priprema otopina za vjezbe iz predmeta Hemija")))
		cout << "Aktivnost uspjesno dodana" << endl;
	if (gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", FIZIKA, Aktivnost(I, 4, "Analiza stepena apsorpcije materijala ")))
		cout << "Aktivnost uspjesno dodana" << endl;
	/*u slucaju da je ucenik uspjesno (ocjenom vecom od 1) realizovao aktivnosti na nivou odredjenog razreda, te posjeduje validan broj telefona,
	u okviru zasebnog thread-a se salje SMS sa sadrzajem "Uspjesno ste okoncali aktivnosti u okviru X razreda sa prosjecnom ocjenom X.X"*/
	if (gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", GEOGRAFIJA, Aktivnost(I, 4, "Izrada 5 reljefa Mostara")))
		cout << "Aktivnost uspjesno dodana" << endl;
	if (gimnazijaMostar.DodajAktivnost("Adel Handzic", MATEMATIKA, Aktivnost(I, 5, "Izrada skripte na temu integralni racun")))
		cout << "Aktivnost uspjesno dodana" << endl;

	//ispisuje sve ucenike i njihove aktivnosti
	cout << gimnazijaMostar << endl;


	pair<Polaznik*, float> par = gimnazijaMostar.GetNajboljegUcenika();
	cout << "Najbolji ucenik je " << par.first->GetImePrezime() << " sa prosjekom " << par.second << endl;

	/*U fajl (npr. Gimnazija.txt) upisati podatke (podatke upisati kao obicni tekst) o skoli i svim ucenicima.
	Nakon upisa, potrebno je ispisati sadrzaj fajla. Parametar tipa bool oznacava da li ce ranije dodani sadrzaj fajla prethodno biti pobrisan*/

	if (gimnazijaMostar.SpasiUFajl("Gimnazija.txt"))
		cout << "Podaci o ucenicima uspjesno pohranjeni u fajl" << endl;
	if (gimnazijaMostar.SpasiUFajl("Gimnazija.txt", true))
		cout << "Podaci o ucenicima uspjesno pohranjeni u fajl" << endl;

	return 0;
}