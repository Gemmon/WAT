#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int character;
    int frequency;
} czestosc;

typedef struct {
    int ojciec;
    int potomek1;
    int potomek2;
} drzewoHuffmana;

typedef struct {
    int symbol;
    unsigned char slowo[4];
    int liczbaBitow;
} tablicaKodu;

tablicaKodu tablicaKoduFull[512]; // Declaration of tablicaKoduFull

int compare_freq(const void *a, const void *b) {
    const czestosc *fa = (const czestosc *)a;
    const czestosc *fb = (const czestosc *)b;
    return fb->frequency - fa->frequency;
}

void tworz_model(const char *nazwa_pliku) {
    FILE *plik;
    int licznik[256] = {0};
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

    char plik_model[256];
    strcpy(plik_model, nazwa_pliku);
    strcat(plik_model, ".model");
    plik = fopen(plik_model, "w");

    if (plik == NULL) {
        printf("Nie można otworzyć pliku modelu.\n");
        return;
    }

    for (int i = 0; i < 256; i++) {
        if (licznik[i] > 0) {
            fprintf(plik, "%d  %d\n", i, licznik[i]);
        }
    }

    fclose(plik);

    char plik_modelSort[256];
    strcpy(plik_modelSort, nazwa_pliku);
    strcat(plik_modelSort, ".modelSort");
    plik = fopen(plik_modelSort, "w");

    if (plik == NULL) {
        printf("Nie można otworzyć.\n");
        return;
    }

    czestosc char_freq[256];
    int count = 0;
    for (int i = 0; i < 256; i++) {
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

    fclose(plik);

    char plik_bajty[256];
    strcpy(plik_bajty, nazwa_pliku);
    strcat(plik_bajty, ".ileBajtow");
    plik = fopen(plik_bajty, "w");

    fprintf(plik, "%d", liczbaBajtow);
    fclose(plik);

    // drzewo Huffmana
    char plik_drzewo[256];
    strcpy(plik_drzewo, nazwa_pliku);
    strcat(plik_drzewo, ".drzewo");
    plik = fopen(plik_drzewo, "w");

    czestosc modelDlaDrzewa[256];
    int liczbaSymboli = 0;

    for (int i = 0; i < 256; i++) {
        if (licznik[i] > 0) {
            modelDlaDrzewa[liczbaSymboli].character = i;
            modelDlaDrzewa[liczbaSymboli].frequency = licznik[i];
            liczbaSymboli++;
        }
    }

    qsort(modelDlaDrzewa, liczbaSymboli, sizeof(czestosc), compare_freq);

    drzewoHuffmana drzewo[256];
    int licznikSymboli = liczbaSymboli;
    int dodane = 0;

    for (int k = 0; k < liczbaSymboli - 1; k++) {
        drzewo[k].ojciec = 256 + k;
        drzewo[k].potomek1 = modelDlaDrzewa[liczbaSymboli - 1 - k].character;
        drzewo[k].potomek2 = modelDlaDrzewa[liczbaSymboli - 2 - k].character;
        modelDlaDrzewa[liczbaSymboli - 2 - k].character = 256 + k;
        modelDlaDrzewa[liczbaSymboli - 2 - k].frequency = modelDlaDrzewa[liczbaSymboli - 1 - k].frequency + modelDlaDrzewa[liczbaSymboli - 2 - k].frequency;
        licznikSymboli--;
        qsort(modelDlaDrzewa, licznikSymboli, sizeof(czestosc), compare_freq);
        dodane++;
    }

    for (int i = 0; i < dodane; i++) {
        fprintf(plik, "%d %d %d\n", drzewo[i].ojciec, drzewo[i].potomek1, drzewo[i].potomek2);
    }

    fclose(plik);

    // tabela kodowa
    char plik_tabelaF[256];
    strcpy(plik_tabelaF, nazwa_pliku);
    strcat(plik_tabelaF, ".tabelaKoduFull");
    plik = fopen(plik_tabelaF, "w");

    int licznikKodu = 0;

    for (int k = 0; k < 512; ++k) {
        for (int i = 0; i < 4; ++i)
            tablicaKoduFull[k].slowo[i] = 0;
        tablicaKoduFull[k].symbol = 0;
        tablicaKoduFull[k].liczbaBitow = 0;
    }

    licznikSymboli = liczbaSymboli - 2;
    licznikKodu = 0;
    tablicaKoduFull[licznikKodu].symbol = drzewo[licznikSymboli].ojciec;

    while (licznikSymboli + 1) {
        int symbolOjca = drzewo[licznikSymboli].ojciec;
        tablicaKoduFull[licznikKodu + 1].symbol = drzewo[licznikSymboli].potomek1;
        tablicaKoduFull[licznikKodu + 2].symbol = drzewo[licznikSymboli].potomek2;

        int indeksOjca = -1;
        for (int i = 0; i < licznikKodu + 1; ++i) {
            if ((tablicaKoduFull[i].symbol) == (symbolOjca)) {
                indeksOjca = i;
                break;
            }
        }
        if (indeksOjca == -1) {
            printf("Błąd tworzenia tablicy kodu\n");
            exit(EXIT_FAILURE);
        }

        int dlugoscCiagu = tablicaKoduFull[indeksOjca].liczbaBitow;

        for (int i = 0; i < 4; ++i) {
            tablicaKoduFull[licznikKodu + 1].slowo[i] = tablicaKoduFull[indeksOjca].slowo[i];
            tablicaKoduFull[licznikKodu + 2].slowo[i] = tablicaKoduFull[indeksOjca].slowo[i];
        }

        int pozycja = dlugoscCiagu;
        int ktoryBajt = pozycja / 8;
        int ktoryBit = pozycja % 8;
        unsigned char jedynka = 1 << (7 - ktoryBit);
        unsigned char bajt = tablicaKoduFull[indeksOjca].slowo[ktoryBajt] | jedynka;

        tablicaKoduFull[licznikKodu + 1].slowo[ktoryBajt] = bajt;
        tablicaKoduFull[licznikKodu + 1].liczbaBitow = dlugoscCiagu + 1;
        tablicaKoduFull[licznikKodu + 2].liczbaBitow = dlugoscCiagu + 1;
        licznikKodu += 2;
        licznikSymboli--;

    }

for (int k = 0; k <= licznikKodu; k++) {
    unsigned char *slowo = tablicaKoduFull[k].slowo;
    fprintf(plik, "%d %d %d %d %d %d\n", 
            tablicaKoduFull[k].symbol, 
            slowo[0], slowo[1], slowo[2], slowo[3], tablicaKoduFull[k].liczbaBitow);
}


    fclose(plik);


     // tabela kodowa bez symboli dodatkowych
    char plik_tabelaK[256];
    strcpy(plik_tabelaK, nazwa_pliku);
    strcat(plik_tabelaK, ".tabelaKodu");
    plik = fopen(plik_tabelaK, "w");

    for (int k = 0; k <= licznikKodu; k++) {
    if(tablicaKoduFull[k].symbol < 256){
    unsigned char *slowo = tablicaKoduFull[k].slowo;
    fprintf(plik, "%d %d %d %d %d %d\n", 
            tablicaKoduFull[k].symbol, 
            slowo[0], slowo[1], slowo[2], slowo[3], tablicaKoduFull[k].liczbaBitow);
    }
}

    fclose(plik);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Użycie: %s <nazwa_pliku>\n", argv[0]);
        return 1;
    }

    tworz_model(argv[1]);

    return 0;
}
