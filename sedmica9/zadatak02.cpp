#include <iostream>
using namespace std;

char* charAlloc(const char* src) {
	if (src == nullptr)
		return nullptr;
	int len = strlen(src) + 1;
	char* out = new char[len];
	strcpy_s(out, len, src);
	return out;
}

const char* br = "<--------->\n";

class Animal {
protected:
	char* vrsta;
	int starost;
public:
	Animal(const char* spiece, int age) {
		vrsta = charAlloc(spiece);
		starost = age;
	}

	~Animal() {
		delete[] vrsta;
	}

	char* getVrsta() { return vrsta; }
	int getStarost() { return starost; }
	void setVrsta(const char* spiece) { vrsta = charAlloc(spiece); }
	void setStarost(int age) { starost = age; }

	void predstaviSe() {
		cout << "Vrsta: " << vrsta << "\nStarost: " << starost << "\n";
	}
};

class Friend {
protected:
	char* ime;
	char spol;
	double masa;
public:
	Friend(const char* name, char sex, double weight) {
		ime = charAlloc(name);
		spol = sex;
		masa = weight;
	}

	~Friend() {
		delete[] ime;
	}

	char* getIme() { return ime; }
	char getSpol() { return spol; }
	double getMasa() { return masa; }
	void setMasa(double masa) { this->masa = masa; }
	void setIme(char* name) { ime = charAlloc(name); }
	void setSpol(char sex) { spol = sex; }

	void predstaviSe() {
		cout << "Ime: " << ime << "\nSpol: " << spol << "\nMasa: " << masa << "\n";
	}
};

class Dog : public Animal, public Friend {
	char* boja;
	char* vlasnik;
public:
	Dog(const char* collor, const char* owner, const char* vrsta, int starost,
		const char* ime, char spol, double masa) : Animal(vrsta, starost), Friend(ime, spol, masa) {
		boja = charAlloc(collor);
		vlasnik = charAlloc(owner);
	}

	~Dog() {
		delete[] boja;
		delete[] vlasnik;
	}

	char* getBoja() { return boja; }
	char* getVlasnik() { return vlasnik; }
	void setBoja(char* collor) { boja = charAlloc(collor); }
	void setVlasnik(char* owner) { vlasnik = charAlloc(owner); }

	void predstaviSe() {
		Animal::predstaviSe();
		Friend::predstaviSe();
		cout << "Boja: " << boja << "\nVlasnik: " << vlasnik << "\n";
	}
};

int main() {
	// demonstrirati rad svih kreiranih metoda;
	Animal test("Pas", 12);
	test.predstaviSe();

	cout << br;

	Friend tester("Cojk", 'm', 12);
	tester.predstaviSe();

	cout << br;

	Dog reks("Smedja", "Hamdo", "Pas", 12, "Pipa", 'M', 20);
	reks.predstaviSe();
}