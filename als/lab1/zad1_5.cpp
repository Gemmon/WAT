//============================================================================
// Zadanie 1_5  jezyk C++
//  Najwiêksza i najmniejsza wartoœæ
//  WCY22IY1S1  Chrapowicz Krzysztof
//============================================================================

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
	int n = 0;

    vector<int> X;
    srand(time(0)); 
 
    while(n < 10) {
        int liczba = rand() % 20;
        X.push_back(liczba);

        cout << liczba << " ";
        if ((n + 1) % 10 == 0) {
        }
        n++;
    }
    cout << endl;

    int maxWartosc = X[0];
    int minWartosc = X[0];

    for (int i = 1; i < 10; ++i) {
        if (X[i] > maxWartosc) {
            maxWartosc = X[i];
        }
        if (X[i] < minWartosc) {
            minWartosc = X[i];
        }
    }

    cout << "Maksymalna wartosc: " << maxWartosc << endl;
    cout << "Minimalna wartosc: " << minWartosc << endl;

    return 0;
}
