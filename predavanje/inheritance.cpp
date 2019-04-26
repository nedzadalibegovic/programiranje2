#include <iostream>
#include <memory>
using namespace std;

char* charAlloc(const char* src) {
	int vel = strlen(src) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, src);
	return temp;
}

void ptrAlloc(unique_ptr<char[]>& target, const char* txt) {
	int len = strlen(txt) + 1;
	target = make_unique<char[]>(len);
	strcpy_s(target.get(), len, txt);
}

class Osoba {
	unique_ptr<char[]> _imePrezime;

public:
	Osoba(const char* imePrezime) {
		ptrAlloc(_imePrezime, imePrezime);
	}

	Osoba(const Osoba& src) {
		ptrAlloc(_imePrezime, src._imePrezime.get());
	}

	Osoba(Osoba&& src) noexcept {
		_imePrezime = move(src._imePrezime);
	}

	friend ostream& operator<<(ostream& COUT, const Osoba& obj) {
		COUT << obj._imePrezime.get();
		return COUT;
	}
};

class Student : public Osoba {
	int _brojIndeksa;
public:
	Student(const char* imePrezime, int brojIndeksa) : Osoba(imePrezime) {
		_brojIndeksa = brojIndeksa;
	}

	Student(const Student& src) : Osoba(src) {
		_brojIndeksa = src._brojIndeksa;
	}

	Student(const Student&& src) noexcept : Osoba(src) {
		_brojIndeksa = src._brojIndeksa;
	}

	friend ostream& operator<<(ostream& COUT, const Student& obj) {
		COUT << Osoba(obj);
		COUT << " " << obj._brojIndeksa;
		return COUT;
	}
};

int main() {
	Student hamo("Hamo Pipa", 180001);
	cout << hamo;
}