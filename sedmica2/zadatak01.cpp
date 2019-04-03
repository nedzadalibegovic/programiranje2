#include <iostream>
#include <string>
using namespace std;

class Osoba {
    string imePrezime;
    float visina;
    float masa;
public:
    void inicijalizacija(string, float, float);
    void predstaviSe();
    Osoba(string imePrezime = "null", float visina = 0.0f, float masa = 0) {
        this->imePrezime = imePrezime;
        this->visina = visina;
        this->masa = masa;
    }
};

void Osoba::inicijalizacija(string IP, float V, float M) {
    imePrezime = IP;
    visina = V;
    masa = M;
}
void Osoba::predstaviSe() {
    cout << "Ime i prezime: " << imePrezime << endl;
    cout << "Visina: " << visina << endl;
    cout << "Masa: " << masa << endl;

}


void main() {

    Osoba O1;

    string IP;
    float vis, mas;

    cout << "Unesite ime i prezime" << endl;
    cin >> IP;
    cout << "Unesite visinu" << endl;
    cin >> vis;
    cout << "Unesite masu" << endl;
    cin >> mas;
    
    O1.inicijalizacija(IP, vis, mas);
    O1.predstaviSe();


    // Windows specific
    system("pause");
}