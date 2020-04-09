#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;


struct Element {
    int key;
    Element *prev, *next;
};

Element *head = nullptr;
Element *tail = nullptr;

bool running = true;
int arraySize;
int *array = nullptr;


void vnosRep(int key) {
    Element *novi = new Element();
    novi->key = key;
    novi->next = nullptr;

    if (tail != nullptr) {
        tail->next = novi;
        novi->prev = tail;
    }
    else
        head = novi;
    tail = novi;

}

void generiraj(int size) {
    std::mt19937 generator;
    std::uniform_int_distribution<int> smallNum(0, 10000);

    int i = 0;
    while (i != size) {
        vnosRep(smallNum(generator));
        i++;
    }

}

bool preveri() {
    Element *tmp = head;
    while (tmp->next != nullptr) {
        if (tmp->next->key < tmp->key)
            return false;
        tmp = tmp->next;
    }
    return true;
}

Element* deli(Element* dno, Element* vrh) {
    int pe = dno->key;
    Element* l = dno;
    Element* d = vrh;
    bool prekrizala = false;

    while (!prekrizala) {
        while (l->key <= pe && l != vrh) {
            l = l->next;
            if (l == d)
                prekrizala = true;
        }
        while (d->key >= pe && d != dno) {
            d = d->prev;
            if (d == l)
                prekrizala = true;
        }
        if (!prekrizala)
            swap(l->key, d->key);

    }
    swap(dno->key, d->key);
    return d;
}


// DAJ NOTRI KOPIJO OD HEAD
void hitroUredi (Element* dno, Element* vrh) {
    if (dno != vrh) {
        Element *j = deli(dno, vrh);
        if (dno != j)
            hitroUredi(dno, j->prev);
        if (vrh != j)
            hitroUredi(j->next, vrh);
    }
}


void timeQS(Element* dno, Element* vrh) {
    auto start = std::chrono::steady_clock::now();
    hitroUredi(dno, vrh);
    auto stop = std::chrono::steady_clock::now();

    cout << "Čas pri urejanju s QS algoritmom je " <<
        std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count()
        << " mikrosekund.";
}


void izpis(bool vsota) {
    if (head == nullptr && tail == nullptr)
        cout << "Seznam je prazen!";
    else {
        Element *tmp = head;
        if (vsota) {
            long long sum = 0;
            while (tmp != nullptr) {
                sum += tmp->key;
                tmp = tmp->next;
            }
            cout << "Vsota elementov je: " << sum;
        }
        else {
            while (tmp != nullptr) {
                cout << tmp->key << ", ";
                tmp = tmp->next;
            }
        }

        delete tmp;
    }
}


void izpisMenija() {
    int choice;

    cout << "Hitro uredi - izbira:" << endl << endl;
    cout << "1) Generiraj naključno zaporedje" << endl;
    cout << "2) Izpis zaporedja" << endl;
    cout << "3) Preveri urejenost zaporedja" << endl;
    cout << "4) Izpiši vsoto elementov" << endl;
    cout << "5) Uredi" << endl;
    cout << "6) Konec" << endl << endl;
    cout << "Izbira: " << endl;
    cin >> choice;


    switch (choice) {
        case 1:
            cout << "Vnesi dolžino zaporedja: " << endl;
            cin >> arraySize;
            generiraj(arraySize);
            break;
        case 2:
            izpis(false);
            break;
        case 3:
            if (!preveri())
                cout << "Zaporedje NI urejeno.";
            else
                cout << "Zaporedje JE urejeno.";
            break;
        case 4:
            izpis(true);
            break;
        case 5:
            timeQS(head, tail);
            break;
        case 6:
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
