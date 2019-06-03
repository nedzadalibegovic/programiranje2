#include <iostream>
#include <vector>
#include <regex>
#include <exception>
#include <algorithm>
#include <thread>

using namespace std;

const char* crt = "\n-------------------------------------------\n";

class Datum {
	int* _dan, * _mjesec, * _godina;
public:
	Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
	}
	Datum(const Datum& dat) {
		_dan = new int(*dat._dan);
		_mjesec = new int(*dat._mjesec);
		_godina = new int(*dat._godina);
	}

	friend bool jelPoslije(const Datum& prije, const Datum& poslije) {
		if (*prije._godina <= *poslije._godina) {
			if (*prije._mjesec <= *poslije._mjesec) {
				if (*prije._dan <= *poslije._dan) {
					return true;
				}
			}
		}
		return false;
	}

	friend void swap(Datum& lhs, Datum& rhs) {
		using std::swap;

		swap(lhs._dan, rhs._dan);
		swap(lhs._mjesec, rhs._mjesec);
		swap(lhs._godina, rhs._godina);
	}

	Datum& operator=(Datum src) {
		swap(*this, src);
		return *this;
	}

	~Datum() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}
	friend ostream& operator<<(ostream& COUT, const Datum& obj) {
		COUT << *obj._dan << " " << *obj._mjesec << " " << *obj._godina;
		return COUT;
	}

	int brojDana() const {
		int suma = 0;
		suma += *_dan;

		for (size_t i = 1; i < *_mjesec; i++) {
			switch (i) {
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:
					suma += 31;
					break;

				case 2:suma += 28; break;
				case 4:
				case 6:
				case 9:
				case 11:
					suma += 30;
				default:
					break;
			}
		}
		return suma;
	}
};

class Izuzetak : public exception {
	string _funkcija;
public:
	Izuzetak(const char* poruka, const char* funkcija)
		: exception(poruka), _funkcija(funkcija) {}

	void info() {
		cout << "Funkcija: " << _funkcija << "\nPoruka: "
			<< what() << "\n";
	}
};

template <class T1, class T2, int max = 10>
class Kolekcija {
	T1* _elementi1;
	T2* _elementi2;
	int _trenutnoElemenata;
	bool _omoguciDupliranjeElemenata;

	bool isDuplicate(const T1& el1, const T2& el2) {
		for (size_t i = 0; i < _trenutnoElemenata; i++) {
			if (_elementi1[i] == el1 && _elementi2[i] == el2) {
				return true;
			}
		}
		return false;
	}

public:
	Kolekcija(bool omoguciDupliranjeElemenata = false) {
		_trenutnoElemenata = 0;
		_omoguciDupliranjeElemenata = omoguciDupliranjeElemenata;
		_elementi1 = nullptr;
		_elementi2 = nullptr;
	}

	Kolekcija(const Kolekcija& src) {
		_trenutnoElemenata = src._trenutnoElemenata;
		_elementi1 = new T1[_trenutnoElemenata];
		_elementi2 = new T2[_trenutnoElemenata];
		_omoguciDupliranjeElemenata = src._omoguciDupliranjeElemenata;

		for (size_t i = 0; i < _trenutnoElemenata; i++) {
			_elementi1[i] = src._elementi1[i];
			_elementi2[i] = src._elementi2[i];
		}
	}

	~Kolekcija() {
		delete[] _elementi1;
		delete[] _elementi2;
		_elementi1 = nullptr;
		_elementi2 = nullptr;
	}

	friend void swap(Kolekcija& lhs, Kolekcija& rhs) {
		using std::swap;

		swap(lhs._elementi1, rhs._elementi1);
		swap(lhs._elementi2, rhs._elementi2);
		swap(lhs._trenutnoElemenata, rhs._trenutnoElemenata);
		swap(lhs._omoguciDupliranjeElemenata, rhs._omoguciDupliranjeElemenata);
	}

	Kolekcija& operator=(Kolekcija src) {
		swap(*this, src);
		return *this;
	}

	bool AddElement(const T1& el1, const T2& el2) {
		if (_trenutnoElemenata + 1 >= max)
			return false;

		if (isDuplicate(el1, el2))
			return false;

		T1* temp1 = new T1[_trenutnoElemenata + 1];
		T2* temp2 = new T2[_trenutnoElemenata + 1];

		for (size_t i = 0; i < _trenutnoElemenata; i++) {
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];
		}

		temp1[_trenutnoElemenata] = el1;
		temp2[_trenutnoElemenata] = el2;

		delete[] _elementi1;
		delete[] _elementi2;

		_elementi1 = temp1;
		_elementi2 = temp2;

		temp1 = nullptr;
		temp2 = nullptr;

		_trenutnoElemenata += 1;

		return true;
	}

	void RemoveElement(const T1& el) {
		for (size_t i = 0; i < _trenutnoElemenata - 1; i++) {
			if (_elementi1[i] == el) {
				swap(_elementi1[i], _elementi1[i + 1]);
				swap(_elementi2[i], _elementi2[i + 1]);
			}
		}
		_trenutnoElemenata -= 1;

		T1* temp1 = new T1[_trenutnoElemenata];
		T2* temp2 = new T2[_trenutnoElemenata];

		for (size_t i = 0; i < _trenutnoElemenata; i++) {
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];
		}

		delete[] _elementi1;
		delete[] _elementi2;

		_elementi1 = temp1;
		_elementi2 = temp2;

		temp1 = nullptr;
		temp2 = nullptr;
	}

	int GetMax() const { return max; }
	int GetTrenutno() const { return _trenutnoElemenata; }
	T1& GetElement1(int lokacija) const {
		if (lokacija < 0 || lokacija >= _trenutnoElemenata)
			throw Izuzetak("Nepostojeca lokacija", __FUNCTION__);
		return _elementi1[lokacija];
	}

	T2& GetElement2(int lokacija) const {
		if (lokacija < 0 || lokacija >= _trenutnoElemenata)
			throw Izuzetak("Nepostojeca lokacija", __FUNCTION__);
		return _elementi2[lokacija];
	}
	friend ostream& operator<<(ostream& COUT, const Kolekcija& obj) {
		for (size_t i = 0; i < obj.GetTrenutno(); i++)
			COUT << obj._elementi1[i] << " " << obj._elementi2[i] << endl;
		return COUT;
	}
};

class Dogadjaj {
	Datum _datumOdrzavanja;
	Kolekcija<string, bool>* _obaveze; //cuva informaciju o obavezama koje je potrebno ispuniti prije samog dogadjaja, string se odnosi na opis, a bool na izvrsenje te obaveze (da li je zavrsena ili ne)

	char* _naziv;
	int _notificirajPrije; //oznacava broj dana prije samog dogadjaja kada ce krenuti notifikacija/podsjetnik
	bool _rekurzivnaNotifikacija; //ako je vrijednost true onda se korisnik notificira svaki dan do _datumaOdrzavanja dogadjaja, a pocevsi prije dogadjaja za _brojDanaZaNotifikaciju

public:
	float getPostotak() {
		float postotak = 0;
		for (size_t i = 0; i < _obaveze->GetTrenutno(); i++) {
			if (_obaveze->GetElement2(i))
				postotak += 1;
		}
		return postotak /= _obaveze->GetTrenutno();
	}
	void ispisiZavrseneObaveze() {
		int brojac = 1;
		cout << endl;
		for (int i = 0; i < _obaveze->GetTrenutno(); i++) {

			if (_obaveze->GetElement2(i) == false) {
				cout << brojac++ << ". " << _obaveze->GetElement1(i) << endl;
			}
		}
	}
	Dogadjaj(Datum datumOdrzavanja, const char* naziv, int brojDana = 1,
			 bool rekurzivnaNotifikacija = false) : _datumOdrzavanja(datumOdrzavanja) {
		_naziv = new char[strlen(naziv) + 1];
		strcpy_s(_naziv, strlen(naziv) + 1, naziv);

		_notificirajPrije = brojDana;
		_rekurzivnaNotifikacija = rekurzivnaNotifikacija;
		_obaveze = nullptr;
	}

	Dogadjaj(const Dogadjaj& obj) :
		_datumOdrzavanja(obj._datumOdrzavanja) {
		_naziv = new char[strlen(obj._naziv) + 1];
		strcpy_s(_naziv, strlen(obj._naziv) + 1, obj._naziv);
		_obaveze = new Kolekcija<string, bool>(*obj._obaveze);
		_notificirajPrije = obj._notificirajPrije;
		_rekurzivnaNotifikacija = obj._rekurzivnaNotifikacija;
	}

	friend void swap(Dogadjaj& lhs, Dogadjaj& rhs) {
		using std::swap;

		swap(lhs._datumOdrzavanja, rhs._datumOdrzavanja);
		swap(lhs._naziv, rhs._naziv);
		swap(lhs._notificirajPrije, rhs._notificirajPrije);
		swap(lhs._obaveze, rhs._obaveze);
		swap(lhs._rekurzivnaNotifikacija, rhs._rekurzivnaNotifikacija);
	}

	friend bool operator==(const Dogadjaj& lhs, const Dogadjaj& rhs) {
		return !strcmp(lhs._naziv, rhs._naziv);
	}

	bool operator==(const char* naziv) {
		return !strcmp(_naziv, naziv);
	}

	Dogadjaj& operator=(Dogadjaj src) {
		swap(*this, src);
		return *this;
	}

	~Dogadjaj() {
		delete[] _naziv;
		_naziv = nullptr;
		delete _obaveze;
		_obaveze = nullptr;
	}

	bool AddObavezu(const char* obaveza) {
		static string uslov = R"(Samo)";

		if (_obaveze == nullptr)
			_obaveze = new Kolekcija<string, bool>;

		if (regex_search(obaveza, regex(uslov)))
			return false;

		return _obaveze->AddElement(obaveza, false);
	}

	Datum& getDatum() {
		return _datumOdrzavanja;
	}

	char* GetNaziv() { return _naziv; }
	Kolekcija<string, bool>* GetObaveze() { return _obaveze; }

};

class Student {
	int _indeks;
	string _imePrezime;
	vector<Dogadjaj> _dogadjaji;
public:

	Student(int indeks, string imePrezime) : _indeks(indeks), _imePrezime(imePrezime) {}

	int GetIndeks() const { return _indeks; }

	string& getImePrezime() { return _imePrezime; }

	vector<Dogadjaj>& GetDogadjaji() { return _dogadjaji; }

	friend ostream& operator<<(ostream& COUT, const Student& obj) {
		COUT << obj._imePrezime << " (" << obj._indeks << ")" << endl;
		return COUT;
	}

	friend bool operator==(const Student& lhs, const Student& rhs) {
		return lhs._indeks == rhs._indeks;
	}

	bool operator==(int indeks) const {
		return _indeks == indeks;
	}

	bool AddDogadjaj(const Dogadjaj& dogadjaj) {
		if (find(_dogadjaji.begin(), _dogadjaji.end(), dogadjaj) != _dogadjaji.end())
			return false;

		_dogadjaji.push_back(dogadjaj);
		return true;
	}

};

class DLWMSReminder {
	vector<Student> _reminiderList;
public:
	void AddStudent(const Student& obj) {
		if (find(_reminiderList.begin(), _reminiderList.end(), obj)
			!= _reminiderList.end())
			throw Izuzetak("Dupli element!", __FUNCTION__);

		_reminiderList.push_back(obj);
	}

	bool OznaciObavezuKaoZavrsenu(int indeks, const char* dogadjaj, const char* obaveza) {
		for (size_t i = 0; i < _reminiderList.size(); i++) {
			if (_reminiderList[i] == indeks) {
				Student& stud = _reminiderList[i];
				for (size_t i = 0; i < stud.GetDogadjaji().size(); i++) {
					if (stud.GetDogadjaji()[i] == dogadjaj) {
						Dogadjaj& dog = stud.GetDogadjaji()[i];
						for (size_t i = 0; i < dog.GetObaveze()->GetTrenutno(); i++) {
							if (dog.GetObaveze()->GetElement1(i) == obaveza) {
								if (!dog.GetObaveze()->GetElement2(i)) {
									dog.GetObaveze()->GetElement2(i) = true;
									return true;
								}
							}
						}
					}
				}
			}
		}
		return false;
	}

	int PosaljiNotifikacije(const Datum& datum) {
		int poslato = 0;

		thread trazi([&]() {
			for (int i = 0; i < _reminiderList.size(); i++) {
				vector<Dogadjaj>& dog = _reminiderList[i].GetDogadjaji();
				for (int j = 0; j < dog.size(); j++) {
					if (jelPoslije(datum, dog[j].getDatum())) {
						poslato += 1;
						cout << crt;
						cout << "Postovani " << _reminiderList[i].getImePrezime() << endl;
						cout << "Dogadjaj: " << dog[j].GetNaziv() << " je zakazan za: " << dog[j].getDatum().brojDana() - datum.brojDana() << " dana\n";
						cout << "Do sada ste obavili " << dog[j].getPostotak() * 100 << "% obaveza vezanih za ovaj dogadjaj" << endl;
						cout << "Neispunjene obaveze su:";
						dog[j].ispisiZavrseneObaveze();
						cout << "Predlazemo vam da ispunite i ostale neispunjene obaveze" << endl;
						cout << crt;
					}
				}
			}
					 });

		trazi.join();
		return poslato;
	}
};

int main() {

	/**************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR CE BITI OZNACENO KAO "RE"
	3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKODJER NALAZI U FAJLU CODE_ParcijalniII.TXT
	5. NAZIVI FUNKCIJA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U.OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI PO ŽELJI.
	****************************************************************************/

#pragma region Datum

	Datum danas(28, 1, 2018), sutra(29, 1, 2018);
	Datum datumIspitaPRIII(30, 1, 2018), datumIspitBPII(31, 1, 2018);
	Datum prekosutra(danas);
	prekosutra = danas;
	cout << danas << endl
		<< sutra << endl
		<< prekosutra << crt;

#pragma endregion

#pragma region Kolekcija

	/*
	AddElement :: omogucava dodavanje novog elementa u kolekciju. Ukoliko je moguce, osigurati automatsko prosiranje kolekcije prilikom dodavanja svakog novog elementa, te onemoguciti ponavljanje elemenata
	RemoveElement :: na osnovu parametra tipa T1 uklanja elemente iz kolekcije i ukoliko je moguce smanjuje velicinu niza/kolekcije. Prilikom uklanjanja elemenata ocuvati redoslijed njihovog dodavanja
	*/
	Kolekcija<int, float, 10> kolekcija1;
	for (size_t i = 0; i < kolekcija1.GetMax(); i++)
		if (!kolekcija1.AddElement(i, i + (0.6 * i)))
			cout << "Elementi " << i << " i " << i + (0.6 * i) << " nisu dodati u kolekciju" << endl;

	cout << kolekcija1.GetElement1(0) << " " << kolekcija1.GetElement2(0) << endl;
	cout << kolekcija1 << endl;

	kolekcija1.RemoveElement(1);

	Kolekcija<int, float, 10> kolekcija2;
	kolekcija2 = kolekcija1;
	cout << kolekcija2 << crt;

	if (kolekcija1.GetTrenutno() == kolekcija2.GetTrenutno())
		cout << "ISTI BROJ ELEMENATA" << endl;

	Kolekcija<int, float, 10> kolekcija3(kolekcija2);
	cout << kolekcija3 << crt;

#pragma endregion

#pragma region Dogadjaj

	Dogadjaj ispitPRIII(datumIspitaPRIII, "Ispit iz PRIII", 5, true),
		ispitBPII(datumIspitBPII, "Ispit iz BPII", 7, true);
	/*po vlasitom izboru definisati listu zabranjenih rijeci koje ce onemoguciti dodavanje odredjene obaveze. Prilikom provjere koristiti regex*/
	if (ispitPRIII.AddObavezu("Preraditi pdf materijale"))
		cout << "Obaveza dodana!" << endl;
	//onemoguciti dupliranje obaveza
	if (!ispitPRIII.AddObavezu("Preraditi pdf materijale"))
		cout << "Obaveza nije dodana!" << endl;
	if (ispitPRIII.AddObavezu("Pregledati video materijale"))
		cout << "Obaveza dodana!" << endl;
	if (ispitPRIII.AddObavezu("Preraditi ispitne zadatke"))
		cout << "Obaveza dodana!" << endl;
	if (ispitPRIII.AddObavezu("Samostalno vjezbati"))
		cout << "Obaveza dodana!" << endl;
	if (ispitBPII.AddObavezu("Preraditi knjigu SQL za 24"))
		cout << "Obaveza dodana!" << endl;
	if (ispitBPII.AddObavezu("Pregledati video materijale"))
		cout << "Obaveza dodana!" << endl;
	if (ispitBPII.AddObavezu("Napraviti bazu za konkretnu aplikaciju"))
		cout << "Obaveza dodana!" << endl;

	Student jasmin(150051, "Jasmin Azemovic"), adel(160061, "Adel Handzic");

	if (jasmin.AddDogadjaj(ispitPRIII) && jasmin.AddDogadjaj(ispitBPII))
		cout << "Dogadjaj uspjesno dodan!" << endl;

	if (adel.AddDogadjaj(ispitPRIII) && adel.AddDogadjaj(ispitBPII))
		cout << "Dogadjaj uspjesno dodan!" << endl;
	//onemoguciti dupliranje dogadjaja
	if (!adel.AddDogadjaj(ispitPRIII))
		cout << "Dogadjaj nije uspjesno dodan!" << endl;

	DLWMSReminder reminder;

	try {
		reminder.AddStudent(jasmin);
		reminder.AddStudent(adel);
		//u slucaju dupliranja studenata funkcija baca izuzetak tipa Izuzetak
		//reminder.AddStudent(jasmin);
	} catch (Izuzetak& err) {
		//ispisati sve informacije o nastalom izuzetku
		err.info();
	} catch (exception& err) {
		cout << err.what() << endl;
	}

	//da bi bila oznacena kao zavrsena, obaveza mora postojati i mora biti oznacena kao nezavrsena (false)
	if (reminder.OznaciObavezuKaoZavrsenu(150051, "Ispit iz PRIII", "Pregledati video materijale"))
		cout << "Obaveza oznacena kao zavrsena" << endl;

	/*metodi PosaljiNotifikacije se salje trenutni datum na osnovu cega ona pretrazuje sve studente
	koje treba podsjetiti/notoficirati o dogadjajima koji se priblizavaju.
	Koristeci multithread-ing, svim studentima se salju notifikacije sa sljedecim sadrzajem:
	-------------------------------------------------------------------------
	Postovani Jasmin Azemovic,
	Dogadjaj Ispit iz PRIII je zakazan za 2 dana, a do sada ste obavili 56% obaveza vezanih za ovaj
	dogadjaj. Neispunjene obaveze su:
		1.Preraditi ispitne zadatke
		2.Samostalno vjezbati
	Predlazemo Vam da ispunite i ostale planirane obaveze.
	FIT Reminder
	-------------------------------------------------------------------------
	Dakle, notifikacije ce biti poslane svim studentima koji su dodali dogadjaj za 30.01.2018.
	godine i oznacili da zele da budu podsjecani ponovo/rekurzivno najmanje 2 dana prije samog dogadjaja
	(podaci se odnose na konkretan dogadjaj: Ispit iz PRIII)
	*/
	int poslato = 0;
	//funkcija vraca broj poslatih podsjetnika/notifikacija
	poslato = reminder.PosaljiNotifikacije(danas);
	cout << "Za " << danas << " poslato ukupno " << poslato << " podsjetnika!" << endl;
	poslato = reminder.PosaljiNotifikacije(sutra);
	cout << "Za " << sutra << " poslato ukupno " << poslato << " podsjetnika!" << endl;

#pragma endregion
}