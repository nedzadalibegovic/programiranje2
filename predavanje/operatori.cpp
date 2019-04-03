#include <iostream>
using namespace std;

class String {
	char* _content;

	char* charAlloc(const char* src) {
		int len = strlen(src) + 1;
		char* rt = new char[len];
		strcpy_s(rt, len, src);
		return rt;
	}

public:
	String(const char* str) : _content(charAlloc(str)) {}

	String(const String& src) : _content(charAlloc(src._content)) {}

	String(String&& src) {
		_content = src._content;
		src._content = nullptr;
	}

	// copy-and-swap idiom
	String& operator=(String str) {
		zamjeni(*this, str);
		return *this;
	}

	String& operator+=(const String& str) {
		int vel = strlen(_content) + 1 + strlen(str._content) + 1;
		char* rt = new char[vel];

		strcpy_s(rt, vel, _content);
		strcat_s(rt, vel, str._content);
		
		delete[] _content;
		_content = rt;

		return *this;
	}

	char& operator[](const int& index) {
		return _content[index];
	}

	friend void zamjeni(String& lhs, String& rhs) {
		swap(lhs._content, rhs._content);
	}

	friend ostream& operator<<(ostream& COUT, const String& str) {
		COUT << str._content;
		return COUT;
	}
};

int main() {
	String test = "Nedzad";
	test += " Alibegovic";
	cout << test << "\n";
	cout << test[2] << "\n";
	test[2] = 'A';
	cout << test << "\n";
}