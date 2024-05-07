package zad3;

import java.util.Random;
import java.util.concurrent.Semaphore;

public class Pisarz extends Thread{
    private Semaphore wolne;
    private Semaphore pis;

    private int id;


    public Pisarz(Semaphore pis, Semaphore wolne, int id) {
        this.pis = pis;
        this.wolne = wolne;
        this.id = id;
    }


    public void run() {
        for(int i = 1; i<50; i++) {
            try {

                //sprawy wlasne
                Random random = new Random();
                int time = random.nextInt(10) + 5;
                Thread.sleep(time);

                pis.acquire();
                for(int j = 0; j<3; j++) {
                    wolne.acquire();
                }
                System.out.println("==>[P-" + id + ", " + i + "]");
                //pisanie
                Random random2 = new Random();
                int time2 = random2.nextInt(4) + 1;
                Thread.sleep(time2);

                System.out.println("<==[P-" + id + ", " + i + "]");
                for(int j = 0; j<3; j++) {
                    wolne.release();
                }
                pis.release();
            }

            catch (InterruptedException e) {
                break;
            }

        }

    }
}
