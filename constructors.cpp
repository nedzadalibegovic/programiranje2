#include <iostream>
using namespace std;

char* charAlloc(const char* arr) {
	if (arr == nullptr)
		return nullptr;

	int len = strlen(arr) + 1;
	char* cpy = new char[len];

	strcpy_s(cpy, len, arr);
	return cpy;
}

class Student {
	static int genIndx;

	const int _brojIndeksa;
	char* _ime;
	char* _prezime;

public:

	// constructor
	Student(const char* ime, const char* prezime) : _brojIndeksa(genIndx++) {
		cout << "Constructor called\n";

		_ime = charAlloc(ime);
		_prezime = charAlloc(prezime);
	}

	// copy constructor
	Student(const Student& src) : _brojIndeksa(src._brojIndeksa) {
		cout << "Copy constructor called\n";

		_ime = charAlloc(src._ime);
		_prezime = charAlloc(src._prezime);
	}

	// move constructor
	Student(Student&& src) : _brojIndeksa(src._brojIndeksa) {
		cout << "Move constructor called\n";

		_ime = src._ime;
		src._ime = nullptr;

		_prezime = src._prezime;
		src._prezime = nullptr;
	}

	// destructor
	~Student() {
		cout << "Destructor called\n";

		delete[] _ime;
		_ime = nullptr;

		delete[] _prezime;
		_prezime = nullptr;
	}

	// print all information about object
	void info() {
		cout << "Broj indeksa: IB" << _brojIndeksa << "\n";
		cout << "Ime: " << _ime << "\n";
		cout << "Prezime: " << _prezime << "\n";
	}

	static void currIndx() {
		cout << "Current index: " << genIndx << "\n";
	}
};

int Student::genIndx = 180000;

Student testMoveConstructor() {
	Student temp("Tester", "Testic");
	return temp;
}

int main() {
	Student nedzad("Nedzad", "Alibegovic");
	nedzad.info();

	Student::currIndx();

	Student haris("Haris", "Mlaco");
	haris.info();
	haris.currIndx();

	Student noviNedzad = nedzad;
	noviNedzad.info();

	cout << "Funckija pozvana\n";
	Student mainTemp = testMoveConstructor();
	cout << "Funckija ugasena\n";

	cin.get();
	return 0;
}