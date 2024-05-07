package zad1;

import java.util.Random;
import java.util.concurrent.Semaphore;

public class Konsument extends Thread {
    static volatile int k;
    private Semaphore zajete;
    private Semaphore wolne;
    private Semaphore chron_k;
    private int idk;

    private int N;

    public Konsument(Semaphore zajete, Semaphore wolne, Semaphore chron_k, int idk, int N)
    {
        this.idk = idk;
        this.zajete = zajete;
        this.wolne = wolne;
        this.chron_k = chron_k;
        this. N = N;
    }

    public void run() {
        for (int i = 0; i <80 ; i++) {
            try {
                zajete.acquire();
                chron_k.acquire();
                String element = "[K-" + idk + ", " + i + ", " + k +"] :: " + Bufor.bufor[k];
                Random random = new Random();
                int time = random.nextInt(2) + 12;
                Thread.sleep(time);
                System.out.println(element);
                wolne.release();
                k = (k+1)%N;
                chron_k.release();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }


}
