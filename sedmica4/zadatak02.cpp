#include <iostream>
#include <string>

using namespace std;

class BankovniRacun {
	string brojRacuna;
	string imePrezime;
	double stanjeRacuna;
	const double kamatnaStopa; //kamatna stopa je konstantna vrijednost
	static int brojOtvorenihRacuna; //staticka varijabla koja ce ukazivati na broj otvorenih racuna
public:
	BankovniRacun(string, string, double); //konstruktor - 3 parametra
	BankovniRacun(string, double, double); //konstruktor - 3 parametra
	BankovniRacun(string, double); //konstruktor - 2 parametra
	BankovniRacun(string); //konstruktor - 1 parametar
	BankovniRacun(const BankovniRacun&); //konstruktor kopije
	~BankovniRacun(); //destruktor


	double proslijediStanje() const; // get metoda - stanje
	string getBankovniRacun() const; // konstantna metoda - funkcija
	string proslijediBrojRacuna() const; //get metoda - broj racuna

	double izracunajKamatu(); //metoda za izracun iznosa kamate
	void uplata(double); //metoda za uplate na racun
	bool isplata(double);//metoda za isplate s racuna - u slucaju da na racunu nema dovoljno sredstava vraca false
	void infoBankovni();//ispis obiljezja objekta

	void postaviImeiP(string); //modifikacija imena i prezimena
	void setStanje(double);//modifikacija stanja racuna

	static int ukupnoRacuna(); //staticka funkcija koja ce omoguciti prebrojavnje otvorenih racuna
};

int BankovniRacun::brojOtvorenihRacuna = 0;

BankovniRacun::BankovniRacun(string brojRacuna, string imePrezime, double stanjeRacuna)
	: kamatnaStopa(7) {
	this->brojRacuna = brojRacuna;
	this->imePrezime = imePrezime;
	this->stanjeRacuna = stanjeRacuna;
	++brojOtvorenihRacuna;
}

BankovniRacun::BankovniRacun(string brojRacuna, double kamatnaStopa, double stanjeRacuna)
	: kamatnaStopa(kamatnaStopa) {
	this->brojRacuna = brojRacuna;
	this->stanjeRacuna = stanjeRacuna;
	imePrezime = "null";
	++brojOtvorenihRacuna;
}

BankovniRacun::BankovniRacun(string brojRacuna, double stanjeRacuna)
	: kamatnaStopa(7) {
	this->brojRacuna = brojRacuna;
	this->stanjeRacuna = stanjeRacuna;
	imePrezime = "null";
	++brojOtvorenihRacuna;
}

BankovniRacun::BankovniRacun(string brojRacuna)
	: kamatnaStopa(7) {
	this->brojRacuna = brojRacuna;
	imePrezime = "null";
	stanjeRacuna = 0;
	++brojOtvorenihRacuna;
}

BankovniRacun::BankovniRacun(const BankovniRacun& src)
	: kamatnaStopa(src.kamatnaStopa) {
	brojRacuna = src.brojRacuna;
	imePrezime = src.imePrezime;
	stanjeRacuna = src.stanjeRacuna;
	++brojOtvorenihRacuna;
}

string BankovniRacun::getBankovniRacun() const {
	return brojRacuna;
}

double BankovniRacun::izracunajKamatu() {
	return stanjeRacuna * (kamatnaStopa / 100);
}

double BankovniRacun::proslijediStanje() const {
	return stanjeRacuna;
}

string BankovniRacun::proslijediBrojRacuna() const {
	return brojRacuna;
}

void BankovniRacun::uplata(double upl) {
	stanjeRacuna += upl;
}

bool BankovniRacun::isplata(double ispl) {
	if (stanjeRacuna < ispl)
		return false;
	stanjeRacuna -= ispl;
	return true;
}

void BankovniRacun::infoBankovni() {
	cout << "Broj racuna: " << brojRacuna << "\n";
	cout << "Ime i prezime: " << imePrezime << "\n";
	cout << "Stanje racuna: " << stanjeRacuna << "\n";
	cout << "Kamatna stopa: " << kamatnaStopa << "%\n";
}

void BankovniRacun::postaviImeiP(string ip) {
	imePrezime = ip;
}

void BankovniRacun::setStanje(double stanje) {
	stanjeRacuna = stanje;
}

int BankovniRacun::ukupnoRacuna() {
	return brojOtvorenihRacuna;
}

BankovniRacun::~BankovniRacun() {}

int main() {
	//demonstrirati rad svih metoda i za objekte i za pokazivace na objekte tipa bankovni racun
	BankovniRacun obj1("345678910", "Hamo Pipa", 1000);
	BankovniRacun obj2("345678911", 20, 20000.56);
	BankovniRacun obj3("345678912", 1200.75);
	BankovniRacun obj4("345678913");
	BankovniRacun obj5 = obj1;

	obj1.infoBankovni();
	obj2.infoBankovni();
	obj3.infoBankovni();
	obj4.infoBankovni();
	obj5.infoBankovni();

	cout << "\n";

	cout << "obj1 broj racuna: " << obj1.getBankovniRacun() << "\n";
	cout << "obj1 kamata: " << obj1.izracunajKamatu() << "\n";
	cout << "obj1 stanje racuna: " << obj1.proslijediStanje() << "\n";

	obj1.uplata(20);
	obj1.isplata(10);

	cout << "obj1 novo stanje racuna: " << obj1.proslijediStanje() << "\n\n";

	obj2.postaviImeiP("Ime Prezime");
	obj2.setStanje(13.37);
	obj2.infoBankovni();

	cout << "\nUkupno racuna kreirano: " << BankovniRacun::ukupnoRacuna() << "\n";

	return 0;
}
