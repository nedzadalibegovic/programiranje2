#include <iostream>
#include <string>
using namespace std;

class Vehicle {
public:
    virtual void Info() {
        cout << "Color: " << _color << "\n";
    }

private:
    string _color = "red";

protected:
    int _fuel;
    int _capacity;
};

class Bus : public Vehicle {
public:
    void Info() {
        cout << "Color: " << _color << "\n";
    }

private:

};


void main() {
    Bus autobus;

    autobus.Info();
}