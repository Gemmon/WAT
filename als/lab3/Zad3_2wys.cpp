//============================================================================
// Zadanie 3_2  jezyk C++
//  Sito Atkina-Bernsteina
//  WCY22IY1S1  Chrapowicz Krzysztof
//============================================================================
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Node {
    int value;
    Node* next;
};

void atkinBernstein(int n) {
    vector<bool> pierwsza(n + 1, false);

    int g = (unsigned int)(sqrt(n));

    for (int x = 1; x <= g; x++) {
        for (int y = 1; y <= g; y++) {
            int xx = x * x;
            int yy = y * y;
            int n1 = 4 * xx + yy;
            int n2 = 3 * xx + yy;
            int n3 = 3 * xx + 4 * yy;

            if (n1 <= n && (n1 % 12 == 1 || n1 % 12 == 5)) {
                pierwsza[n1] = !pierwsza[n1];
            }

            if (n2 <= n && n2 % 12 == 7) {
                pierwsza[n2] = !pierwsza[n2];
            }

            if (x > y) {
                int n4 = xx + 4 * yy;
                if (n4 <= n && n4 % 12 == 11) {
                    pierwsza[n4] = !pierwsza[n4];
                }
            }
        }
    }

    Node* head = NULL;
    Node* tail = NULL;

    for (int i = 2; i <= n; i++) {
        if (pierwsza[i]) {
            Node* new_node = new Node();
            new_node->value = i;
            new_node->next = NULL;

            if (head == NULL) {
                head = new_node;
                tail = new_node;
            } else {
                tail->next = new_node;
                tail = new_node;
            }
        }
    }

    Node* current = head;
    while (current != NULL) {
        cout << current->value << " ";
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Podaj n: ";
    cin >> n;
    cout << "Liczby pierwsze: 2 3 ";
    atkinBernstein(n);

    return 0;
}