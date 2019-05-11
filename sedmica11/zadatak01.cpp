#include <iostream>
using namespace std;

//apstraktna klasa
class KucniLjubimac {
protected:
	char ime[20];
	int starost;
public:
	KucniLjubimac(const char* i, int s) {
		strcpy_s(ime, 20, i);
		starost = s;
	}
	char* GetIme() const { return &ime; }
	int GetStarost() const { return starost; }
	virtual void OglasiSe() = 0; //cista virtuelna funkcija
};

class Pas : public KucniLjubimac {
public:
	Pas(const char* i, int s);
	void OglasiSe() { cout << "VAU VAU" << endl; }
};

class Macka : public KucniLjubimac {
public:
	Macka(const char* i, int s);
	void OglasiSe() { cout << "MIJAUUU" << endl; }
};

class Rotvajler : public Pas {
public:
	Rotvajler(const char* i, int s);
	void OglasiSe() { cout << "VUF VUF" << endl; }
};

int main() {
	//kreirati objekte klasa i demonstrirati rad metoda
	return 0;
}