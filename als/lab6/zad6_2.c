#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 100

struct MaxHeap {
    int size;
    int array[MAX_HEAP_SIZE];
};

void insert(struct MaxHeap* heap, int value) {
    if (heap->size == MAX_HEAP_SIZE) {
        printf("Kopiec jest pełny. Nie można dodać więcej elementów.\n");
        return;
    }

    // Dodaj element na koniec kopca
    heap->array[heap->size] = value;
    int current = heap->size;
    heap->size++;

    // Napraw kopiec w górę
    while (current > 0 && heap->array[current] > heap->array[(current - 1) / 2]) {
        // Zamień obecny element z rodzicem, jeśli jest większy
        int temp = heap->array[current];
        heap->array[current] = heap->array[(current - 1) / 2];
        heap->array[(current - 1) / 2] = temp;

        // Idź w górę kopca
        current = (current - 1) / 2;
    }

    printf("Element %d zostal dodany do kopca.\n", value);
}

void deleteMax(struct MaxHeap* heap) {
    if (heap->size == 0) {
        printf("Kopiec jest pusty.\n");
        return;
    }

    // Zamień korzeń z ostatnim elementem
    int maxValue = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;

    // Napraw kopiec w dół
    int current = 0;
    while (1) {
        int leftChild = 2 * current + 1;
        int rightChild = 2 * current + 2;
        int largest = current;

        if (leftChild < heap->size && heap->array[leftChild] > heap->array[largest])
            largest = leftChild;

        if (rightChild < heap->size && heap->array[rightChild] > heap->array[largest])
            largest = rightChild;

        if (largest != current) {
            // Zamień obecny element z większym dzieckiem
            int temp = heap->array[current];
            heap->array[current] = heap->array[largest];
            heap->array[largest] = temp;

            // Idź w dół kopca
            current = largest;
        } else {
            break;
        }
    }

    printf("Maksymalny element %d zostal usuniety.\n", maxValue);
}

void deleteHeap(struct MaxHeap* heap) {
    heap->size = 0;
}

void printHeap(struct MaxHeap* heap) {
    if (heap->size == 0) {
        printf("Kopiec jest pusty.\n");
        return;
    }

    printf("Kopiec: ");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->array[i]);
    }
    printf("\n");
}


void printLevelOrder(struct MaxHeap* heap) {
    if (heap->size == 0) {
        printf("Kopiec jest pusty.\n");
        return;
    }

    printf("Kopiec poziomami:\n");

    int levelSize = 1;
    int count = 0;

    for (int i = 0; i < heap->size; i++) {
        printf("%d", heap->array[i]);

        if (i < heap->size - 1) {
            printf(",");
        }

        count++;

        if (count == levelSize) {
            printf("\n");
            levelSize *= 2;
            count = 0;
        } else {
            printf("\t");
        }
    }

    printf("\n");
}

void inorderTraversal(struct MaxHeap* heap, int index) {
    if (index < heap->size) {
        inorderTraversal(heap, 2 * index + 1);
        printf("%d ", heap->array[index]);
        inorderTraversal(heap, 2 * index + 2);
    }
}

int main() {
    struct MaxHeap heap;
    heap.size = 0;

    int choice, value;

    do {
        printf("\n1. Dodaj element\n");
        printf("2. Usun maksymalny element\n");
        printf("3. Usun caly kopiec\n");  
        printf("4. Wyswietl kopiec poziomami\n");
        printf("5. Przeglad wezlow (LVR)\n");
        printf("0. Zakoncz\n");

        printf("Wybierz opcje: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Podaj wartosc do dodania: ");
                scanf("%d", &value);
                insert(&heap, value);
                break;
            case 2:
                deleteMax(&heap);
                break;
            case 3:
                deleteHeap(&heap);
                printf("Kopiec zostal usuniety.\n");
                break;

            case 4:
                printLevelOrder(&heap);
                break;
            case 5:
                printf("Przeglad wezlow (LVR): ");
                inorderTraversal(&heap, 0);
                printf("\n");
                break;
            case 0:
                break;
            default:
                printf("Blad wyboru.\n");
        }

    } while (choice != 0);

    return 0;
}

