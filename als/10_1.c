#include <stdio.h>
#include <stdlib.h>

// Funkcja do naprawy kopca o korzeniu w indeksie i w poddrzewie o rozmiarze n
void heapify(int arr[], int n, int i) {
    int largest = i;  // Inicjowanie korzenia jako największego elementu
    int left_child = 2 * i + 1;
    int right_child = 2 * i + 2;

    // Sprawdzanie, czy lewe dziecko jest większe od korzenia
    if (left_child < n && arr[left_child] > arr[largest])
        largest = left_child;

    // Sprawdzanie, czy prawe dziecko jest większe od korzenia
    if (right_child < n && arr[right_child] > arr[largest])
        largest = right_child;

    // Zamiana korzenia, jeśli potrzebne, i rekurencyjne naprawianie poddrzewa
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

// Główna funkcja sortująca przez kopcowanie
void heapSort(int arr[], int n) {
    // Budowanie kopca (reorganizacja elementów)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Wydobywanie elementów z kopca i sortowanie
    for (int i = n - 1; i > 0; i--) {
        // Zamiana korzenia z ostatnim elementem
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Naprawianie kopca dla zmniejszonego poddrzewa
        heapify(arr, i, 0);
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

    heapSort(tablica, n);

    printf("\nTablica po sortowaniu: \n");
    Wypisz(n, tablica);

    saveToFile("out.txt", tablica, n);
    printf("Wyniki zapisane do out.txt\n");

    free(tablica);

    return 0;
}