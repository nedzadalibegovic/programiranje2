#include <iostream>
using namespace std;

class Porez {
public:
	int poreska_skupina;
	float procenat;

	//konstruktor klase porez
	Porez(int skupina, float proc) {
		poreska_skupina = skupina;
		procenat = proc;
	}
	void infoPorez() {
		cout << "Poreska skupina: " << poreska_skupina << "\n";
		cout << "Procenat: " << procenat << "%\n";
	}
};

class Artikal {
	Porez p;	//klasa artikal kao atribut sadrzi objekat klase porez 
	float cijena;
	char naziv[20];
	float& c; //referenca na cijenu artikla
	const int artikalID; //konstanta
	static int brojacArtikala; //staticka varijabla

public:
	// konstruktor klase artikal- voditi racuna o obiljezju p koje je tipa porez
	Artikal(const char naziv[], float cij, int skupina, float proc)
			: p(skupina,proc), artikalID(brojacArtikala++), c(cijena) {
		strcpy_s(this->naziv, 20, naziv);
		cijena = cij;
	}

	//ispis obiljezja artikla
	void PrintInfo() {
		cout << "Artikal ID: " << artikalID << "\n";
		cout << "Naziv: " << naziv << "\n";
		cout << "Cijena: " << cijena << "\n";
		cout << "Referenca: " << c << "\n";
		p.infoPorez();
	}

	/*staticka funkcija koja treba da vrati informaciju koliko artikala je kreirano do tog momenta*/
	static int GetBrojArtikala() {
		return brojacArtikala;
	}
};

int Artikal::brojacArtikala = 0;

int main() {
	//Kreirati testni program koji demonstrira implementirane funckionalnosti
	Artikal obj1("Cigare", 5.40, 2, 17);
	Artikal obj2("Stikle", 90.75, 3, 21);

	obj1.PrintInfo();
	obj2.PrintInfo();

	cout << "Broj artikala: " << Artikal::GetBrojArtikala() << "\n";

	return 0;
}
