#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int i,k,n,x;
char name[20];
int numb;
int choice,numbUsers,size;

//test

struct user{
    int numb;
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
};

void addUser(struct user *base, int *num){
    *num = *num +1;
    (struct user*)realloc(base,(*num)*sizeof(struct user));
    printf("Podaj wiek: ");
    scanf("%d", &base[*num-1].age);
     printf("Podaj imie: ");
    scanf("%s", &base[*num-1].name);
}


void showUser(struct user *base,int n){
    printf(" Numer uzytkownika: %d\nImie: %d",base[n].age, base[n].name);    
}

void showUsers(struct user *base, int n) {

    for (int i = 0; i < n; i++) {
    printf("Numer: %d, Name: %s\n", base[i].age, base[i].name);
    }
}

int main(){
 
 int num = 2;
 struct user *base;
 base = malloc(sizeof(struct user)*num);

 int wart = 1;
 base[0].age = 13;
 strcpy(base[0].name,"Tamo");
    
    
  printf("Wybierz z opcji:\n 1.Dodaj uzytkownika \n 2.Wyswietl wszystkich \n 3.Pokaz uzytkownika \n 4.Usun uzytkownika \n");
  scanf("%d", &choice);

    switch (choice){
    case 1:
      addUser(base, &num);  
    break;

    case 2:
          
      showUsers(base, num);

      break;

    case 3:

    printf("ktorego sasma? \n");
    scanf("%d", &numb);      
    showUser(base, numb);
    
    break;
    
    case 4:
  
    break;

    default:
      printf("Wybrano nie poprawnie.");
      break;
    }
    free(base);  
    return 0;
}
