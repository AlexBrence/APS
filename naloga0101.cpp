#include <iostream>

using namespace std;

struct Sklad {
    int *S;
    int vrh;
    int MAX;
    bool zakljuci;
} s;

void izpisMenija();

// Za vnos v Sklad
void push(int vnos) {
    s.vrh++;
    s.S[s.vrh] = vnos;
}


void pop() {
    if (s.vrh == -1) {
        cout << "NAPAKA, PRAZNO!" << endl;
    }
    else {
        cout << "ŠTEVILO: " << s.S[s.vrh];
        s.vrh--;
    }
}


void izpisSklada() {
    if (s.vrh == -1) {
        cout << "SKLAD JE PRAZEN!" << endl;
    }
    else {
        cout << "Sklad: ";
        for (int i = 0; i <= s.vrh; ++i) {
            cout << s.S[i] << ", ";
        }
        cout << endl;
    }
}



void izpisMenija() {

    int izbira;
    int steviloPush;

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
    cin >> izbira;

    switch (izbira) {
        case 1 :
            if (s.vrh == s.MAX-1) {
                cout << "NAPAKA, POLNO!";
                break;
            }
            else {
                cout << "Vnesi število: " << endl;
                cin >> steviloPush;
                push(steviloPush);
                break;
            }
        case 2 :
            pop();
            break;
        case 3 :
            izpisSklada();
            break;
        case 7 :
            s.zakljuci = true;
            break;
        default :
            izpisMenija();
    }
}


int main() {
    cout << "Vnesi velikost polja: " << endl;
    cin >> s.MAX;

    s.S = new int[s.MAX];
    s.vrh = -1;
    s.zakljuci = false;

    while (!s.zakljuci) {
            izpisMenija();
    }

    return 0;
}
