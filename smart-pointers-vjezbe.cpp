#include <iostream>
#include <memory>
using namespace std;

//typedef shared_ptr<int[]> PPNN;

void unos(shared_ptr<int[]> niz, int max) {
    cout << "<--Unos-->\n";
	for (int i = 0; i < max; i++) {
        cout << "niz[" << i << "] = ";
		cin >> niz[i];
	}
    cin.ignore();
}

void ispis(shared_ptr<int[]> niz, int max) {
    cout << "<--Ispis-->\n";
	for (int i = 0; i < max; i++) {
		cout << niz[i] << " " << &niz[i] << "\n";
	}
}

shared_ptr<int> getAdresaNajmanjiByIndira(shared_ptr<int[]> niz, int max) {
    int lokalni = niz[0], pozicija = 0;
	for (int i = 1; i < max; i++) {
        if (lokalni > niz[i]) {
            lokalni = niz[i];
            pozicija = i;
        }
	}
    shared_ptr<int> l(new int(niz[pozicija]));
    return l;
}

shared_ptr<int> getAdresaNajmanji(shared_ptr<int[]> niz, int max) {
    int najmanjiVrijednost = niz[0], najmanjiIndeks = 0;
    for (int i = 1; i < max; i++) {
        if (najmanjiVrijednost > niz[i]) {
            najmanjiVrijednost = niz[i];
            najmanjiIndeks = i;
        }
    }
	shared_ptr<int> returnPointer(niz, niz.get() + najmanjiIndeks);
    return returnPointer;
}

void main() {

	int max;

    cout << "Unesite velicinu niza: ";
	cin >> max;

	shared_ptr<int[]> niz(new int[max]);

	unos(niz, max);
	ispis(niz, max);
    // Indirin nacin
    // shared_ptr<int> najmanji = getAdresaNajmanjiByIndira(niz, max);
    // koristeci aliasing konstruktor
    shared_ptr<int> najmanji = getAdresaNajmanji(niz, max);

    cout << "Najmanji element:\n"<< *najmanji << " " << najmanji << "\n";

    cin.get();
}