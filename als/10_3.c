#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Funkcja zamieniająca miejscami elementy o podanych indeksach w tablicy
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Funkcja implementująca algorytm sortowania grzebieniowego
void combSort(int arr[], int n) {
    // Ustawienie początkowego rozstawu
    int gap = n;
    bool swapped = true;

    // Iteruj, dopóki rozstaw nie będzie mniejszy niż 1 i nie wykonano żadnej zamiany
    while (gap != 1 || swapped) {
        // Aktualizuj rozstaw
        if (gap > 1) {
            gap = (int)(gap / 1.3);
        }

        swapped = false;

        // Przejdź przez tablicę i zamień elementy w odpowiednich odległościach
        for (int i = 0; i + gap < n; i++) {
            if (arr[i] > arr[i + gap]) {
                swap(&arr[i], &arr[i + gap]);
                swapped = true;
            }
        }
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

    combSort(tablica, n);

    printf("\nTablica po sortowaniu: \n");
    Wypisz(n, tablica);

    saveToFile("out.txt", tablica, n);
    printf("Wyniki zapisane do out.txt\n");

    free(tablica);

    return 0;
}