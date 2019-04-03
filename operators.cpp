#include <iostream>
using namespace std;

class Coordinates {
	int _x, _y;
public:

	friend ostream& operator << (ostream&, const Coordinates&);
	friend istream& operator >> (istream&, Coordinates&);

	Coordinates(int x, int y) {
		_x = x;
		_y = y;
	}

	int getX() const {
		return _x;
	}

	int getY() const {
		return _y;
	}
};

ostream& operator << (ostream& COUT, const Coordinates& obj) {
	COUT << "X: " << obj._x << ", Y: " << obj._y;

	return COUT;
}

istream& operator >> (istream& CIN, Coordinates& obj) {
	cout << "X: ";
	CIN >> obj._x;

	cout << "Y: ";
	CIN >> obj._y;

	return CIN;
}

int main() {
	Coordinates mos(10, 10);
	cout << mos << "\n";
	cin >> mos;
	cout << mos << "\n";

	return 0;
}