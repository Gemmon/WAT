//============================================================================
// Zadanie 1_2  jezyk C++
//  Fibonacci
//  WCY22IY1S1  Chrapowicz Krzysztof
//============================================================================

#include<iostream>
using namespace std;


int fiboR(int n) 
    {
    if(n <= 1) 
	{
        return n;
    } 
	else 
	{
        return (fiboR(n - 1) + fiboR(n - 2) );
    }
}

int fiboI(int n)
{
    if(n<=2)
        return 1;
    else{

        int wynik;
        int fib1=1;
        int fib2=1;

        for(int i=3;i<=n;i++)
		{
            wynik = fib1 + fib2;
            fib1 = fib2;
            fib2 = wynik;
        }

        return wynik;
    }
}

int main() {
    int n;
    cout << "Podaj n: ";
    cin >> n;

    if(n < 0) 
	{
        cout << "Blad" << endl;
    } 
	else 
	{
		int wynik = 0;
		cout << " Wynik rekurencyjnie:  " << wynik;
		for(int i=1; i < n; i++){
		
        wynik = fiboR(i);
        cout << " " << wynik;
    }
}

  if(n < 0) 
	{
        cout << "Blad" << endl;
    } 
	else 
	{
		int wynik = 0;
		cout << " Wynik iteracyjnie:  " << wynik;
		for(int i=1; i < n; i++){
		
        wynik = fiboI(i);
        cout << " " << wynik;
    }
}


    return 0;
}
