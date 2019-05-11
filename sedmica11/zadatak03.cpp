#include <iostream>
using namespace std;

class vozilo {
private:
	float brzina;
	char tipVozila[20];
public:
	vozilo(const char* tip, float brzina);
	char* getTipVozila();
	float getBrzina();
	void setBrzina(float brz);
	virtual void ispisi();
};

class terenskoVozilo : public vozilo {
private:
	int brojTockova;
	float nosivost;
public:
	terenskoVozilo(const char* Tip, int brTockova, float brzina, float nosivost);
	int getBrojTockova();
	float getNosivost();
	void setNosivost(float nosivost);
	virtual void ispisi();
};

class vodenoVozilo : public vozilo {
private:
	float minDubina;
	float nosivost;
public:
	vodenoVozilo(const char* tip, float minDubina, float brzina, float nosivost);
	float getMinDubina();
	float getNosivost();
	void setNosivost(float nosivost);
	virtual void ispisi();
};

class amfibija : public vodenoVozilo, public terenskoVozilo {
private:
	float precnik_pr;
public:
	amfibija(char* tip, float minDubina, float brzina, int b_tockova,
			 float nosivost_k, float nosivost_v, float precnik_pr);
	float getPrecnik_pr();
	void ispisi();
};

int main() {}