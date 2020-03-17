#include <iostream>

using namespace std;


struct node {
    int key;
    node *prev, *next;
};

node *head = nullptr;
node *tail = nullptr;
bool running = true;


node *iskanjePodatka(int key) {
    node *current = head;

    while (current != nullptr && current->key != key) {
        current = current->next;
    }

    if (current->key != key) {
        cout << "Ni iskanega podatka!" << endl << endl;
    }
    else {
        return current;
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
    while (currNode->key != key && currNode != nullptr) {
        currNode = currNode->next;
    }

    if (currNode->key != key) {
        cout << "Vnešena vrednost ne obstaja!" << endl << endl;
    }
    else {
        newNode->next = currNode->next;
        newNode->prev = currNode;
        currNode->next = newNode;

        if (newNode->next != nullptr) {
            newNode->next->prev = newNode;
        }
        else {
            node *tail = newNode;
        }
    }
}

void vnosZaRepom(int key) {
    node *newNode = new node();
    newNode->key = key;
    newNode->next = nullptr;

    if (tail != nullptr) {
        tail->next = newNode;
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

    if (deleted->key != key) {
        cout << "Podatek ne obstaja!" << endl << endl;
    }
    else {
        if (deleted->prev == nullptr && deleted->next == nullptr) {
            head = nullptr;
            tail = nullptr;
        }

        if (deleted->prev != nullptr) {
            deleted->prev->next = deleted->next;

            if (deleted->next != nullptr) {
                deleted->next->prev = deleted->prev;
            }
        }
        else {
            head = deleted->next;
            head->prev = nullptr;
        }

        if (deleted->next != nullptr) {
            deleted->next->prev = deleted->prev;

            if (deleted->prev != nullptr) {
                deleted->prev->next = deleted->next;
            }
        }

        else {
            tail = deleted->prev;
            tail->next = nullptr;
        }

    }


    delete deleted;
}


void izpisGlavaRep() {
    node *tmp = head;

    while (tmp != nullptr) {
        cout << tmp->key << ", ";
        tmp = tmp->next;
    }
    cout << endl << endl;

    delete tmp;
}


void izpisRepGlava() {
    node *tmp = tail;

    while (tmp != nullptr) {
        cout << tmp->key << ", ";
        tmp = tmp->prev;
    }
    cout << endl << endl;

    delete tmp;
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
            //hitrostTest();
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