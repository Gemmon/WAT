package zad2;

import java.util.concurrent.Semaphore;

public class Test {

    static volatile int cp = 0;
    static volatile int cc = 0;
    static volatile int pp = 0;
    static volatile int pc = 0;

    static volatile Semaphore pis = new Semaphore(0);
    static volatile Semaphore czyt = new Semaphore(0);
    static volatile Semaphore chron = new Semaphore(1);

    public static void main(String[] args) throws InterruptedException {


        Thread[] tr1 = new Thread[4];
        Thread[] tr2 = new Thread[2];

        for (int i = 0; i < 4; i++) {
        tr1[i] = new Czytelnik(czyt, pis, chron, i+1);}
        tr2[0] = new Pisarz(czyt, pis, chron, 1);
        tr2[1] = new Pisarz(czyt, pis, chron, 2);

        for(int i = 0; i<4; i++) {
            tr1[i].start();
        }

        for(int i = 0; i<2; i++) {
            tr2[i].start();
        }


        //uspienie wątku test
        try {
            Thread.sleep(5000);
            System.out.println("Przerwanie");
        } catch (InterruptedException e) {
            ;
        }

        for(int i = 0; i<4; i++) {
            tr1[i].interrupt();
        }

        for(int i = 0; i<2; i++) {
            tr2[i].interrupt();
        }


        for(int i = 0; i<4; i++) {
            tr1[i].join();
        }

        for(int i = 0; i<2; i++) {
            tr2[i].join();
        }
    }
}

