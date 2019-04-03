#include <iostream>
using namespace std;

template <class T>
class Vector {
	T* _items;
	int _numberOfItems;

public:
	Vector() : _items(nullptr), _numberOfItems(0) {}

	~Vector() {
		delete[] _items;
	}

	void push_back(const T& item) {
		T* arr = new T[_numberOfItems + 1];

		for (size_t i = 0; i < _numberOfItems; i++)
			arr[i] = _items[i];
		arr[_numberOfItems++] = item;

		delete[] _items;
		_items = arr;
	}

	void print() const {
		for (size_t i = 0; i < _numberOfItems; i++)
			cout << _items[i] << "\n";
	}

	int getSize() const {
		return _numberOfItems;
	}

	int getLastIndex() const {
		return _numberOfItems - 1;
	}
};

int main() {
	Vector<float> vkt;
	for (int i = 0; i < 100; i++)
		vkt.push_back(i * i);
	vkt.print();
	cout << "Size: " << vkt.getSize() << "\n";
	cout << "Last index: " << vkt.getLastIndex() << "\n";
}