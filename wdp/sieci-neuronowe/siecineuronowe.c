#include<stdio.h>

//wektory

#define numInputs


void print(int n,int k,int tab[][3]){
   for(int i=0 ; i<n ; i++ ){
       for(int j=0 ; j<k ;j++ ){

        printf("%d ", tab[i][j]);
        }
   }
}
void print1( int n, int tab[]){
   for(int i=0;i<n;i++){
  
   printf("%d ",tab[i]);
   }
}

void first(int vector[],int x[],int bias[],int w[][3])
{
    int mua;
    for(int i=0;i<2;i++)
    {
        mua=0;
        for(int j=0;j<3;j++)
        {
            mua += w[i][j]*x[j];
        }
        vector[i] = mua + bias[i];
    }
}

void second(int vector[],int x[],int bias[],int w[][2])
{
    int mua;
    for(int i=0;i<3;i++)
    {
        mua=0;
        for(int j=0;j<2;j++)
        {
            mua += w[i][j]*x[j];
        }
        vector[i] = mua + bias[i];
    }}


void y(int vector[],int x[],int b[],int w[]){
    
    int mua = 0;
    for(int i=0;i<2;i++){
        mua += w[i]*x[i];
    }
    vector[0] = mua + b[0];
}

void f_akt(int o[],int k)
{
    for(int i=0;i<k;i++)
    {
        o[i]=o[i]*2;
    }
}


int main(){
    
    //
    int x[3] = {1,2,3};
    int y[1] = {1};
    int vector1[2];
    int vector2[3];
    int weigth1[2][3]={{1,4,2},{0,2,5}};
    int weight2[3][2]={{1,1},{4,2},{0,3}};
    int weigth3[2]={1,2};
    int b1[3]={0,1,1};
    int b2[2]={1,2};
    int b3[1]={1};
   
   printf("wektory x: ");
   print1(3, x);
   printf("\nFunkcja: y=2x\n");
   first(vector1,x,b1,weigth1);
   print1(3, vector1);
   




}
