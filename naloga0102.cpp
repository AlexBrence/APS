#include <iostream>
#include <stack>
#include <iomanip>

using namespace std;

struct Stolp {
    stack<int> stolp;
} s1, s2, s3;


// Če gre večje na manjšo
bool isBigger(int prvi, int drugi) {
    return prvi > drugi;
}

// Premakni iz stolpca v stolpec
void change(int from, int to) {
    switch (from) {
        case 1 :
            switch (to) {
                case 2 :
                    if (s2.stolp.size() == 0) {
                        s2.stolp.push(s1.stolp.top());
                        s1.stolp.pop();
                        break;
                    }
                    else if (isBigger(s1.stolp.top(), s2.stolp.top())) {
                        cout << "NE SME VEČJI NA MANJŠEGA" << endl << endl;
                        break;
                    }
                    else {
                        s2.stolp.push(s1.stolp.top());
                        s1.stolp.pop();
                        break;
                    }
                case 3 :
                    if (s3.stolp.size() == 0) {
                        s3.stolp.push(s1.stolp.top());
                        s1.stolp.pop();
                        break;
                    }
                    else if (isBigger(s1.stolp.top(), s3.stolp.top())) {
                        cout << "NE SME VEČJI NA MANJŠEGA" << endl << endl;
                    }
                    else {
                        s3.stolp.push(s1.stolp.top());
                        s1.stolp.pop();
                        break;
                    }
                default:
                    cout << "NAPAČEN VNOS" << endl << endl;
                    break;
            }
            break;

        case 2 :
            switch (to) {
                case 1 :
                    if (s1.stolp.size() == 0) {
                        s1.stolp.push(s2.stolp.top());
                        s2.stolp.pop();
                        break;
                    }
                    else if (isBigger(s2.stolp.top(), s1.stolp.top())) {
                        cout << "NE SME VEČJI NA MANJŠEGA" << endl << endl;
                        break;
                    }
                    else {
                        s1.stolp.push(s2.stolp.top());
                        s2.stolp.pop();
                        break;
                    }
                case 3 :
                    if (s3.stolp.size() == 0) {
                        s3.stolp.push(s2.stolp.top());
                        s2.stolp.pop();
                        break;
                    }
                    else if (isBigger(s2.stolp.top(), s3.stolp.top())) {
                        cout << "NE SME VEČJI NA MANJŠEGA" << endl << endl;
                        break;
                    }
                    else {
                        s3.stolp.push(s2.stolp.top());
                        s2.stolp.pop();
                        break;
                    }
                default:
                    cout << "NAPAČEN VNOS" << endl << endl;
                    break;
            }
            break;

        case 3 :
            switch (to) {
                case 1 :
                    if (s1.stolp.size() == 0) {
                        s1.stolp.push(s3.stolp.top());
                        s3.stolp.pop();
                    }
                    else if (isBigger(s3.stolp.top(), s1.stolp.top())) {
                        cout << "NE SME VEČJI NA MANJŠEGA" << endl << endl;
                        break;
                    }
                    else {
                        s1.stolp.push(s3.stolp.top());
                        s3.stolp.pop();
                        break;
                    }
                case 2 :
                    if (s2.stolp.size() == 0) {
                        s2.stolp.push(s3.stolp.top());
                        s3.stolp.pop();
                    }
                    else if (isBigger(s3.stolp.top(), s2.stolp.top())) {
                        cout << "NE SME VEČJI NA MANJŠEGA" << endl << endl;
                        break;
                    }
                    else {
                        s2.stolp.push(s3.stolp.top());
                        s3.stolp.pop();
                        break;
                    }
                default:
                    cout << "NAPAČEN VNOS" << endl << endl;
                    break;
            }
            break;
    }
}


void izpisiStolp() {
    cout << "STOLP 1: ";
    for (stack<int> dump = s1.stolp; !dump.empty(); dump.pop()) {
        cout << dump.top() << " ";
    }
    cout << endl;

    cout << "STOLP 2: ";
    for (stack<int> dump = s2.stolp; !dump.empty(); dump.pop()) {
        cout << dump.top() << " ";
    }
    cout << endl;

    cout << "STOLP 3: ";
    for (stack<int> dump = s3.stolp; !dump.empty(); dump.pop()) {
        cout << dump.top() << " ";
    }
    cout << endl;
}



int main() {
    int inputNum;
    int from;
    int to;

    cout << "Največje število ploščice naj bo (med 2 in 10): " << endl;
    cin >> inputNum;
    while (inputNum > 10 || inputNum < 2) {
        cout << "Napačen vnos. Vnesi ponovno: " << endl;
        cin >> inputNum;
    }

    for (int i = inputNum; i > 0; i--) {
        s1.stolp.push(i);
    }

    while (s3.stolp.size() != inputNum) {
    //    cout << "Stolp 1" << setw(20) << "Stolp 2" << setw(20) << "Stolp 3" << setw(20) << "\n\n\n\n";

        izpisiStolp();

        cout << endl << "PREMAKNI IZ: " << endl;
        cin >> from;
        cout << "PREMAKNI V: " << endl;
        cin >> to;
        change(from, to);
    }

    cout << "ČESTITAM!" << endl;
    izpisiStolp();

    return 0;
}
