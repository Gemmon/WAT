#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

int blad[10];
int n,h,u,i,y,x,z,r,c,ups;

int main(){
srand(time(NULL));

//tworzenie macierzy
int tab[4];
for( n=0; n<4; n++){
    r = rand()%2;
    tab[n]=r;   
}

printf("\nLosowo wygenerowana macierz 4bitowa: ");

for(n=0;n<4;n++){
   printf("%d", tab[n]);
}

int macierz[40];
for(n=0;n<40;n++){ 
    r = rand()%2;
    macierz[n]=r;
}

printf("\nLosowo wygenerowana macierz 40 bitowa: ");

for(n=0;n<40;n++){
   printf("%d", macierz[n]);
}

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

int remacierz[70];
for (i=0;i<10;i++){
  for(n=0;n<7;n++){
    for(y=0;y<4;y++){
      z += (hamming[n][y])*(macierz[i*4+y]); 
      }
   remacierz[i*7+n] = z%2;
   z=0;
   }
}

printf("\nWynik mnozenia 7bit z kodem hamminga to: ");
for(n=0; n<7; n++){
   printf("%d", retab[n]);
}

printf("\nWynik mnozenia 70bit z kodem hamminga to: ");
for(n=0; n<70; n++){
   printf("%d", remacierz[n]);
}

//utworzenie randomowych błędów
r = rand()%7;
int rm = rand()%70;
if(retab[r]==0) retab[r]=1;
else retab[r]=0;
printf("\nLokalizacja zmiany w macierzy 7 bitowej: %d", r+1);

if(remacierz[rm]==0) remacierz[rm]=1;
else remacierz[rm]=0;
printf("\nLokalizacja zmiany w macierzy 70 bitowej: %d", rm+1);

//przemnożenie wyników mnożenia z hammingcheck
int retab1[3];
for(n=0;n<3;n++){
    for(y=0;y<7;y++){
        z += (hammingcheck[n][y])*(retab[y]);}
        retab1[n] = z%2;
        z=0;
}

int remacierz1[30];
for(i=0;i<10;i++){
   for(n=0;n<3;n++){
    for(y=0;y<7;y++){
        z += (hammingcheck[n][y])*(remacierz[7*i+y]);
        }
        remacierz1[n+3*i] = z%2;
        z=0;
} }

//sprawdzenie gdzie są błędy
for(i=0;i<10;i++){
   for(n=0;n<3;n++){
if(remacierz1[i*3+n]!=0){ blad[i]=i;
  }
  }}

printf("\nWynik mnozenia 7 bit po bledzie to: ");
for(n=0; n<7; n++){
   printf("%d", retab[n]);
}

printf("\nWynik mnozenia 70bit po bledzie to: ");
for(n=0; n<70; n++){
   printf("%d", remacierz[n]);
}

printf("\nWynik mnozenia macierzy 70 bitowej z hammingcheck: ");
for(n=0;n<30;n++){printf("%d", remacierz1[n]);}

// Podanie wyników
int decimal=0;
int modifier=1;
int wiersz=0;        
   for (i=0;i<3;i++){
          decimal += retab1[i]*modifier;
          modifier = modifier*2;
        }
printf("\nlokalizacja bledu 7bitowej: %d\n", decimal);

if(retab[decimal-1]==0) retab[decimal-1]=1;
else retab[decimal-1]=0;

printf("Poprawienie macierzy 7bitowej: ");
for(n=0; n<7; n++){
   printf("%d", retab[n]);
}

printf("\n");
modifier = 1;
decimal = 0;
for(n=0;n<10;n++){
   if(blad[n]!=0){
      wiersz = 7*blad[n];
      for(x=0;x<3;x++){
      decimal += remacierz1[3*n+x]*modifier;
      modifier = modifier*2;
  }
 }
} 

int ups = decimal + wiersz;
printf("lokalizajca 70 bitowej: %d \n", ups);

if(remacierz[ups-1]==0) remacierz[ups-1]=1;
else remacierz[ups-1]=0;

printf("Poprawienie macierzy 70bitowej: ");
for(n=0; n<70; n++){
   printf("%d", remacierz[n]);
}

return 0;
}