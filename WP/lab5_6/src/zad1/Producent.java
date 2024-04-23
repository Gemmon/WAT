package zad1;

import java.util.concurrent.Semaphore;
import java.util.Random;
public class Producent extends Thread {
    static volatile int j;
    private Semaphore zajete;
    private Semaphore wolne;
    private Semaphore chron_j;
    private int idp;

    private int N;
    public Producent(Semaphore zajete, Semaphore wolne, Semaphore chron_j, int idp, int N) {
        this.zajete = zajete;
        this.wolne = wolne;
        this.chron_j = chron_j;
        this.idp = idp;
        this.N = N;
    }

    public void run() {
        for (int i = 0; i < 100; i++) {
            try {
                //produkcja elementu
                Random random = new Random();
                int time = random.nextInt(10) + 1;
                Thread.sleep(time);
                Random random2 = new Random();
                int wartosc = random2.nextInt(99);
                wolne.acquire();
                chron_j.acquire();
                //zapis elementu do bufora
                String element = "Dana=[P-" + idp + ", " + i + ", " + j + ", " + wartosc + "]";
                Bufor.bufor[j] = element;
                zajete.release();
                j = (j+1)%N;
                chron_j.release();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

}