#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);

        // Dodaj nową linię po każdych 10 liczbach
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }
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

    // Opcja wczytywania danych z pliku
    readFromFile("we.txt", arr, &n);

    printf("Unsorted array: \n");
    printArray(arr, n);

    quickSort(arr, 0, n - 1);

    printf("Sorted array: \n");
    printArray(arr, n);

    saveToFile("out.txt", arr, n);
    printf("Results saved to out.txt\n");

    return 0;
}
