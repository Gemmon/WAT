package zad3;

import java.util.Random;
import java.util.concurrent.Semaphore;

public class Czytelnik extends Thread {

    private Semaphore wolne;

    private int id;

    public Czytelnik(Semaphore wolne, int id) {

        this.wolne = wolne;
        this.id = id;
    }


    public void run() {
        for (int i = 1; i < 50; i++) {
            try {

                //wlasne sprawy
                Random random = new Random();
                int time = random.nextInt(10) + 5;
                Thread.sleep(time);

                wolne.acquire();
                System.out.println(">>>[C-" + id + ", " + i + "]");
                //czytanie
                Random random2 = new Random();
                int time2 = random2.nextInt(4) + 1;
                Thread.sleep(time2);

                System.out.println("<<<[C-" + id + ", " + i + "]");
                wolne.release();


            }

            catch (InterruptedException e) {
                break;
            }

        }
    }
}
