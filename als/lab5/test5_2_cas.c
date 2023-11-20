#include <stdio.h>
#include <stdlib.h>

// Struktura reprezentująca klienta
typedef struct {
    char kod;  // Typ klienta: 'P' (PLATINIUM), 'G' (GOLD), 'S' (SILVER)
    int numer; // Numer klienta
    int czasTrwania;
} Klient;

// Struktura reprezentująca element kolejki
typedef struct Elem {
    Klient klient;
    struct Elem* nastepny;
} ElementKolejki;

// Struktura reprezentująca kolejkę
typedef struct {
    ElementKolejki* poczatek;
    ElementKolejki* koniec;
} Kolejka;

// Inicjalizacja kolejki
void inicjalizujKolejke(Kolejka* kolejka) {
    kolejka->poczatek = NULL;
    kolejka->koniec = NULL;
}



int nadajPriorytet(char kod) {
    switch (kod) {
        case 'P':
            return 2;
        case 'G':
            return 1;
        case 'S':
            return 0;
        default:
            fprintf(stderr, "Nieznany typ klienta: %c\n", kod);
            exit(EXIT_FAILURE);
    }
}

void dodajDoKolejki(Kolejka* kolejka, Klient klient) {
    ElementKolejki* nowyElement = (ElementKolejki*)malloc(sizeof(ElementKolejki));
    if (nowyElement == NULL) {
        fprintf(stderr, "Blad alokacji pamieci\n");
        exit(EXIT_FAILURE);
    }

    nowyElement->klient = klient;
    nowyElement->nastepny = NULL;

    int priorytetNowegoKlienta = nadajPriorytet(klient.kod);

    if (kolejka->koniec == NULL) {
        // Kolejka jest pusta
        kolejka->poczatek = nowyElement;
        kolejka->koniec = nowyElement;
    } else {
        // Dodaj klienta zgodnie z priorytetem
        ElementKolejki* obecny = kolejka->poczatek;
        ElementKolejki* poprzedni = NULL;

        while (obecny != NULL && nadajPriorytet(obecny->klient.kod) >= priorytetNowegoKlienta) {
            poprzedni = obecny;
            obecny = obecny->nastepny;
        }

        if (poprzedni == NULL) {
            // Klient ma najwyższy priorytet
            nowyElement->nastepny = kolejka->poczatek;
            kolejka->poczatek = nowyElement;
        } else {
            poprzedni->nastepny = nowyElement;
            nowyElement->nastepny = obecny;
        }

        if (obecny == NULL) {
            // Klient ma najniższy priorytet
            kolejka->koniec = nowyElement;
        }
    }
}
// Wczytywanie danych z pliku
void wczytajDaneZPliku(const char* nazwaPliku, Kolejka* kolejka) {
    FILE* plik = fopen(nazwaPliku, "r");
    if (plik == NULL) {
        fprintf(stderr, "Blad otwarcia pliku %s\n", nazwaPliku);
        exit(EXIT_FAILURE);
    }

    int obsluzonych = 0;

    while (1) {
        Klient klient;
        if (fscanf(plik, " %c %d %d", &klient.kod, &klient.numer, &klient.czasTrwania) != 3) {
            break; // Koniec pliku lub błąd
        }

        if (obsluzonych < 3) {
            // Obsłuż pierwszych trzech klientów od razu
            printf("Obsluzono klienta %c%d od razu\n", klient.kod, klient.numer);
            obsluzonych++;
        } else {
            // Dodaj pozostałych klientów do kolejki
            dodajDoKolejki(kolejka, klient);
        }
    }

    fclose(plik);
}

// Usunięcie klienta z kolejki
Klient usunZKolejki(Kolejka* kolejka) {
    if (kolejka->poczatek == NULL) {
        fprintf(stderr, "Kolejka jest pusta\n");
        exit(EXIT_FAILURE);
    }

    ElementKolejki* doUsuniecia = kolejka->poczatek;
    Klient klient = doUsuniecia->klient;

    kolejka->poczatek = doUsuniecia->nastepny;
    free(doUsuniecia);

    if (kolejka->poczatek == NULL) {
        // Kolejka jest teraz pusta
        kolejka->koniec = NULL;
    }

    return klient;
}

// Sprawdzenie, czy kolejka jest pusta
int czyKolejkaPusta(const Kolejka* kolejka) {
    return kolejka->poczatek == NULL;
}

// Obsługa klientów
void obslugaKlientow(Kolejka* kolejka) {
    // Obsłuż pierwszych trzech klientów od razu
    for (int i = 1; i <= 3; ++i) {
        if (!czyKolejkaPusta(kolejka)) {
            Klient klient = usunZKolejki(kolejka);
            printf("Obsluzono klienta %c %d\n", klient.kod, klient.numer);
        }
    }

    // Obsłuż resztę klientów według priorytetu
    while (!czyKolejkaPusta(kolejka)) {
        Klient klient = usunZKolejki(kolejka);
        printf("Obsluzono klienta %c %d\n", klient.kod, klient.numer);
    }
}

int main() {
    Kolejka kolejka;
    inicjalizujKolejke(&kolejka);


    wczytajDaneZPliku("we.txt", &kolejka);
    // Obsłuż klientów
    obslugaKlientow(&kolejka);

    return 0;
}