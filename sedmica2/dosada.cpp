#include <iostream>
#include <string>
#include <random>
#include <ctime>
using namespace std;



void gen_random(char *s, const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

void main() {
    srand(time(0));

    while (true) {
        char* s = new char[100000];
        gen_random(s,100000);
        cout << s;
        new double[10000000];
    }
}