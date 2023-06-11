#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int i,k,n,x;
char name[20];
int choice,numbUsers;


typedef struct{
    char name[20];
    int age;
    /*
    int adult;
    int isAStudent;
    int studentID;
    char degreeCourse;
    int weight;
    int height;
    int pet;
*/
} user;

user* base(int size) {
    user* base = malloc(size * sizeof(user));
    if (base == NULL) {
        printf("Alokacja pamieci nie powiodla sie.\n");
        return NULL;
    }


    return base;
}
user addUser(){
    user u;

    printf("Podaj imie: \n");
    scanf("%s", &u.name);

    printf("Podaj wiek: \n");
    scanf("%d", &u.age);

    return u;
}

void showUsers( user u ){

    printf("Imie: %s \n", u.name);
    printf("Wiek: %d \n", u.age);

};

int main(){
    int numbUsers = 2;

    user u1;

    printf("Wybierz z opcji:\n 1.Dodaj uzytkownika \n 2.Wyswietl wszystkich \n 3.Usun uzytkownika \n");
    scanf("%d", &choice);

    switch (choice){
    case 1:
      user u = addUser();
      printf("Uzytkownik: \nImie: %s \nWiek: %d \nzostal dodany.", u.name, u.age);
      break;

    case 2:

    for(int i=0; i < numbUsers*sizeof(user); i++){
          showUsers(u1);
    }
      
      break;

    case 3:

    break;

    default:
      printf("Wybrano nie poprawnie.");
      break;
    }


    

    

   
/*
    strcpy( a.name, "Sam" );
    printf("Podaj imie: "); 
    fgets(u1.name, 20, stdin);
    
    

    u1.age = 21;

    showUsers(u1);
   /*
    printf("wiek: %d \n", u1.age);
    printf("imie: %s \n", u1.name);
*/

    //printf("wiek: %d \n", b.age);
    
};