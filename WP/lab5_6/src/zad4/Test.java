package zad4;

import java.util.concurrent.Semaphore;

public class Test {

    static volatile Semaphore dopusc = new Semaphore(4);

    public static void main(String[] args) throws InterruptedException {

        Semaphore[] widelec = new Semaphore[5];
        for (int i = 0; i < 5; i++) {
            widelec[i] = new Semaphore(1);}

        Thread[] tr1 = new Thread[5];
        for (int i = 0; i < 5; i++) {
            tr1[i] = new Filozof(dopusc, widelec, i);}


        for(int i = 0; i<5; i++) {
            tr1[i].start();
        }

        //uspienie wątku test
        try {
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            ;
        }

        for(int i = 0; i<5; i++) {
            tr1[i].interrupt();
        }


        for(int i = 0; i<5; i++) {
            tr1[i].join();
        }
    }
}
