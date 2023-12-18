#include <stdio.h>
#include <stdlib.h>

// Struktura węzła listy
struct Node {
    int data;
    struct Node* next;
};

// Funkcja do zamiany miejscami dwóch elementów
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Funkcja do podziału listy względem elementu pivot
struct Node* partition(struct Node* low, struct Node* high) {
    int pivot = high->data;
    struct Node* i = low->next;

    for (struct Node* j = low; j != high; j = j->next) {
        if (j->data < pivot) {
            swap(&(i->data), &(j->data));
            i = i->next;
        }
    }

    swap(&(i->data), &(high->data));
    return i;
}

// Funkcja do implementacji algorytmu Quick Sort dla listy
void quickSortUtil(struct Node* low, struct Node* high) {
    if (low != NULL && high != NULL && low != high && low->next != high) {
        struct Node* pivot = partition(low, high);
        quickSortUtil(low, pivot);
        quickSortUtil(pivot->next, high);
    }
}

// Funkcja do sortowania listy przy użyciu Quick Sort
void quickSort(struct Node** headRef) {
    quickSortUtil(*headRef, NULL);
}

// Funkcja do dodawania nowego węzła na początku listy
void push(struct Node** headRef, int newData) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = newData;
    newNode->next = *headRef;
    *headRef = newNode;
}

// Funkcja do wyświetlania listy
void printList(struct Node* node, FILE* outputFile) {
    while (node != NULL) {
        fprintf(outputFile, "%d ", node->data);
        node = node->next;
    }
    fprintf(outputFile, "\n");
}

// Funkcja do zwalniania pamięci zajmowanej przez listę
void freeList(struct Node* head) {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct Node* head = NULL;
    FILE* inputFile = fopen("we.txt", "r");

    // Odczyt danych z pliku we.txt
    int value;
    while (fscanf(inputFile, "%d", &value) == 1) {
        push(&head, value);
    }

    fclose(inputFile);

    printf("Lista przed sortowaniem: \n");
    printList(head, stdout);

    // Wywołanie funkcji sortującej
    quickSort(&head);

    FILE* outputFile = fopen("out.txt", "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Nie można otworzyć pliku out.txt do zapisu.\n");
        exit(EXIT_FAILURE);
    }

    printf("Lista po sortowaniu: \n");
    printList(head, outputFile);

    // Zwolnienie pamięci
    freeList(head);

    fclose(outputFile);

    return 0;
}
