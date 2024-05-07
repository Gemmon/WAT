package zad3;


import java.util.concurrent.Semaphore;

public class Test {

    static volatile Semaphore pis = new Semaphore(1);
    static volatile Semaphore wolne = new Semaphore(3);

    public static void main(String[] args) throws InterruptedException {

        Thread[] tr1 = new Thread[5];
        Thread[] tr2 = new Thread[2];
        for (int i = 0; i < 5; i++) {
        tr1[i] = new Czytelnik(wolne, i+1);}
        tr2[0] = new Pisarz(pis, wolne, 1);
        tr2[1] = new Pisarz(pis, wolne, 2);

        for(int i = 0; i<5; i++) {
            tr1[i].start();
        }

        for(int i = 0; i<2; i++) {
            tr2[i].start();
        }


        for(int i = 0; i<5; i++) {
            tr1[i].join();
        }

        for(int i = 0; i<2; i++) {
            tr2[i].join();
        }
    }
}

