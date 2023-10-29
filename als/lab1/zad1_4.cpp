//============================================================================
// Zadanie 1_4  jezyk C++
//  Mno¿enie macierzy
//  WCY22IY1S1  Chrapowicz Krzysztof
//============================================================================

#include <iostream>
using namespace std;

int main() {
    int a[3][3] = {{1, 2, 3}, {3, 2, 1}, {5, 2, 3}};
    int b[3][3] = {{-1, 3, 1}, {-1, 2, 1}, {0, 2, 1}};
    int r[3][3];

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            r[i][j] = 0;
        }
    }

    for (int i = 0; i < 3; ++i) 
    {
        for (int j = 0; j < 3; ++j) 
        {
            for (int k = 0; k < 3; ++k) 
            {
                r[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    cout << "Wynik: " << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << r[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
