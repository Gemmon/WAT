//============================================================================
// Zadanie 1_1  jezyk C++
//  Silnia 
//  WCY22IY1S1  Chrapowicz Krzysztof
//============================================================================

#include <iostream>
#include <cstdio>
using namespace std;

int silnia(int n) {
    if (n < 0) {
        return 0;
    } else if (n == 0) {
        return 1;
    } else {
        return n * silnia(n - 1);
    }
}


int main()
{
    int n;
    int silniaI = 1;
    cout <<"Give n: "<< endl;
    scanf("%d", &n);
    
    if(n < 0)
	{
     silniaI = 0;
	}
	else
	{
     for(int i = 1; i <= n; i++)
	  {
            silniaI *= i;
      }
    }
    
	cout<<"Silnia iteracyjnie: "<< silniaI<<endl;
	
	
    int wynik = silnia(n);
   
    cout << "Silnia rekurencyjnie: "<< wynik <<endl;

    
  return 0;   
}

