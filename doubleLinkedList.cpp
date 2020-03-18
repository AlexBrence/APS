#include <iostream>
#include <list>
#include <chrono>
#include <fstream>

using namespace std;


struct node {
    int key;
    node *prev, *next;
};

node *head = nullptr;
node *tail = nullptr;
bool running = true;


void iskanjePodatka(int key) {
    node *current = head;

    while (current != nullptr && current->key != key) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Ni iskanega podatka!" << endl << endl;
    }
    else {
        cout << "Število " << key << " je v seznamu." << endl << endl;
    }
}

void vnosGlava(int key) {
    node *newInput = new node();
    newInput->key = key;
    newInput->next = head;
    newInput->prev = nullptr;

    if (head != nullptr) {
        head->prev = newInput;
    }
    else {
        tail = newInput;
    }
    head = newInput;
}


void vnosZaElt(int key, int inputKey) {
    node *newNode = new node();
    newNode->key = inputKey;

    node* currNode = head;
    while (currNode != nullptr && currNode->key != key) {
        currNode = currNode->next;
    }
    if (currNode == nullptr) {
        cout << "Podatek ne obstaja!" << endl << endl;
    }
    else {
        newNode->prev = currNode;
        newNode->next = currNode->next;
        currNode->next = newNode;


        if (newNode->next != nullptr) {
            newNode->next->prev = newNode;
        }
        else {
            tail = newNode;
        }
    }
}

void vnosZaRepom(int key) {
    node *newNode = new node();
    newNode->key = key;
    newNode->next = nullptr;

    if (tail != nullptr) {
        tail->next = newNode;
        newNode->prev = tail;
    }
    else {
        head = newNode;
    }
    tail = newNode;
}

void brisanjePodatka(int key) {
    node *deleted = head;

    while (deleted->key != key && deleted != nullptr) {
        deleted = deleted->next;
    }

    if (deleted == nullptr || (head == nullptr && tail == nullptr)) {
        cout << "Podatek ne obstaja!" << endl << endl;
    }
    else if (deleted->prev == nullptr && deleted->next == nullptr) {
            head = nullptr;
            tail = nullptr;
    }
    else {
        if (deleted->prev != nullptr) {
            deleted->prev->next = deleted->next;

            if (deleted->next != nullptr) {
                deleted->next->prev = deleted->prev;
            }
        } else {
            head = deleted->next;
            head->prev = nullptr;
        }

        if (deleted->next != nullptr) {
            deleted->next->prev = deleted->prev;

            if (deleted->prev != nullptr) {
                deleted->prev->next = deleted->next;
            }
        } else {
            tail = deleted->prev;
            tail->next = nullptr;
        }
    }

    delete deleted;
}


void izpisGlavaRep() {

    if (head == nullptr && tail == nullptr) {
        cout << "Seznam je prazen!" << endl << endl;
    }
    else {
        node *tmp = head;

        while (tmp != nullptr) {
            cout << tmp->key << ", ";
            tmp = tmp->next;
        }
        cout << endl << endl;

        delete tmp;
    }
}


void izpisRepGlava() {
    if (head == nullptr && tail == nullptr) {
        cout << "Seznam je prazen!" << endl << endl;
    }
    else {
        node *tmp = tail;

        while (tmp != nullptr) {
            cout << tmp->key << ", ";
            tmp = tmp->prev;
        }
        cout << endl << endl;

        delete tmp;
    }
}


void hitrostTest(int N) {
    long long sum = 0;
    int *array = new int[N];
    int *norArray = new int[N];
    ofstream datoteka;
    datoteka.open("hitrostRezultati.txt");

    // EMPTY THE LIST
    node *tmp = head;
    while (tmp != nullptr) {
        brisanjePodatka(tmp->key);
        tmp = tmp->next;
    }

    // FILL LIST
    auto startList = std::chrono::steady_clock::now();
    list<int> speedyGonzales;
    for (int i = 1; i <= N; i++) {
        speedyGonzales.push_front(i);
    }
    auto endList = std::chrono::steady_clock::now();

    cout << "ČAS PRI POLNJENJU SEZNAMA(mikrosek): " <<
        std::chrono::duration_cast<std::chrono::microseconds>(endList-startList).count()
    << endl;

    // SUM OF ALL ELEMENTS IN LIST
    auto sumListStart = std::chrono::steady_clock::now();
    for (int i : speedyGonzales) {
        sum += i;
    }
    auto sumListEnd = std::chrono::steady_clock::now();

    cout << "VSOTA SEZNAMA: " << sum << endl;
    cout << "ČAS PRI SEŠTEVANJU PODATKOV SEZNAMA(mikrosek): " <<
        std::chrono::duration_cast<std::chrono::microseconds>(sumListEnd-sumListStart).count()
    << endl << endl;

    datoteka << "->Čas pri polnjenju seznama(mikrosek): " <<
        std::chrono::duration_cast<std::chrono::microseconds>(endList-startList).count()
    << endl;
    datoteka << "Čas pri seštevanju elt seznama: " <<
        std::chrono::duration_cast<std::chrono::microseconds>(sumListEnd-sumListStart).count()
    << endl;


    // ARRAY FIRST SPOT INPUT
    auto arrayFirstStart = std::chrono::steady_clock::now();
    for (int i = 0; i < N; i++) {
        if (i == N-1) {
            array[0] = i+1;
        }
        else {
            array[0] = i + 1;
            for (int j = i; j >= 0; j--) {
                array[j+1] = array[j];
            }
        }
    }
    auto arrayFirstEnd = std::chrono::steady_clock::now();

    cout << "ČAS PRI POLNJENJU POLJA NA 1. MESTO(mikrosek): " <<
        std::chrono::duration_cast<std::chrono::microseconds>(arrayFirstEnd-arrayFirstStart).count()
    << endl;

    // SUM OF ALL ELEMENTS IN FIRST-SPOT-ARRAY
    sum = 0;
    auto sumArrayFirstStart = std::chrono::steady_clock::now();
    for (int i = 0; i < N; i++) {
        sum += array[i];
    }
    auto sumArrayFirstEnd = std::chrono::steady_clock::now();

    cout << "VSOTA FIRST-SPOT-POLJA JE: " << sum << endl;
    cout << "ČAS PRI SEŠTEVANJU PODATKOV POLJA(mikrosek): " <<
        std::chrono::duration_cast<std::chrono::microseconds>(sumArrayFirstEnd-sumArrayFirstStart).count()
    << endl << endl;

    datoteka << "->Čas pri polnjenju first-spot-arraya(mikrosek): " <<
        std::chrono::duration_cast<std::chrono::microseconds>(arrayFirstEnd-arrayFirstStart).count()
      << endl;
    datoteka << "Čas pri seštevanju elt: " <<
        std::chrono::duration_cast<std::chrono::microseconds>(sumArrayFirstEnd-sumArrayFirstStart).count()
    << endl;


    // NORMAL ARRAY FILL
    auto arrayStart = std::chrono::steady_clock::now();
    for (int i = 0; i < N; i++) {
        norArray[i] = i+1;
    }
    auto arrayEnd = std::chrono::steady_clock::now();

    cout << "ČAS PRI POLNJENJU NAVADNEGA POLJA(mikrosek): " <<
        std::chrono::duration_cast<std::chrono::microseconds>(arrayEnd-arrayStart).count()
    << endl;

    // SUM OF ELEMENTS IN NORMAL ARRAY
    sum = 0;
    auto sumArrayStart = std::chrono::steady_clock::now();
    for (int i = 0; i < N; i++) {
        sum += norArray[i];
    }
    auto sumArrayEnd = std::chrono::steady_clock::now();

    cout << "VSOTA PRI SEŠTEVANJU NAVADNEGA POLJA JE: " << sum << endl;
    cout << "ČAS PRI SEŠTEVANJU PODATKOV NAVADNEGA POLJA(mikrosek): " <<
        std::chrono::duration_cast<std::chrono::microseconds>(sumArrayEnd-sumArrayStart).count()
    << endl << endl;

    datoteka << "->Čas pri polnjenju navadnega arraya(mikrosek): " <<
        std::chrono::duration_cast<std::chrono::microseconds>(arrayEnd-arrayStart).count()
    << endl;
    datoteka << "Čas pri seštevanju elt: " <<
        std::chrono::duration_cast<std::chrono::microseconds>(sumArrayEnd-sumArrayStart).count()
    << endl;

    datoteka.close();
}



void izpisMenija() {
    int izbira;

    cout << "Dvojno povezan seznam - izbira:" << endl << endl;
    cout << "1) Iskanje podatka" << endl;
    cout << "2) Vnos podatka v glavo" << endl;
    cout << "3) Vnos podatka za elementom" << endl;
    cout << "4) Vnos podatka za repom" << endl;
    cout << "5) Brisanje podatka" << endl;
    cout << "6) Izpis seznama od glave proti repu" << endl;
    cout << "7) Izpis seznama od repa proti glavi" << endl;
    cout << "8) Testiraj hitrost" << endl;
    cout << "9) Konec" << endl << endl;

    cout << "Izbira: " << endl;
    cin >> izbira;

    int value;

    switch (izbira) {
        case 1 :
            int keySearch;
            cout << "Kateri podatek želiš poiskati?\n";
            cin >> keySearch;
            iskanjePodatka(keySearch);
            break;
        case 2 :
            cout << "Vnesi vrednost: " << endl;
            cin >> value;
            vnosGlava(value);
            break;
        case 3 :
            int key, newKey;
            cout << "Vnesi podatek, za katerega boš vnesel nov podatek: ";
            cin >> key;
            cout << "\nVnesi nov podatek: ";
            cin >> newKey;
            vnosZaElt(key, newKey);
            break;
        case 4 :
            cout << "Vnesi vrednost: " << endl;
            cin >> value;
            vnosZaRepom(value);
            break;
        case 5 :
            cout << "Vnesi podatek, ki ga želiš izbrisati: ";
            cin >> value;
            brisanjePodatka(value);
            break;
        case 6 :
            izpisGlavaRep();
            break;
        case 7 :
            izpisRepGlava();
            break;
        case 8 :
            cout << "Vnesi količino podatkov: ";
            cin >> value;
            hitrostTest(value);
            break;
        case 9 :
            running = false;
            break;
        default :
            cout << "NAPAČEN VNOS!" << endl << endl;
            break;
    }
}



int main() {


    while(running) {
        izpisMenija();
    }


    return 0;
}