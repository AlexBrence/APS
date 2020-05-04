#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;


struct Povezava {
    int p;
    int q;
    int cena;
};
bool running = true;
vector<Povezava*> povezave;

int partition(const int &dno, const int &vrh) {
    int pe = povezave[0]->cena;
    int l = dno;
    int d = vrh;

    while (l < d) {
        while (povezave[l]->cena <= pe && l < vrh)
            l++;
        while (povezave[d]->cena > pe && d > dno)
            d--;
        if (l < d)
            swap(povezave[l], povezave[d]);
    }
    swap(povezave[dno], povezave[d]);
    return d;
}

void quickSort(const int &dno, const int &vrh) {
    if (dno < vrh) {
        int j = partition(dno, vrh);
        quickSort(dno, j-1);
        quickSort(j+1, vrh);
    }
}


void beri() {
    if (!povezave.empty())
        povezave.clear();

    ifstream file("/home/alex/Documents/APS/vaja9/graf.txt");
    int stVozlisc, stPovezav;

    file >> stVozlisc;
    file >>stPovezav;

    for (int i = 0; i < stPovezav; i++) {
        Povezava *tmp = new Povezava();
        file >> tmp->p >> tmp->q >> tmp->cena;
        povezave.emplace_back(tmp);         // &*tmp
    }
}

void generiraj(const int &steviloVozlisc) {
    if (!povezave.empty())
        povezave.clear();

    std::mt19937 generator;
    std::uniform_int_distribution<int> vozlisceRandom(1, steviloVozlisc);
    std::uniform_int_distribution<int> povezaveRandom(1, steviloVozlisc + 20);

    // Zgeneriraj povezaveRandom
    for (int i = 0; i < steviloVozlisc + (steviloVozlisc/20); i++) {
        Povezava *tmp = new Povezava();

        tmp->p = vozlisceRandom(generator);
        tmp->q = vozlisceRandom(generator);
        tmp->cena = povezaveRandom(generator);

        if (tmp->p == tmp->q) {
            i = i - 1;
            continue;
        }

        povezave.emplace_back(tmp);
    }

    quickSort(0, povezave.size() - 1);
}


void izpisMenija() {
    cout << "Kruskalov algoritem - izbira" << endl << endl;
    cout << "1) Preberi graf iz datoteke" << endl;
    cout << "2) Generiraj naključni graf" << endl;
    cout << "3) Poženi" << endl;
    cout << "4) Izpis sprejetih povezav" << endl;
    cout << "5) Konec" << endl << endl;
    cout << "Izbira: " << endl;

    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            beri();
            break;
        case 2:
            int stVozlisc;
            cout << "Vnesi število vozlišč (max 1500)" << endl;
            cin >> stVozlisc;
            if (stVozlisc < 3 || stVozlisc > 1500) {
                cout << "Napaka";
            } else {
                generiraj(stVozlisc);
            }
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            running = false;
            break;
        default:
            cout << "Napačen vnos.";
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
