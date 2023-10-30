#include <iostream>
#include <fstream>
using namespace std;

struct wizytowka {
    int ID;
    char name;
    wizytowka* prev;
    wizytowka* next;
};

struct lista {
    wizytowka head;
    wizytowka* tail;
};

wizytowka* stworzWizytowke(int ID, const char& name) {
    wizytowka* newskladnik = new wizytowka;
    newskladnik->ID = ID;
    newskladnik->name = name;
    newskladnik->prev = NULL;
    newskladnik->next = NULL;
    return newskladnik;
}

void swtorzListe(lista* list) {
    list->head.next = NULL;
    list->head.prev = NULL;
    list->tail = NULL;
}

bool jestPusta(lista* list) {
    return list->head.next == NULL;
}

void dodajKoniec(lista* list, int ID, const char& name) {
    wizytowka* newskladnik = stworzWizytowke(ID, name);
    if (jestPusta(list)) {
        list->head.next = newskladnik;
        newskladnik->prev = &list->head;
        list->tail = newskladnik;
    }
    else {
        newskladnik->prev = list->tail;
        list->tail->next = newskladnik;
        list->tail = newskladnik;
    }
}

int usunPoczatek(lista* list) {
    if (jestPusta(list)) {
        cout << "Lista jest pusta." << endl;
        return -1;
    }
    else {
        wizytowka* temp = list->head.next;
        int ID = temp->ID;
        char name = temp->name;

        list->head.next = temp->next;
        if (list->head.next != NULL)
            list->head.next->prev = &list->head;
        else
            list->tail = NULL;
        delete temp;
        return ID;
    }
}

void wyswietlListe(lista* list) {
    if (jestPusta(list)) {
        cout << "Lista jest pusta." << endl;
    }
    else {
        wizytowka* current = list->head.next;
        cout << "Lista: " << endl;
        int numer = 1;
        while (current != NULL) {
            cout << numer << ". Nr " << current->ID << " Imie: " << current->name << endl;
            current = current->next;
            numer++;
        }
        cout << endl;
    }
}

void wyswietlListeOdKonca(lista* list) {
    if (jestPusta(list)) {
        cout << "Lista jest pusta." << endl;
    }
    else {
        wizytowka* current = list->tail;
        cout << "Lista (od konca): " << endl;
        int numer = 1;
        while (current != NULL) {
            cout << numer << ". Nr " << current->ID << " Imie: " << current->name << endl;
            current = current->prev;
            numer++;
        }
        cout << endl;
    }
}


void szukajWizytowke(lista* list, int ID){
    wizytowka* current = list->head.next;
    int z = 1;
    while(z)
    if( current->ID = ID){
        cout << "ID: " << current->ID << " Imie: " << current->name << endl;
        z = 0;
    } else {
       current = current->next;
    }

}

void freeListe(lista* list) {
    wizytowka* current = list->head.next;
    wizytowka* next;
    while (current != NULL) {
        next = current->next;
        delete current;
        current = next;
    }
    list->head.next = NULL;
    list->tail = NULL;
}


void zapiszListe(lista* list, const char& filename) {
   FILE* file = fopen(filename, "w");
    if (!file) {
        cout << "Blad pliku." << endl;
        return;
    }

    wizytowka* current = list->head.next;
    while (current != NULL) {
        file << "ID: " << current->ID << " Imie: " << current->name << endl;
        current = current->next;
    }
    fclose(();
}

int main() {
    lista list;
    swtorzListe(&list);

    int choice = 0;
    int ID = 0;
    char name;
    while (true) {
        cout << "\n1. Dodaj wizytowke(d)\n2. Szukaj wizytowki(s)\n3. Wypisz wizytowki(w)\n4. Wypisz wizytowki od konca(v)\n5. Usun wizytowke(u)\n6. Zapisz rekordy w pliku(z)\n7. Zakoncz program(Ctrl-Z)\n";
        cout << "Wybierz polecenie: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Podaj ID: ";
            cin >> ID;
            cout << "Podaj imie: ";
            cin >> name;
            dodajKoniec(&list, ID, name);
            cout << "Zostala dodana." << endl;
            break;
        case 2:
           cout<< "Podaj numer wizytowki: "<<endl;
           cin >> ID;
           szukajWizytowke(&list, ID);


        break;
        case 3:
            wyswietlListe(&list);
            break;
        case 4:
            wyswietlListeOdKonca(&list);
            break;
        case 5:
            if (!jestPusta(&list)) {
                int removedElement = usunPoczatek(&list);
                cout << "Zostal usuniety: " << removedElement << endl;
            }
            else {
                cout << "Lista jest pusta." << endl;
            }
            break;
        case 6: {
            char filename;
            cout << "Nazwa pliku: ";
            cin >> filename;
            zapiszListe(&list, filename);
            cout << "Zapisano liste do pliku." << endl;
            break;
        }
        case 7:
            freeListe(&list);
            cout << "Zakonczenie programu" << endl;
            return 0;
        default:
            cout << "Wybierz ponownie." << endl;
        }
    }

    return 0;
}
