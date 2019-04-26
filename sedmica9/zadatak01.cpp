#include <iostream>
using namespace std;

// osnovna klasa
class KucniLjubimac {
	char ime[20];
	int starost;
public:
	KucniLjubimac() : ime("Tester"), starost(20) {}

	const char* GetIme() const {
		return ime;
	}

	void SetIme(const char* ime) {
		strcpy_s(this->ime, 20, ime);
	}

	int GetStarost() const {
		return starost;
	}

	void SetStarost(int starost) {
		this->starost = starost;
	}
};

// izvedena klasa
class Pas : public KucniLjubimac {
public:
	Pas() : KucniLjubimac() {}

	void OglasiSe() {
		cout << GetIme() << " " << GetStarost() << "\n";
	}
};

int main() {
	Pas reks;
	reks.OglasiSe();
}