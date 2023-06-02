#include<stdio.h>
#include<string.h>
struct user{
    char name[20];
    int age;
    int adult;
    int isAStudent;
    int studentID;
    char degreeCourse;
    int weight;
    int height;
    int pet;

};

void addUser(struct user x, char name, int age ){
      
};

int main(){
    struct user a;
    strcpy( a.name, "Sam" );
    a.age = 21;

    printf("wiek: %d \n", a.age);
    printf("imie: %s \n", a.name);
    //printf("wiek: %d \n", b.age);
    
};