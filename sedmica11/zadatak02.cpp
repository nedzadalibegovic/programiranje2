#include <iostream>
using namespace std;

class Osoba {
	char* ime;
	char* prezime;
public:
	Osoba(const char* i, const char* p);
	Osoba(Osoba&);
	virtual ~Osoba();
	void IspisiPodatke();
};

class Zena {
	char* djevPrezime;
public:
	Zena(const char* i, const char* p, const char* d);
	Zena(Zena&);
	~Zena();
	void IspisiPodatke();
};

int main() {}