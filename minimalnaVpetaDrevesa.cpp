#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;


struct Povezava {
    int p;
    int q;
    int cena;
};
bool running = true;
vector<Povezava*> povezave;
vector<Povezava*> sprejetePovezave;
int steviloVozlisc;


int partition(int dno, int vrh) {
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

void quickSort(int dno, int vrh) {
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
    int stPovezav;

    file >> steviloVozlisc;
    file >>stPovezav;

    for (int i = 0; i < stPovezav; i++) {
        Povezava *tmp = new Povezava();
        file >> tmp->p >> tmp->q >> tmp->cena;
        povezave.emplace_back(tmp);         // &*tmp
    }

    // Če ni urejeno uredi
    for (int i = 0; i < steviloVozlisc - 1; i++) {
        if (povezave[i] > povezave[i+1])
            quickSort(0, povezave.size() - 1);
    }
}

void generiraj() {
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

int poisciMax(const vector<int>& mnozice) {
    int max = 0;
    for (const auto &elt : mnozice) {
        if (elt > max)
            max = elt;
    }
    return max;
}

vector<Povezava *> kruskal() {
    auto start = std::chrono::steady_clock::now();

    if (!sprejetePovezave.empty())
        sprejetePovezave.clear();

    vector<int> mnozice(steviloVozlisc, 0);

    cout << "Število vhodnih vozlišč: " << steviloVozlisc << endl;
    cout << "Število vhodnih povezav: " << povezave.size() << endl;

    for (auto &elt : povezave) {
        // Če sta v enaki množici zavrni
        if ((mnozice[elt->p - 1] == mnozice[elt->q - 1]) && (mnozice[elt->p - 1] != 0 && mnozice[elt->q - 1] != 0))
            continue;

        // Če nista v enaki množici, ju združi pod eno množico
        else if ((mnozice[elt->p - 1] != mnozice[elt->q - 1]) && (mnozice[elt->p - 1] != 0 && mnozice[elt->q - 1] != 0)) {
            for (auto &zdruzi : mnozice) {
                if (zdruzi == mnozice[elt->q - 1])
                    zdruzi = mnozice[elt->p - 1];
            }
            sprejetePovezave.push_back(elt);
        }

        // Če eno od vozlišč še ni v množici
        else if ((mnozice[elt->p - 1] == 0 && mnozice[elt->q - 1] != 0) || (mnozice[elt->q - 1] == 0 && mnozice[elt->p - 1] != 0)) {
            mnozice[elt->p - 1] == 0 ? mnozice[elt->p - 1] = mnozice[elt->q - 1] : mnozice[elt->q - 1] = mnozice[elt->p - 1];
            sprejetePovezave.push_back(elt);
        }

        // Če še nobeno vozlišče ni v množici
        else if (mnozice[elt->p - 1] == 0 && mnozice[elt->q - 1] == 0) {
            mnozice[elt->p - 1] = poisciMax(mnozice) + 1;
            mnozice[elt->q - 1] = mnozice[elt->p - 1];
            sprejetePovezave.push_back(elt);
        }

        if (sprejetePovezave.size() == (steviloVozlisc - 1)) {
            cout << "Število sprejetih povezav je: " << sprejetePovezave.size() << endl;

            auto stop = std::chrono::steady_clock::now();
            cout << "Čas trajanja algoritma je: " <<
                std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count()
            << " mikrosekund";
            return sprejetePovezave;
        }
    }

    cout << "Ni rešitve.";

    auto stop = std::chrono::steady_clock::now();
    cout << "Čas trajanja algoritma je: " <<
         std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count()
     << " mikrosekund";
}


void izpisPovezav() {
    if (sprejetePovezave.empty()) {
        cout << "Ni sprejetih povezav!";
        return;
    }

    cout << steviloVozlisc << endl;
    cout << sprejetePovezave.size() << endl;

    for (const auto &elt : sprejetePovezave) {
        cout << elt->p << " " << elt->q << " " << elt->cena << endl;
    }
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
            cout << "Vnesi število vozlišč (max 1500)" << endl;
            cin >> steviloVozlisc;
            if (steviloVozlisc < 3 || steviloVozlisc > 1500) {
                cout << "Napaka";
            } else {
                generiraj();
            }
            break;
        case 3:
            kruskal();
            break;
        case 4:
            izpisPovezav();
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
