#include <iostream>

using namespace std;

struct Node {
    int key;
    Node *dad;
    Node *leftSon;
    Node *rightSon;

};

bool running = true;

Node *iskanje(Node *root, int search) {

    if (root == nullptr || root->key == search) {
        return root;
    }
    else {
        if (search < root->key) {
            return iskanje(root->leftSon, search);
        }
        else {
            return iskanje(root->rightSon, search);
        }
    }
}


void vstavi(Node *&root, int input) {
    Node *y = nullptr;
    Node *x = root;
    bool sameKey = false;

    while (x != nullptr) {
        y = x;
        if (input < x->key)
            x = x->leftSon;
        else if (input > x->key)
            x = x->rightSon;
        else {
            cout << "NAPAKA!" << endl << endl;
            sameKey = true;
            break;
        }
    }

    if (!sameKey) {
        Node *fresh = new Node();
        fresh->key = input;
        fresh->dad = y;

        if (y == nullptr)
            root = fresh;
        else {
            if (fresh->key < y->key)
                y->leftSon = fresh;
            else
                y->rightSon = fresh;
        }
    }

}


void urejenIzpis(Node *root) {
    if (root != nullptr) {
        if (root->leftSon != nullptr)
            urejenIzpis(root->leftSon);
        cout << root->key << ", ";
        if (root->rightSon != nullptr)
            urejenIzpis(root->rightSon);
    }
    else {
        cout << "NAPAKA PRAZNO";
    }

}


void izpisPovezav(Node *root) {
    if (root == nullptr)
        cout << "NAPAKA, PRAZNO!";
    else {
        if (root->leftSon != nullptr) {
            cout << root->key << ", " << root->leftSon->key << ", ";
            izpisPovezav(root->leftSon);
        }

        if (root->rightSon != nullptr) {
            cout << root->key << ", " << root->rightSon->key << ", ";
            izpisPovezav(root->rightSon);
        }

    }

    cout << endl << endl;
}



int minimum(Node *root) {
    while (root->leftSon != nullptr) {
        root = root->leftSon;
    }

    return root->key;
}


int maximum(Node *root) {
    while (root->rightSon != nullptr) {
        root = root->rightSon;
    }

    return root->key;
}


int naslednik(Node *root, int key) {
    Node *tmp = iskanje(root, key);

    if (tmp->rightSon != nullptr)
        return minimum(tmp->rightSon);

    Node *secTmp = tmp->dad;
    while (secTmp != nullptr && tmp == secTmp->rightSon) {
        tmp = secTmp;
        secTmp = secTmp->dad;
    }

    return secTmp->key;
}

int predhodnik(Node *root, int key) {
    Node *tmp = iskanje(root, key);

    if (tmp->leftSon != nullptr)
        return maximum(tmp->leftSon);

    Node *secTmp = tmp->dad;
    while (secTmp != nullptr && tmp == secTmp->leftSon) {
        tmp = secTmp;
        secTmp = secTmp->dad;
    }

    return secTmp->key;
}


void brisiDrugi(Node *&root, Node *deleteMe) {
    Node *tmp;

    if (deleteMe->leftSon != nullptr)
        tmp = deleteMe->leftSon;
    else
        tmp = deleteMe->rightSon;

    if (tmp != nullptr)
        tmp->dad = deleteMe->dad;

    if (deleteMe->dad == nullptr)
        root = tmp;
    else {
        if (deleteMe == deleteMe->dad->leftSon)
            deleteMe->dad->leftSon = tmp;
        else
            deleteMe->dad->rightSon = tmp;
    }

    delete deleteMe;
}


void brisi(Node *&root, int key) {
    Node *deleteMe = iskanje(root, key);
    int tmp;

    if (deleteMe->leftSon == nullptr || deleteMe->rightSon == nullptr)
        brisiDrugi(root, deleteMe);
    else {
        tmp = naslednik(root, key);
        Node *parameter = iskanje(root, tmp);
        brisiDrugi(root, parameter);
        deleteMe->key = tmp;
    }
}


Node *root = nullptr;
void izpisMenija() {
    int chosen;
    int value;


    // Meni
    cout << "Binarno iskalno drevo - izbira:" << endl << endl;

    cout << "1) Vnos podatka" << endl;
    cout << "2) Urejen izpis vrednosti" << endl;
    cout << "3) Izpis povezav" << endl;
    cout << "4) Iskanje" << endl;
    cout << "5) Poišči minimum in maksimum" << endl;
    cout << "6) Poišči predhodnika in naslednika" << endl;
    cout << "7) Briši vrednost" << endl;
    cout << "8) Konec"<< endl << endl;

    cout << "Izbira: " << endl;
    cin >> chosen;

    switch (chosen) {
        case 1 :
            cout << "Vnesi število: " << endl;
            cin >> value;
            vstavi(root, value);
            break;
        case 2 :
            urejenIzpis(root);
            cout << endl << endl;
            break;
        case 3 :
            izpisPovezav(root);
            break;
        case 4 :
            cout << "Iskana vrednost: " << endl;
            cin >> value;
            iskanje(root, value);
            break;
        case 5 :
            cout << "Minimum je: " << minimum(root) << endl;
            cout << "Maximum je: " << maximum(root) << endl << endl;
            break;
        case 6 :
            cout << "Poišči predhodnika in naslednika števila: " << endl;
            cin >> value;
            cout << "Predhodnik: " << predhodnik(root, value) << endl;
            cout << "Naslednik: " << naslednik(root, value) << endl << endl;
            break;
        case 7 :
            cout << "Vrednost, ki jo želiš izbrisati: " << endl;
            cin >> value;
            brisi(root, value);
            break;
        case 8 :
            running = false;
            break;
        default:
            izpisMenija();
            break;

    }


}

int main() {

    while (running) {
        izpisMenija();
    }


    return 0;
}
