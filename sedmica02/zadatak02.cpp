#include <iostream>
#include <string>
using namespace std;

class Osoba {
    string ime;
    string prezime;
    int godine;
public:
    void create(string i, string p, int g);

    void setIme(string i);
    char* getIme();

    void setPrezime(string p);
    char* getPrezime();

    void setGodine(int g);
    int getGodine();

    void predstaviSe();
    void DanasJeRodjendan();
};


void main() {



    system("pause");
}