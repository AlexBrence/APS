#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;

bool running = true;
int arraySize;
int *array = nullptr;

void generiraj(int *&polje, int N, int choice) {
    std::mt19937 generator;
    std::uniform_int_distribution<int> bigNum(0, 100000);
    std::uniform_int_distribution<int> smallNum(0, 10000);

    switch(choice) {
        case 1:
            for (int i = 0; i < N; i++) {
                polje[i] = bigNum(generator);
            }
            break;
        case 2:
            polje[0] = smallNum(generator);
            for (int i = 1; i < N; i++) {
                polje[i] = polje[i-1] + bigNum(generator);
            }
            break;
        case 3:
            polje[0] = bigNum(generator);
            for (int i = 1; i < N; i++) {
                polje[i] = polje[i-1] - smallNum(generator);
            }
            break;
    }
}

bool preveri(const int polje[], const int dno, const int vrh) {
    for (int i = dno; i < vrh-1; i++) {
        if (polje[i+1] < polje[i])
            return false;
    }
    return true;
}

int deli(int *&polje, int dno, int vrh) {
    int pe = polje[dno];
    int l = dno;
    int d = vrh;
    while (l < d) {
        while (polje[l] <= pe && l < vrh)
            l++;
        while (polje[d] >= pe && d > dno)
            d--;
        if (l < d) {
            swap(polje[l], polje[d]);
        }
    }
    swap(polje[dno], polje[d]);
    return d;
}


// TODO dodaj da se pokaže čas!
void hitroUredi (int *&polje, int dno, int vrh, bool mediana) {
    // Opcija z mediano
    if (preveri(polje, dno, vrh) || mediana) {
        int m = dno + (vrh - dno) / 2;
        swap(polje[dno], polje[m]);
    }
    if (dno < vrh) {
        int j = deli(polje, dno, vrh);
        hitroUredi(polje, dno, j-1, mediana);
        hitroUredi(polje, j+1, vrh, mediana);
    }
}


void timeQS(int *&polje, int dno, int vrh, bool mediana) {
    auto start = std::chrono::steady_clock::now();
    hitroUredi(polje, dno, vrh, mediana);
    auto stop = std::chrono::steady_clock::now();

    cout << "Čas pri urejanju s QS algoritmom je " <<
        std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count()
        << " mikrosekund.";
}


void bubbleSort(int *&polje, const int N) {
    for (int i = 0; i < N-1; i++) {
        for (int j = 0; j < N-i-1; j++) {
            if (polje[j] > polje[j+1])
                swap(polje[j], polje[j+1]);
        }
    }
}


void timeBubble(int *&polje, const int N) {
    auto start = std::chrono::steady_clock::now();
    bubbleSort(polje, N);
    auto stop = std::chrono::steady_clock::now();

    cout << "Čas pri urejanju z Bubble Sort algoritmom je " <<
        std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count()
    << " mikrosekund.";
}


void izpis(const int polje[], const int N) {
    for (int i = 0; i < N; i++) {
        cout << polje[i] << ", ";
    }
}



void izpisMenija() {
    int choice;

    cout << "Hitro uredi - izbira:" << endl << endl;
    cout << "1) Generiraj naključno zaporedje" << endl;
    cout << "2) Generiraj naraščajoče zaporedje" << endl;
    cout << "3) Generiraj padajoče zaporedje" << endl;
    cout << "4) Izpis zaporedja" << endl;
    cout << "5) Preveri ali je zaporedje urejeno" << endl;
    cout << "6) Uredi s hitrim urejanjem brez mediane" << endl;
    cout << "7) Uredi s hitrim urejanjem z mediano" << endl;
    cout << "8) Uredi z drugim algoritmom za urejanje" << endl << endl;
    cout << "9) Konec" << endl << endl;
    cout << "Izbira: " << endl;
    cin >> choice;


    switch (choice) {
        case 1:
            cout << "Vnesi velikost polja: " << endl;
            cin >> arraySize;
            array = new int[arraySize];
            generiraj(array, arraySize, choice);
            break;
        case 2:
            cout << "Vnesi velikost polja: " << endl;
            cin >> arraySize;
            array = new int[arraySize];
            generiraj(array, arraySize, choice);
            break;
        case 3:
            cout << "Vnesi velikost polja: " << endl;
            cin >> arraySize;
            array = new int[arraySize];
            generiraj(array, arraySize, choice);
            break;
        case 4:
            izpis(array, arraySize);
            break;
        case 5:
            if (!preveri(array, 0, arraySize))
                cout << "Zaporedje NI urejeno.";
            else
                cout << "Zaporedje JE urejeno";
            break;
        case 6:
            timeQS(array, 0, arraySize-1, false);
            break;
        case 7:
            timeQS(array, 0, arraySize-1, true);
            break;
        case 8:
            timeBubble(array, arraySize);
            break;
        case 9:
            running = false;
            break;
        default:
            cout << "Napačna izbira" << endl;
            izpisMenija();
            break;
    }
    cout << endl << endl;

}


int main() {

    while (running) {
        izpisMenija();
    }



    return 0;
}
