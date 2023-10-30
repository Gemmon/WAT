#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* next;
};

class LinkedList {
private:
    Node* first;

public:
    LinkedList() : first(NULL) {}

    void display() {
        Node* current = first;
        while (current) {
            cout << current->value << " ";
            current = current->next;
        }
        cout << endl;
    }

    float average() {
        if (!first) {
            return 0.0;
        }

        float sum = 0.0;
        int count = 0;
        Node* current = first;

        while (current) {
            sum += current->value;
            count++;
            current = current->next;
        }

        return sum / count;
    }

    void append(int value) {
        Node* newNode = new Node{value, NULL};

        if (!first) {
            first = newNode;
        } else {
            Node* last = first;
            while (last->next) {
                last = last->next;
            }
            last->next = newNode;
        }
    }

    void removeFront() {
        if (first) {
            Node* temp = first;
            first = first->next;
            delete temp;
        }
    }

    void remove(int value) {
        Node* current = first;
        Node* previous = NULL;

        while (current) {
            if (current->value == value) {
                if (previous) {
                    previous->next = current->next;
                } else {
                    first = current->next;
                }

                delete current;
                return;
            }

            previous = current;
            current = current->next;
        }
    }

    ~LinkedList() {
        while (first) {
            Node* temp = first;
            first = first->next;
            delete temp;
        }
    }
};

int main() {
    LinkedList list;

    for (int i = 1; i <= 100; i++) {
        list.append(i);
    }

    cout << "Wartosci:" << endl;
    list.display();
    cout << "Wartosc srednia: " << list.average() << endl;

    list.removeFront();

    for (int i = 1; i <= 100; i++) {
        if (i % 2 == 1) {
            list.remove(i);
        }
    }

    cout << "Wartosci po usunieciu nieparzystych elementow:" << endl;
    list.display();
    cout << "Wartosc srednia: " << list.average() << endl;

    return 0;
}
