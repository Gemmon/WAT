//============================================================================
// Zadanie 2_2  jezyk C++
//  Wizytownik
//  WCY22IY1S1  Chrapowicz Krzysztof
//============================================================================


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DLUGOSC 20

struct wizytowka {
    char nazwisko[MAX_DLUGOSC + 1];
    char imie[MAX_DLUGOSC + 1];
    int numer;
    struct wizytowka* prev;
    struct wizytowka* next;
};

struct lista {
    struct wizytowka head;
    struct wizytowka* tail;
};

struct wizytowka* stworzWizytowke(const char* nazwisko, const char* imie, int numer) {
    struct wizytowka* newskladnik = (struct wizytowka*)malloc(sizeof(struct wizytowka));
    strncpy(newskladnik->nazwisko, nazwisko, MAX_DLUGOSC);
    strncpy(newskladnik->imie, imie, MAX_DLUGOSC);
    newskladnik->numer = numer;
    newskladnik->nazwisko[MAX_DLUGOSC] = '\0'; // Ensure null-termination
    newskladnik->imie[MAX_DLUGOSC] = '\0'; // Ensure null-termination
    newskladnik->prev = NULL;
    newskladnik->next = NULL;
    return newskladnik;
}

int jestPusta(struct lista* list) {
    return list->head.next == NULL;
}

void dodajKoniec(struct lista* list, const char* nazwisko, const char* imie, int numer) {
    struct wizytowka* newskladnik = stworzWizytowke(nazwisko, imie, numer);

    if (jestPusta(list)) {
        list->head.next = newskladnik;
        newskladnik->prev = &list->head;
        list->tail = newskladnik;
    } else {
        struct wizytowka* current = list->tail;
        while (current != NULL) {
            if (strcmp(nazwisko, current->nazwisko) >= 0) {
                newskladnik->prev = current;
                newskladnik->next = current->next;
                if (current->next != NULL) {
                    current->next->prev = newskladnik;
                }
                current->next = newskladnik;

                if (current == list->tail) {
                    list->tail = newskladnik;
                }

                return;
            }
            current = current->prev;
        }

        // If the loop finishes, it means the new contact should be at the beginning of the list
        newskladnik->next = list->head.next;
        list->head.next->prev = newskladnik;
        list->head.next = newskladnik;
        newskladnik->prev = &list->head;
    }
}

void szukajWizytowke(struct lista* list, const char* nazwisko) {
    struct wizytowka* current = list->head.next;
    int z = 1;
    while (current != NULL) {
        if (strcmp(current->nazwisko, nazwisko) == 0) {
            printf("Nazwisko: %s Imie: %s, Numer: %d\n", current->nazwisko, current->imie, current->numer);
            z = 0;
            break;
        } else {
            current = current->next;
        }
    }
    if (z) {
        printf("Wizytowka o podanym nazwisku nie zostala znaleziona.\n");
    }
}

void swtorzListe(struct lista* list) {
    list->head.next = NULL;
    list->head.prev = NULL;
    list->tail = NULL;
}


void wyswietlListe(struct lista* list) {
    if (jestPusta(list)) {
        printf("Lista jest pusta.\n");
    } else {
        struct wizytowka* current = list->head.next;
        printf("Lista:\n");
        int iteracja = 1;
        while (current != NULL) {
            printf("%d. Nazwisko: %s Imie: %s Numer: %d\n", iteracja, current->nazwisko, current->imie, current->numer);
            current = current->next;
            iteracja++;
        }
        printf("\n");
    }
}

void wyswietlListeOdKonca(struct lista* list) {
    if (jestPusta(list)) {
        printf("Lista jest pusta.\n");
    } else {
        struct wizytowka* current = list->tail;
        printf("Lista (od konca):\n");
        int iteracja = 1;
        while (current != NULL) {
            printf("%d. Nazwisko: %c Imie: %c Numer: %d\n", iteracja, current->nazwisko, current->imie, current->numer);
            current = current->prev;
            iteracja++;
        }
        printf("\n");
    }
}

void usunWizytowke(struct lista* list, const char* nazwisko) {
    struct wizytowka* current = list->head.next;
    while (current != NULL) {
        if (strcmp(current->nazwisko, nazwisko) == 0) {
            // Found the contact, remove it
            if (current->prev != NULL) {
                current->prev->next = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }
            if (current == list->tail) {
                list->tail = current->prev;
            }
            free(current);
            printf("Wizytowka o nazwisku %s zostala usunieta.\n", nazwisko);
            return;
        } else {
            current = current->next;
        }
    }
    printf("Wizytowka o podanym nazwisku nie zostala znaleziona.\n");
}

void freeListe(struct lista* list) {
    struct wizytowka* current = list->head.next;
    struct wizytowka* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    list->head.next = NULL;
    list->tail = NULL;
}


void zapiszListe(struct lista* list, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Nie udalo sie otworzyc pliku do zapisu");
        return;
    }

    struct wizytowka* current = list->head.next;
    while (current != NULL) {
        fprintf(file, "%c %c %d\n", current->nazwisko, current->imie, current->numer);
        current = current->next;
    }

    fclose(file);
}

int main() {
    struct lista list;
    swtorzListe(&list);

    char nazwisko[MAX_DLUGOSC];
    char imie[MAX_DLUGOSC];
    int numer;
    while (1) {
        char choice = 'a';
        printf("\n1. Dodaj wizytowke(d)\n2. Szukaj wizytowki(s)\n3. Wypisz wizytowki(w)\n4. Wypisz wizytowki od konca(v)\n5. Usun wizytowke(u)\n6. Zapisz liste(z)\n7. Zakoncz program(e)\n");
        printf("Wybierz polecenie: ");
        scanf(" %c", &choice);

        switch (choice) {
        case 'd':
            printf("Podaj nazwisko: ");
            scanf(" %20s", nazwisko);
            printf("Podaj imie: ");
            scanf(" %20s", imie);
            printf("Podaj numer telefonu: ");
            scanf(" %d", &numer);
            dodajKoniec(&list, nazwisko, imie, numer);
            printf("Zostala dodana.\n");
            break;
        case 's':
            printf("Podaj nazwisko wizytowki: ");
            scanf(" %20s", nazwisko);
            szukajWizytowke(&list, nazwisko);
            break;
        case 'w':
            wyswietlListe(&list);
            break;
        case 'v':
            wyswietlListeOdKonca(&list);
            break;
        case 'u':
            printf("Podaj nazwisko wizytowki do usuniecia: ");
            scanf("%20s", nazwisko);
            usunWizytowke(&list, nazwisko);
            break;
        case 'z':
            zapiszListe(&list, "lista");
            printf("Zapisano listy \n");
            return 0;
        case 'e':
            freeListe(&list);
            printf("Zakonczenie programu\n");
            return 0;
        default:
            printf("Wybierz ponownie.\n");
        }
        while (getchar() != '\n');
    }

    return 0;
}
    return 0;
}
