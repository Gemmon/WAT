#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{  
    int ID;
    char name[20];
    struct node *prev;
    struct node *next;
};

struct linkedList{
    struct node  head;
    struct node *tail;
};

struct node *createNode(int ID, const char* name){
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->ID = ID;
    strncpy(newNode->name, name, sizeof(newNode->name) - 1);
    newNode->name[sizeof(newNode->name) - 1] = '\0'; 
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void createList(struct linkedList* list){
    list->head.next = NULL;
    list->head.prev = NULL;
    list->tail = NULL;
}

int isEmpty(struct linkedList* list){
    return list->head.next == NULL;
}

void insertEnd(struct linkedList* list, int ID, const char *name){
    struct node *newNode = createNode(ID, name);
    if (isEmpty(list)) {
        list->head.next = newNode;
        newNode->prev = &list->head;
        list->tail = newNode;
    }else{
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

int removeFront(struct linkedList* list){
    if (isEmpty(list)) {
        printf("Lista jest pusta.\n");
        return -1;
    }else{
        struct node *temp = list->head.next;
        int ID = temp->ID;
        char *name = temp->name;
        
        list->head.next = temp->next;
        if (list->head.next != NULL)
            list->head.next->prev = &list->head;
        else
            list->tail = NULL;
        free(temp);
        return ID;
    }
}

void displayList(struct linkedList* list){
    if (isEmpty(list)) {
        printf("Lista jest pusta.\n");
    }else{
        struct node *current = list->head.next;
        printf("Lista: \n");
        int numer = 1;
        while (current != NULL) {
            printf("%d.Nr %d Imie: %s\n",numer, current->ID, current->name);
            current = current->next;
            numer++;
        }
        printf("\n");
    }
}

void freeList(struct linkedList* list){
    struct node *current = list->head.next;
    struct node *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    list->head.next = NULL;
    list->tail = NULL;
}

void loadListFromFile(struct linkedList* list, const char* filename){
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Blad pliku.\n");
        return;
    }

    int ID;
    char name[20];
    while (fscanf(file, "ID: %d Imie: %s\n", &ID, name) != EOF) {
        insertEnd(list, ID, name);
    }
    fclose(file);
}

void saveListToFile(struct linkedList* list, const char* filename){
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Blad pliku.\n");
        return;
    }

    struct node *current = list->head.next;
    while (current != NULL) {
        fprintf(file, "ID: %d Imie: %s\n", current->ID, current->name);
        current = current->next;
    }
    fclose(file);
}

int main(){
    struct linkedList list;
    createList(&list);

    int choice = 0;
    int ID = 0;
    char name[20];
    while (1) {
        printf("\n1.Pokaz liste\n2.Dodaj uzytkownika\n3.Usun uzytkownika.\n4.Zaladuj liste z pliku\n5.Zapisz liste\n6.Zakoncz program\n");
        printf("Wybierz polecenie: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayList(&list);
                break;
            case 2:
                printf("Podaj ID: ");
                scanf("%d", &ID);
                printf("Podaj imie: ");
                scanf("%19s", &name);
                insertEnd(&list, ID, name);
                printf("Zostala dodana.\n");
                break;
            case 3:
                if (!isEmpty(&list)) {
                    int removedElement = removeFront(&list);
                    printf("Zostal usuniety: %d\n", removedElement);
                }else{
                    printf("Lista jest pusta.\n");
                }
                break;
            case 4: {
                char filename[10];
                printf("Nazwa pliku: ");
                scanf("%9s", filename);
                loadListFromFile(&list, filename);
                printf("Zaladowano liste z pliku.\n");
                break;
            }
            case 5: {
                char filename[10];
                printf("Nazwa pliku: ");
                scanf("%9s", filename);
                saveListToFile(&list, filename);
                printf("Zapisano liste do pliku.\n");
                break;
            }
            case 6:
                freeList(&list);
                printf("Zakonczenie programu\n");
                return 0;
            default:
                printf("Blad wyboru.\n");
        }
    }
}
