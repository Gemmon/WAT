package zad3;

import java.util.Random;
import java.util.concurrent.locks.ReentrantLock;

public class Filozof extends Thread {
    private ReentrantLock dopusc;
    private ReentrantLock[] widelec;
    private int id;

    public Filozof(ReentrantLock dopusc, ReentrantLock[] widelec, int id) {
        this.dopusc = dopusc;
        this.widelec = widelec;
        this.id = id;
    }

    public void run() {
        for (int i = 1; i < 1000; i++) {
            try {
                //myslenie
                Random random = new Random();
                int time = random.nextInt(10) + 5;
                Thread.sleep(time);

                dopusc.lock();
                try {
                    widelec[id].lock();
                    widelec[(id + 1) % 5].lock();

                    int licznik = 4 - dopusc.getHoldCount();
                    System.out.println(">>>(1)[F-" + id + ", " + i + "] :: licz_fil_przy_stole= " + licznik + ", [w0=" +
                            widelec[0].getHoldCount() + ", w1=" +
                            widelec[1].getHoldCount() + ", w2=" +
                            widelec[2].getHoldCount() + ", w3=" +
                            widelec[3].getHoldCount() + ", w4=" +
                            widelec[4].getHoldCount() + "]");

                    //jedzenie
                    Random random2 = new Random();
                    int time2 = random2.nextInt(4) + 1;
                    Thread.sleep(time2);
                } finally {
                    widelec[id].unlock();
                    widelec[(id + 1) % 5].unlock();
                    dopusc.unlock();
                }

                int licznik = 4 - dopusc.getHoldCount();
                System.out.println("<<<(2)[F-" + id + ", " + i + "] :: licz_fil_przy_stole= " + licznik + ", [w0=" +
                        widelec[0].getHoldCount() + ", w1=" +
                        widelec[1].getHoldCount() + ", w2=" +
                        widelec[2].getHoldCount() + ", w3=" +
                        widelec[3].getHoldCount() + ", w4=" +
                        widelec[4].getHoldCount() + "]");

            } catch (InterruptedException e) {
                break;
            }
        }
    }
}
