#include <iostream>
using namespace std;

template <class T>
struct Node {
	T _data;
	Node<T>* _next;

	Node(const T& data) {
		_data = data;
		_next = nullptr;
	}

	~Node() {
		delete _next;
	}
};

template <class T>
class List {
	Node<T>* _head;
	Node<T>* _tail;
	int _size;

public:
	List() {
		_head = nullptr;
		_tail = nullptr;
		_size = 0;
	}

	void add(const T& data) {
		if (_size) {
			_tail->_next = new Node<T>(data);
			_tail = _tail->_next;
			_size += 1;
		} else {
			_head = new Node<T>(data);
			_tail = _head;
			_size += 1;
		}
	}

	void addFront(const T& data) {
		if (_size) {
			Node<T>* temp = new Node<T>(data);
			temp->_next = _head;
			_head = temp;
			_size += 1;
		} else {
			_head = new Node<T>(data);
			_tail = _head;
			_size += 1;
		}
	}

	void print() {
		Node<T>* ptr = _head;
		while (ptr != nullptr) {
			cout << ptr->_data << "\n";
			ptr = ptr->_next;
		}
	}

	int getSize() const {
		return _size;
	}

	~List() {
		delete _head;
		_head = nullptr;
		_tail = nullptr;
	}
};

int main() {
	List<int> list;

	for (int i = 0; i < 50; i++)
		list.add(i * 2);

	list.print();
}