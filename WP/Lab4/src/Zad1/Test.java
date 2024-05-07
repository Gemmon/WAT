package Zad1;

public class Test {
    public static void main(String[] args) {
        int N =5; // rozmiar bufora
        int m = 4; // liczba producentów
        int n = 5; // liczba konsumentów

        Konsument[] consumers = new Konsument[n];
        Producent[] producers = new Producent[m];

        for (int i = 0; i < n; i++) {
            consumers[i] = new Konsument(i, N);
        }

        for (int i = 0; i < m; i++) {
            producers[i] = new Producent(i, N);
        }

        for (int i = 0; i < n; i++) {
            consumers[i].start();
        }

        for (int i = 0; i < m; i++) {
            producers[i].start();
        }
    }
}