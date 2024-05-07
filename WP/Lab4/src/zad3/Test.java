package zad3;


import java.util.concurrent.locks.ReentrantLock;

public class Test {

    static volatile ReentrantLock dopusc = new ReentrantLock(true);

    public static void main(String[] args) throws InterruptedException {

        ReentrantLock[] widelec = new ReentrantLock[5];
        for (int i = 0; i < 5; i++) {
            widelec[i] = new ReentrantLock();
        }

        Thread[] tr1 = new Thread[5];
        for (int i = 0; i < 5; i++) {
            tr1[i] = new Filozof(dopusc, widelec, i);
        }

        for (int i = 0; i < 5; i++) {
            tr1[i].start();
        }

        //uspienie wątku test
        try {
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            ;
        }

        for (int i = 0; i < 5; i++) {
            tr1[i].interrupt();
        }

        for (int i = 0; i < 5; i++) {
            tr1[i].join();
        }
    }
}