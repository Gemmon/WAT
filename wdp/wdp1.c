#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
int n=0;
int y=0;
int x=0;
int z=0;

int tab[4];
for( n=0; n<4; n++){
    int i;
    scanf("%d", &i);
    tab[n]=i;    
}
printf("\n");

int hamming[7][4]={
{1,1,0,1},
{1,0,1,1},
{1,0,0,0},
{0,1,1,1},
{0,1,0,0},
{0,0,1,0},
{0,0,0,1}};

int hammingcheck[3][7]={
    {1,0,1,0,1,0,1},
    {0,1,1,0,0,1,1},
    {0,0,0,1,1,1,1}};
    
//mnożenie macierzy
int retab[7];
for(n=0;n<7;n++){
   for(y=0;y<4;y++){
 z += (hamming[n][y])*(tab[y]); }
retab[n] = z%2;
z=0; }



//utworzenie randomowego błędu
srand(time(NULL));
int r = rand()%7;
if(retab[r]==0){retab[r]=1;}
else{retab[r]=0;}
printf("\nlokalizacja zmiany: %d", r);

//przemnożenie retab z hammingcheck

int retab1[3];
for(n=0;n<3;n++){
    for(y=0;y<7;y++){
        z += (hammingcheck[n][y])*(retab[y]);}
        retab1[n] = z%2;
        z=0;
}

printf("\nWynik mnozenia to: ");
for(n=0; n<7; n++){
   printf("%d", retab[n]);
}

for(n=0;n<7;n++){
   if(retab[n]==0){
      printf("\nLosowo blad pojawil sie w %d wierszu.", n+1);
   }}

printf("\n");
 for(n=0;n<3;n++){
    printf("%d", retab1[n]);
 }  

return 0;
}