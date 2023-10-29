//============================================================================
// Zadanie 1_3  jezyk C++
//  Wielomian II stopnia
//  WCY22IY1S1  Chrapowicz Krzysztof
//============================================================================
#include <iostream>

using namespace std;

int klasy(int a0, int a1, int a2, int x )
{
    int w;
    w = a2*x*x;
    w = w + a1*x;
    w = w + a0; 
    return w;
}

int horner(int a0, int a1, int a2, int x )
{
    int w;
    w = a2*x+a1;
    w = w*x + a0; 
    return w;
}

int main()
{

    int a2, a1, a0, x;
    cout<< "Podaj liczby a0 a1 a2 x (odzielone spacja albo enterem): "<< endl;
    cin >> a0 >> a1 >> a2 >> x;

    cout<< "Wielomian klasycza: " << klasy(a0,a1,a2,x) << " Wielomian hornerem: " << horner(a0,a1,a2,x) << endl;
    return 0;
}
