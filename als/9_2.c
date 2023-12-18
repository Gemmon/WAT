#include <stdio.h>
#include <stdlib.h>

void librarySort(int arr[], int n) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        // Przesuń elementy większe od klucza o jedno miejsce w prawo
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        // Wstaw puste miejsce przed kluczem
        arr[j + 1] = 0;

        // Przesuń elementy większe od klucza o jedno miejsce w prawo
        while (j >= 0 && arr[j] == 0) {
            arr[j + 1] = 0;
            j = j - 1;
        }

        // Wstaw klucz w puste miejsce
        arr[j + 1] = key;
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void readFromFile(char *filename, int arr[], int *size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (fscanf(file, "%d", &arr[i]) != EOF) {
        i++;
    }

    if (fclose(file) == EOF) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }

    *size = i;
}

void saveToFile(char *filename, int arr[], int size) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d ", arr[i]);

        // Dodaj nową linię po każdych 10 liczbach
        if ((i + 1) % 10 == 0) {
            fprintf(file, "\n");
        }
    }

    if (fclose(file) == EOF) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }
}


int main() {
    int arr[100];  // Załóżmy maksymalny rozmiar tablicy
    int n;
    
    readFromFile("we.txt", arr, &n);
    printf("Unsorted array: \n");
    printArray(arr, n);

    librarySort(arr, n);

    printf("Sorted array: \n");
    printArray(arr, n);
    saveToFile("out.txt", arr, n);

    return 0;
}