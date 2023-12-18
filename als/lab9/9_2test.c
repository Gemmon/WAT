#include <stdio.h>
#include <stdlib.h>

// Struktura węzła listy
struct Node {
    int data;
    struct Node* next;
};

void librarySort(struct Node** head) {
    // Ustawienie wskaźników pomocniczych
    struct Node* sorted = NULL;
    struct Node* current = *head;

    // Przechodzenie przez oryginalną listę
    while (current != NULL) {
        // Zapisanie następnego węzła przed modyfikacją listy
        struct Node* next = current->next;

        // Wstawienie bieżącego węzła do posortowanej listy
        if (sorted == NULL || sorted->data <= current->data) {
            current->next = sorted;
            sorted = current;
        } else {
            // Znalezienie odpowiedniej pozycji w posortowanej liście
            struct Node* temp = sorted;
            while (temp->next != NULL && temp->next->data > current->data) {
                temp = temp->next;
            }

            // Wstawienie bieżącego węzła na odpowiednie miejsce
            current->next = temp->next;
            temp->next = current;
        }

        // Przechodzenie do następnego węzła w oryginalnej liście
        current = next;
    }

    // Zaktualizowanie głównego wskaźnika na posortowaną listę
    *head = sorted;
}

void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);

        // Dodaj nową linię po każdych 10 liczbach
        if (head->data % 10 == 0) {
            printf("\n");
        }

        head = head->next;
    }
    printf("\n");
}

void readFromFile(char *filename, struct Node** head) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int value;
    while (fscanf(file, "%d", &value) != EOF) {
        // Dodaj nowy węzeł do listy dla każdej wczytanej liczby
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = value;
        newNode->next = *head;
        *head = newNode;
    }

    if (fclose(file) == EOF) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }
}

void saveToFile(char *filename, struct Node* head) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    while (head != NULL) {
        fprintf(file, "%d ", head->data);

        // Dodaj nową linię po każdych 10 liczbach
        if (head->data % 10 == 0) {
            fprintf(file, "\n");
        }

        head = head->next;
    }

    if (fclose(file) == EOF) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }
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
    readFromFile("we.txt", &head);
    printf("Unsorted list:\n");
    printList(head);

    // Sortuj listę
    librarySort(&head);

    printf("Sorted list:\n");
    printList(head);

    // Zapisz wyniki do pliku
    saveToFile("out.txt", head);
    printf("Results saved to out.txt\n");

    // Zwolnij pamięć związana z listą
    freeList(&head);

    return 0;
}
