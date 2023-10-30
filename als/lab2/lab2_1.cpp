#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* next;
};

struct LinkedList {
    Node* first;
};

int main() {
    LinkedList list;
    list.first = NULL;

    for (int i = 1; i <= 100; i++) {
        Node* newNode = new Node{ i, NULL };

        if (!list.first) {
            list.first = newNode;
        }
        else {
            Node* last = list.first;
            while (last->next) {
                last = last->next;
            }
            last->next = newNode;
        }
    }

    cout << "Wartosci:" << endl;
    Node* current = list.first;
    while (current) {
        cout << current->value << " ";
        current = current->next;
    }
    cout << endl;

    if (list.first == NULL) {
        cout << "Wartosc srednia: 0.0" << endl;
    }
    else {
        float sum = 0.0;
        int count = 0;
        current = list.first;
        while (current) {
            sum += current->value;
            count++;
            current = current->next;
        }
        cout << "Wartosc srednia: " << sum / count << endl;
    }

    if (list.first) {
        Node* temp = list.first;
        list.first = list.first->next;
        delete temp;
    }

    current = list.first;
    Node* previous = NULL;
    while (current) {
        if (current->value % 2 == 1) {
            if (previous) {
                previous->next = current->next;
            }
            else {
                list.first = current->next;
            }
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        else {
            previous = current;
            current = current->next;
        }
    }

    cout << "Wartosci po usunieciu nieparzystych elementow:" << endl;
    current = list.first;
    while (current) {
        cout << current->value << " ";
        current = current->next;
    }
    cout << endl;

    if (list.first == NULL) {
        cout << "Wartosc srednia: 0.0" << endl;
    }
    else {
        float sum = 0.0;
        int count = 0;
        current = list.first;
        while (current) {
            sum += current->value;
            count++;
            current = current->next;
        }
        cout << "Wartosc srednia: " << sum / count << endl;
    }

    current = list.first;
    while (current) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }

    return 0;
}
