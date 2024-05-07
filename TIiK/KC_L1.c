#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_ASCII_VALUE 128

typedef struct {
    int character;
    int frequency;
} czestosc;

int compare_freq(const void *a, const void *b) {
    const czestosc *fa = (const czestosc *)a;
    const czestosc *fb = (const czestosc *)b;
    return fb->frequency - fa->frequency;
}

void tworz_model(const char *nazwa_pliku) {
    FILE *plik;
    int licznik[MAX_ASCII_VALUE] = {0};
    int znak;
    int liczbaBajtow = 0;

    plik = fopen(nazwa_pliku, "r");

    if (plik == NULL) {
        printf("Nie można otworzyć pliku.\n");
        return;
    }

    while ((znak = fgetc(plik)) != EOF) {
        liczbaBajtow++;
        if (isprint(znak)) {
            licznik[znak]++;
        }
    }

    fclose(plik);

    char *last_dot = strrchr(nazwa_pliku, '.');
    if (last_dot != NULL) {

        *last_dot = '\0';
    }

    char plik_model[100];
    strcpy(plik_model, nazwa_pliku);
    strcat(plik_model, ".model"); 
    plik = fopen(plik_model, "w");

    if (plik == NULL) {
        printf("Nie można otworzyć pliku modelu.\n");
        return;
    }

    fprintf(plik, "", plik_model);
    for (int i = 0; i < MAX_ASCII_VALUE; i++) {
        if (licznik[i] > 0) {
            fprintf(plik, "%d  %d\n", i, licznik[i]);
        }
    }

    fclose(plik);

    char plik_modelSort[100]; 
    strcpy(plik_modelSort, nazwa_pliku);
    strcat(plik_modelSort, ".modelSort"); 
    plik = fopen(plik_modelSort, "w");

    if (plik == NULL) {
        printf("Nie można otworzyć.\n");
        return;
    }

    fprintf(plik, "", plik_modelSort);

    czestosc char_freq[MAX_ASCII_VALUE];
    int count = 0;
    for (int i = 0; i < MAX_ASCII_VALUE; i++) {
        if (licznik[i] > 0) {
            char_freq[count].character = i;
            char_freq[count].frequency = licznik[i];
            count++;
        }
    }

    qsort(char_freq, count, sizeof(czestosc), compare_freq);

    for (int i = 0; i < count; i++) {
        fprintf(plik, "%d  %d\n", char_freq[i].character, char_freq[i].frequency);
    }

    // Zamykamy plik
    fclose(plik);

    char plik_bajty[100]; 
    strcpy(plik_bajty, nazwa_pliku);
    strcat(plik_bajty, ".ileBajtow"); 
    plik = fopen(plik_bajty, "w");
    
   fprintf(plik, "%d", liczbaBajtow);
    
    fclose(plik);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uzycie: %s <nazwa_pliku>\n", argv[0]);
        return 1;
    }

    tworz_model(argv[1]);

    return 0;
}