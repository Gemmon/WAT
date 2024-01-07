
#include <stdio.h>
#include <stdlib.h>

void countingSort(int arr[], int n) {
    // Znajdź maksymalną wartość w tablicy
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    // Utwórz tablicę zliczającą o rozmiarze równej maksymalnej wartości + 1
    int *count = (int *)malloc((max + 1) * sizeof(int));
    if (count == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Zainicjuj tablicę zliczającą zerami
    for (int i = 0; i <= max; i++) {
        count[i] = 0;
    }

    // Zlicz wystąpienia każdej wartości
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    // Przeprowadź sumy częściowe na tablicy zliczającej
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    // Utwórz tablicę wynikową
    int *output = (int *)malloc(n * sizeof(int));
    if (output == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Umieść elementy w tablicy wynikowej zgodnie z tablicą zliczającą
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // Skopiuj posortowaną tablicę do oryginalnej
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    // Zwolnij zaalokowaną pamięć
    free(count);
    free(output);
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

    countingSort(tablica, n);

    printf("\nTablica po sortowaniu: \n");
    Wypisz(n, tablica);

    saveToFile("out.txt", tablica, n);
    printf("Wyniki zapisane do out.txt\n");

    free(tablica);

    return 0;
}