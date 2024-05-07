package zad4;

import java.util.Random;
import java.util.concurrent.Semaphore;

public class Filozof extends Thread{
    private Semaphore dopusc;
    private Semaphore[] widelec;
    private int id;

    public Filozof(Semaphore dopusc, Semaphore[] widelec, int id) {
        this.dopusc = dopusc;
        this.widelec = widelec;
        this.id = id;
    }

    public void run() {
        for(int i = 1; i<1000; i++) {
            try {
                //myslenie
                Random random = new Random();
                int time = random.nextInt(10) + 5;
                Thread.sleep(time);

                dopusc.acquire();
                widelec[id].acquire();
                widelec[(id+1)%5].acquire();
                int licznik = 4 - dopusc.availablePermits();
                System.out.println(">>>[F-" + id + ", " + i + "] :: licz_fil_przy_stole= " + licznik + ", [w0=" +
                        widelec[0].availablePermits() + ", w1="  +
                        widelec[1].availablePermits() + ", w2=" +
                        widelec[2].availablePermits() + ", w3=" +
                        widelec[3].availablePermits() + ", w4=" +
                        widelec[4].availablePermits() + "]");


                //jedzenie
                Random random2 = new Random();
                int time2 = random2.nextInt(4) + 1;
                Thread.sleep(time2);

                widelec[id].release();
                widelec[(id+1)%5].release();
                dopusc.release();
                licznik = 4 - dopusc.availablePermits();
                System.out.println("<<<[F-" + id + ", " + i + "] :: licz_fil_przy_stole= " + licznik + ", [w0=" +
                        widelec[0].availablePermits() + ", w1="  +
                        widelec[1].availablePermits() + ", w2=" +
                        widelec[2].availablePermits() + ", w3=" +
                        widelec[3].availablePermits() + ", w4=" +
                        widelec[4].availablePermits() + "]");

            } catch (InterruptedException e) {
                break;
            }
        }
    }
}
