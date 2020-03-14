#include <iostream>

using namespace std;




struct node {
    int key;
    node *prev, *next;
};

node *head = nullptr;
node *tail = nullptr;
bool running = true;


node *iskanjePodatka(node *head, int key) {
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

void vnosGlava(node *newInput, node *head) {
    head->prev = newInput;
    newInput->next = head;
    head = newInput;
    newInput->prev = nullptr;
}


void vnosZaElt(node *currNode, node *newNode) {
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

void vnosZaRepom(node *newNode) {

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

    switch (izbira) {
        case 1 :
            //iskanjePodatka();
            break;
        case 2 :
            //vnosGlava();
            break;
        case 3 :
            //vnosZaElt();
            break;
        case 4 :
            //vnosZaRepom();
            break;
        case 5 :
            //brisanjePodatka();
            break;
        case 6 :
            //izpisGlavaRep();
            break;
        case 7 :
            //izpisRepGlava();
            break;
        case 8 :
            //hitrostTest();
            break;
        case 9 :
            running = false;
            break;
    }
}

int main() {


    while(running) {
        izpisMenija();
    }


    return 0;
}