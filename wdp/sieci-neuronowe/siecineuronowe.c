#include<stdio.h>

//wektory

#define numInputs


void print(int n,int k,int tab[][3]){
   for(int i=0 ; i<n ; i++ ){
       for(int j=0 ; j<k ;j++ ){

        printf("%d\t", tab[i][j]);
        }
   }
}
void print1(int tab[], int n){
   for(int i=0;i<n;i++){
  
   printf("%d\t",tab[i]);
   }
}

void first(int vector[],int x[],int bias[],int w[][2])
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

void second(int vector[],int x[],int bias[],int w[][3])
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

int main(){
    
    //
    int x[3] = {1,2,3};
    int y[1] = {1};
    int vector1[2];





}