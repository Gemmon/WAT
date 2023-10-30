//============================================================================
// Zadanie 2_1  jezyk C
//  Lista jednokierunkowa zaimplementowana wskaünikowo
//  WCY22IY1S1  Chrapowicz Krzysztof
//============================================================================

#include <stdio.h>
#include <stdlib.h>

typedef struct lista lista;
struct lista
{
  int wartosc;
  lista* nastepny;
};

void wyswietlanie(lista* pierwszy) {
  lista* tymczasowy = pierwszy;
  if (tymczasowy == NULL)
    return;
  do {
    printf("%d ", tymczasowy->wartosc);
    tymczasowy = tymczasowy->nastepny;
  } while (tymczasowy != NULL);
  printf("\n");
}

void srednia(lista* pierwszy) {
  float wartosc = 0.0;
  float srednia = 0.0;
  int j = 0;
  lista* tymczasowy = pierwszy;
  if (tymczasowy == NULL)
    return;
  do {
    wartosc = wartosc + tymczasowy->wartosc;
    j++;
    tymczasowy = tymczasowy->nastepny;
  } while (tymczasowy != NULL);
  srednia = wartosc / j;
  printf("Wartosc srednia: %f\n", srednia);
}

void dodawanie_koniec(lista** pierwszy, int wartosc) {
  lista* ostatni = *pierwszy;
  if (ostatni == NULL) {
    lista* new = (lista*)malloc(sizeof(lista));
    new->wartosc = wartosc;
    new->nastepny = NULL;
    *pierwszy = new;
  } else {
    while (ostatni->nastepny != NULL) {
      ostatni = ostatni->nastepny;
    }
    lista* new = (lista*)malloc(sizeof(lista));
    new->wartosc = wartosc;
    new->nastepny = NULL;
    ostatni->nastepny = new;
  }
}

void usuwanie_pocz(lista** a) {
  lista* pom = *a;
  if (pom) {
    *a = pom->nastepny;
    free(pom);
  }
}

void usun(lista** pierwszy, int wartosc) {
  lista* obecny = *pierwszy;
  lista* poprzedni = obecny;
  if (obecny && obecny->wartosc == wartosc) {
    *pierwszy = obecny->nastepny;
    free(obecny);
    return;
  }
  obecny = obecny->nastepny;
  while (obecny != NULL) {
    if (obecny->wartosc == wartosc) {
      poprzedni->nastepny = obecny->nastepny;
      free(obecny);
      return;
    }
    poprzedni = obecny;
    obecny = obecny->nastepny;
  }
}

int main() {
  lista* wsk = (lista*)malloc(sizeof(lista));
  wsk->wartosc = 1;
  wsk->nastepny = NULL;

  printf("Wartosci:\n");
  int i;
  for (i = 2; i <= 100; i++) {
    dodawanie_koniec(&wsk, i);
  }

  wyswietlanie(wsk);
  srednia(wsk);
  usuwanie_pocz(&wsk);

  for (i = 1; i <= 100; i++) {
    if (i % 2 == 1) {
      usun(&wsk, i);
    }
  }

  wyswietlanie(wsk);
  srednia(wsk);
}
