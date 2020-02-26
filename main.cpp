#include <iostream>

using namespace std;

struct Sklad {
    int *S;
    int vrh;
    int MAX;
} s;

void izpisMenija();

// Za vnos v Sklad
void push(int vnos) {
    if (s.vrh == s.MAX) {
        cout << "NAPAKA, POLNO!" << endl;
        izpisMenija();
    }
    else {
        s.S[s.vrh] = vnos;
        s.vrh++;
        izpisMenija();
    }
}


void pop() {
    if (s.vrh == 0) {
        cout << "NAPAKA, PRAZNO!" << endl;
        izpisMenija();
    }
    else {
        cout << s.S[s.vrh];
        cout << "Število: " << s.vrh--;
        izpisMenija();
    }
}


void izpisSklada() {
    if (s.vrh == 0) {
        cout << "SKLAD JE PRAZEN!" << endl;
        izpisMenija();
    }
    else {
        cout << "Sklad: ";
        for (int i = 0; i < s.vrh; ++i) {
            cout << s.S[i] << ", ";
        }
        cout << endl;
        izpisMenija();
    }
}



void izpisMenija() {

    // SKLAD
    cout << endl << "Sklad - izbira:" << endl;
    cout << "1. Vnos podatka" << endl;
    cout << "2. Branje podatka" << endl;
    cout << "3. Izpis vsebine podatka" << endl << endl;

    // KROŽNA VRSTA
    cout << "Krožna vrsta - izbira:" << endl;
    cout << "4. Vnos podatka" << endl;
    cout << "5. Branje podatka" << endl;
    cout << "6. Izpis vrste od glave do repa " << endl << endl;

    cout << "7. Konec" << endl << endl;

    cout << "Izbira:";

}


int main() {
    cout << "Vnesi velikost polja: " << endl;
    cin >> s.MAX;
    s.S = new int[s.MAX];
    s.vrh = 0;
    int izbira;
    int steviloPush;

    izpisMenija();

    switch (izbira) {
        case 1 :
            cout << "Vnesi število: " << endl;
            cin >> steviloPush;
            push(steviloPush);
        case 2 :
            pop();
        case 3 :
            izpisSklada();
    }

    return 0;
}
