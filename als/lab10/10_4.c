
#include <stdio.h>
#include <stdlib.h>

// Funkcja do znalezienia maksymalnej liczby w tablicy
int findMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// Funkcja do przeprowadzenia sortowania pozycyjnego dla jednej cyfry
void countingSort(int arr[], int n, int exp) {
    const int BASE = 10; // System liczbowy, dla którego sortujemy (dziesiętny)
    
    int *output = (int *)malloc(n * sizeof(int));
    if (output == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    int *count = (int *)malloc(BASE * sizeof(int));
    if (count == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Inicjalizacja tablicy count zerami
    for (int i = 0; i < BASE; i++) {
        count[i] = 0;
    }

    // Liczenie wystąpień poszczególnych cyfr
    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % BASE]++;
    }

    // Przeprowadzenie sumy prefiksowej
    for (int i = 1; i < BASE; i++) {
        count[i] += count[i - 1];
    }

    // Umieszczenie elementów w tablicy wynikowej zgodnie z ich cyframi
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % BASE] - 1] = arr[i];
        count[(arr[i] / exp) % BASE]--;
    }

    // Skopiowanie posortowanej tablicy z powrotem do tablicy wejściowej
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    // Zwolnij zaalokowaną pamięć
    free(count);
    free(output);
}
// Funkcja sortująca przez sortowanie pozycyjne
void radixSort(int arr[], int n) {
    // Znalezienie maksymalnej liczby w tablicy
    int max = findMax(arr, n);

    // Przechodzenie przez poszczególne cyfry
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSort(arr, n, exp);
    }
}

//zmieniona funkcja by zawsze generowalo od 0 do 1000 
void GenLos(int n, int tab[])
{       
        int i;
    	for ( i = 0; i < n; i++)
    	{
    		tab[i] = (rand() % (999));
		}
}

//funkcja zabrana z teams do wypisywania
void Wypisz(int n, int tab[])
{ 
         int i;
    for (i = 0; i < n; i++)
    {
        printf ("%7d ", tab[i] );
        if ((i + 1) % 10 == 0)
        {
        	printf ("\n");
		}
    }
}

// czytanie z pliku
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
    int i;
    for ( i = 0; i < size; i++) {
        fprintf(file, "%d ", arr[i]);

        // Dodawanie linii po 10 liczbach
        if ((i + 1) % 10 == 0) {
            fprintf(file, "\n");
        }
    }

    if (fclose(file) == EOF) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }
}

// Przykład użycia
int main() {
    int n;
    int *tablica;

    int choice;
    printf("Wybierz metode wprowadzania danych:\n");
    printf("1. Z klawiatury\n");
    printf("2. Z pliku\n");
    printf("3. Losowo\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Podaj ilosc elementow do podania:\n");
            scanf("%d", &n);
            tablica = (int*)malloc(n * sizeof(int));
            if (tablica == NULL) {
                perror("Memory allocation failed");
                return 1;
            }
            int i;
            for (i = 0; i < n; i++) {
                printf("Podaj element %d: ", i + 1);
                scanf("%d", &tablica[i]);
            }
            break;

        case 2:
            n = 50;
            tablica = (int*)malloc(n * sizeof(int));
            if (tablica == NULL) {
                perror("Memory allocation failed");
                return 1;
            }
            readFromFile("we.txt", tablica, &n);
            break;

        case 3:
            printf("Podaj ilosc elementow do wygenerowania:\n");
            scanf("%d", &n);
            tablica = (int*)malloc(n * sizeof(int));
            if (tablica == NULL) {
                perror("Memory allocation failed");
                return 1;
            }
            GenLos(n, tablica);
            break;

        default:
            printf("Nieprawidlowy wybor.\n");
            return 1;
    }

    printf("Wybrane liczby:\n");
    Wypisz(n, tablica);

    printf("\nTablica przed sortowaniem: \n");
    Wypisz(n, tablica);

    radixSort(tablica, n);

    printf("\nTablica po sortowaniu: \n");
    Wypisz(n, tablica);

    saveToFile("out.txt", tablica, n);
    printf("Wyniki zapisane do out.txt\n");

    free(tablica);

    return 0;
}