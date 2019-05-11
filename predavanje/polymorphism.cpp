#include <iostream>
using namespace std;

class Date {
	int day, month, year;
public:
	Date(int day, int month, int year) {
		this->day = day;
		this->month = month;
		this->year = year;
	}

	friend ostream& operator<<(ostream& out, const Date& obj) {
		out << obj.day << "." << obj.month << "." << obj.year;
		return out;
	}
};

class Person {
	string _name;
	Date _dateOfBirth;
public:
	Person(const char* name, int day, int month, int year)
		: _name(name), _dateOfBirth(day, month, year) {}

	virtual void info() {
		cout << "Name: " << _name << "\nDate: " << _dateOfBirth << "\n";
	}
};

class Worker : public Person {
	string _employer;
	double _salary;
public:
	Worker(const char* name, int day, int month, int year,
		   const char* employer, double salary)
		: Person(name, day, month, year), _employer(employer) {
		_salary = salary;
	}

	void info() {
		Person::info();
		cout << "Employer: " << _employer << "\nSalary: " << _salary << "\n";
	}
};

int main() {
	Person* arr[2] = { new Person("John Doe",12,12,1990), new Worker("Jane Doe",11,11,1999,"Generic",2400.00) };

	for (size_t i = 0; i < 2; i++)
		arr[i]->info();
}