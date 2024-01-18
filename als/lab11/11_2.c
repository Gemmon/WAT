#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Tworzenie tymczasowych tablic
    int L[n1], R[n2];

    // Kopiowanie danych do tablic tymczasowych L[] i R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Scalanie tablic tymczasowych z powrotem do arr[left..right]
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Kopiowanie pozostałych elementów L[], jeśli są
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Kopiowanie pozostałych elementów R[], jeśli są
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        // Znajdź punkt środkowy
        int mid = left + (right - left) / 2;

        // Sortuj lewą i prawą połowę
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Scal obie połowy
        merge(arr, left, mid, right);
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
            readFromFile("we50.txt", tablica, &n);
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

    mergeSort(tablica, 0, n);

    printf("\nTablica po sortowaniu: \n");
    Wypisz(n, tablica);

    saveToFile("out.txt", tablica, n);
    printf("Wyniki zapisane do out.txt\n");

    free(tablica);

    return 0;
}