package zad1;

import java.util.concurrent.Semaphore;

public class Test {

    public static void main(String[] args) {
        int N = 10; //rozmiar bufora
        Semaphore zajete = new Semaphore(0);
        Semaphore wolne = new Semaphore(N);
        Semaphore chron_j = new Semaphore(1);
        Semaphore chron_k = new Semaphore(1);
        int j = 1;
        int k = 1;

        Thread[] tr1 = new Thread[4];
        Thread[] tr2 = new Thread[5];
        for (int i = 0; i < 4; i++) {
            tr1[i] = new Producent(zajete, wolne, chron_j, i, N);
        }
        for (int i = 0; i < 5; i++) {
        tr2[i] = new Konsument(zajete, wolne, chron_k, i, N);
        }

        for (int i = 0; i < 4; i++) {
            tr1[i].start();
        }
        for (int i = 0; i < 5; i++) {
            tr2[i].start();
        }

        try {
            for (int i = 0; i < 4; i++) {
                tr1[i].join();
            }

            for (int i = 0; i < 5; i++) {
                tr2[i].join();
            }

        } catch (InterruptedException e) {
        }
    }
}