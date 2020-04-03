#include <iostream>
#include <string>
#include <map>
#include <list>
#include <fstream>
#include <ostream>
#include <algorithm>
#include <chrono>

using namespace std;


std::map<int, list<string>> T;
bool running = true;


void vnosFilma(int datum, string ime) {
    list<string> seznam;

    if (T.find(datum) == T.end()) {
        seznam.push_back(ime);
        T.insert(std::make_pair(datum, seznam));
    }
    else {
        T[datum].push_back(ime);
    }
}



void urejenIzpis() {
    for (auto line : T) {
        cout << line.first << " ";
        for (auto ime : line.second) {
            cout << ime << ", ";
        }
        cout << endl;
    }
}


void iskanjePoDatumu(int datum) {
    auto searchStart = std::chrono::steady_clock::now();
    T.find(datum);
    auto searchStop = std::chrono::steady_clock::now();

    if (T.find(datum) != T.end()) {
        for (auto ime : T[datum]) {
            cout << ime << ", ";
        }
        cout << endl << "Ćas iskanja: " <<
            std::chrono::duration_cast<std::chrono::microseconds>(searchStop-searchStart).count()
        << " mikrosekund.";
    }
    else {
        cout << "=== TA DATUM NE OBSTAJA! ===";
    }
}


int minimum() {
    min_element(T.begin(), T.end(), [](const auto &l, const auto &r) {return l.first < r.first;});
}

int maximum() {
    max_element(T.begin(), T.end(), [](const auto &l, const auto &r) {return l.first < r.first;});
}


// TODO Naslednik, predhodnik


void brisiDatum(int datum) {
    if (T.find(datum) == T.end())
        cout << "TA DATUM NE OBSTAJA!";
    else
        T.erase(T.find(datum));
}


void nalaganjeFilmov(const string& pot) {
    ifstream in(pot);

    int N;
    string ime;
    int datum;


    auto Start = std::chrono::steady_clock::now();
    in >> N;
    for (int i = 0; i < N; i++) {
        in >> datum;
        getline(in, ime, '\r');
        vnosFilma(datum, ime);
        if (i % 1000 == 0) {
            std::cout << '*' << std::flush;
            cout << endl;
        }
    }
    auto Stop = std::chrono::steady_clock::now();

    cout << "Čas pri nalaganju filmov je " <<
        std::chrono::duration_cast<std::chrono::microseconds>(Stop - Start).count()
    << " mikrosekund." << endl;

    in.close();
}


void izpisSeznama() {
    int izbira, date;
    string name, pot;


    cout << "Filmi - izbira:" << endl << endl;

    cout << "1) Vnos filma" << endl;
    cout << "2) Urejen izpis filmov" << endl;
    cout << "3) Iskanje po datumu izdaje" << endl;
    cout << "4) Poisci minumum in maksimum" << endl;
    cout << "5) Poisci predhodnika in naslednika" << endl;
    cout << "6) Brisi datum" << endl;
    cout << "\e[1m7) Nalaganje filmov iz datoteke\e[0m" << endl << endl;
    cout << "8) Konec" << endl << endl;
    cout << "Izbira:" << endl;
    cin >> izbira;

    switch(izbira) {
        case 1:
            cout << "Vnesi datum(YYYYMMDD)" << endl;
            cin >> date;
            cout << "Vnesi ime filma" << endl;
            cin.ignore();
            getline(cin, name);
            vnosFilma(date, name);
            break;
        case 2:
            urejenIzpis();
            break;
        case 3:
            cout << "Vnesi datum, ki ga zelis poiskati" << endl;
            cin >> date;
            iskanjePoDatumu(date);
            break;
        case 4:
            cout << "Minumum je: " << minimum() << endl;
            cout << "Maximum je: " << maximum() << endl;
            break;
        case 5:
            // TODO predhodnik, naslednik
        case 6:
            cout << "Vnesi datum, ki ga zelis izbrisati: " << endl;
            cin >> date;
            brisiDatum(date);
            break;
        case 7:
            cout << "Vnesi celotno pot do mape s filmi: " << endl;
            cin >> pot;
            nalaganjeFilmov(pot);
            break;
        case 8:
            running = false;
            break;
        default:
            izpisSeznama();
            break;
    }
    cout << endl << endl;
}


int main() {

    T.clear();

    while (running) {
        izpisSeznama();
    }


    return 0;
}
