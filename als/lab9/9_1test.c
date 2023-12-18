#include <stdio.h>
#include <stdlib.h>

// Struktura węzła listy
struct Node {
    int data;
    struct Node* next;
};

// Funkcja do dodawania nowego węzła na końcu listy
void append(struct Node** head, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* last = *head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = newNode;
    }
}

// Funkcja do drukowania listy
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;

        // Dodaj nową linię po każdych 10 liczbach
        if (head != NULL && head->data % 10 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

// Funkcja do sortowania listy algorytmem Shella
void shellSort(struct Node** head) {
    // Konwertuj listę na tablicę
    int n = 0;
    struct Node* current = *head;
    while (current != NULL) {
        n++;
        current = current->next;
    }

    int* arr = (int*)malloc(n * sizeof(int));
    current = *head;
    for (int i = 0; i < n; i++) {
        arr[i] = current->data;
        current = current->next;
    }

    // Zastosuj algorytm Shella na tablicy
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;

            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }

            arr[j] = temp;
        }
    }

    // Zaktualizuj wartości węzłów listy na podstawie posortowanej tablicy
    current = *head;
    for (int i = 0; i < n; i++) {
        current->data = arr[i];
        current = current->next;
    }

    free(arr);
}

// Funkcja do zwalniania pamięci związanej z listą
void freeList(struct Node** head) {
    struct Node* current = *head;
    struct Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

int main() {
    struct Node* head = NULL;

    // Wczytaj dane z pliku do listy
    FILE* file = fopen("we.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int value;
    while (fscanf(file, "%d", &value) != EOF) {
        append(&head, value);
    }

    fclose(file);

    printf("Unsorted list:\n");
    printList(head);

    // Sortuj listę
    shellSort(&head);

    printf("Sorted list:\n");
    printList(head);

    // Zapisz wyniki do pliku
    file = fopen("out.txt", "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    struct Node* current = head;
    current = head;
    while (current != NULL) {
        fprintf(file, "%d ", current->data);

        // Dodaj nową linię po każdych 10 liczbach
        if (current->data % 10 == 0) {
            fprintf(file, "\n");
        }

        current = current->next;
    }

    fclose(file);

    // Zwolnij pamięć związana z listą
    freeList(&head);

    printf("Results saved to out.txt\n");

    return 0;
}
