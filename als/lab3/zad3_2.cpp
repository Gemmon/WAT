//============================================================================
// Zadanie 3_2  jezyk C++
//  Sito Atkina-Bernsteina
//  WCY22IY1S1  Chrapowicz Krzysztof
//============================================================================
#include <iostream>
#include <cmath>

using namespace std;

struct Node {
    int value;
    Node* next;
};

Node* append(Node* tail, int value) {
    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = NULL;
    
    if (tail != NULL) {
        tail->next = newNode;
    }
    
    return newNode;
}

void freeList(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void atkinBernstein(int n) {
    Node* primeList = NULL;
    Node* tail = NULL;

    bool* isPrime = new bool[n + 1];
    for (int i = 0; i <= n; i++) {
        isPrime[i] = false;
    }

    int sqrtN = static_cast<int>(sqrt(n));

    for (int x = 1; x <= sqrtN; x++) {
        for (int y = 1; y <= sqrtN; y++) {
            int num = 4 * x * x + y * y;
            if (num <= n && (num % 12 == 1 || num % 12 == 5))
                isPrime[num] = !isPrime[num];

            num = 3 * x * x + y * y;
            if (num <= n && num % 12 == 7)
                isPrime[num] = !isPrime[num];

            num = 3 * x * x - y * y;
            if (x > y && num <= n && num % 12 == 11)
                isPrime[num] = !isPrime[num];
        }
    }

    for (int x = 5; x <= sqrtN; x++) {
        if (isPrime[x]) {
            for (int y = x * x; y <= n; y += x * x) {
                isPrime[y] = false;
            }
        }
    }

    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            if (primeList == NULL) {
                primeList = new Node;
                primeList->value = i;
                primeList->next = NULL;
                tail = primeList;
            } else {
                tail = append(tail, i);
            }
        }
    }

    Node* current = primeList;
    while (current != NULL) {
        cout << current->value << " ";
        current = current->next;
    }

    freeList(primeList);
    delete[] isPrime;
}

int main() {
    int n;
    cout << "Podaj n: ";
    cin >> n;

    cout << "Liczby pierwsze: 2 3 ";
    atkinBernstein(n);
    cout << endl;

    return 0;
}
