package zad2;

import java.util.Random;
import java.util.concurrent.Semaphore;

public class Czytelnik extends Thread {
    private Semaphore czyt;
    private Semaphore pis;
    private Semaphore chron;

    private int id;

    public Czytelnik(Semaphore czyt, Semaphore pis, Semaphore chron, int id) {
        this.czyt = czyt;
        this.pis = pis;
        this.chron = chron;
        this.id = id;
    }

    public void run() {
        for (int i = 1; i < 1500; i++) {
            try {
                //wlasne sprawy
                Random random = new Random();
                int time = random.nextInt(10) + 5;
                Thread.sleep(time);

                chron.acquire();
                System.out.println(">>>(1) [C-" + id + ", " + i + "] :: [licz_czyt=" + Test.cc + ", licz_czyt_pocz=" + Test.cp + ", licz_pis=" + Test.pc + ", licz_pis_pocz=" + Test.pp);

                if (Test.pp + Test.pc == 0) {
                    Test.cc = Test.cc + 1;
                    czyt.release();
                } else {
                    Test.cp = Test.cp + 1;
                }
                System.out.println(">>>(2) [C-" + id + ", " + i + "] :: [licz_czyt=" + Test.cc + ", licz_czyt_pocz=" + Test.cp + ", licz_pis=" + Test.pc + ", licz_pis_pocz=" + Test.pp);
                chron.release();

                czyt.acquire();

                //czytanie
                Random random2 = new Random();
                int time2 = random2.nextInt(4) + 1;
                Thread.sleep(time2);


                chron.acquire();
                System.out.println("<<<(1) [C-" + id + ", " + i + "] :: [licz_czyt=" + Test.cc + ", licz_czyt_pocz=" + Test.cp + ", licz_pis=" + Test.pc + ", licz_pis_pocz=" + Test.pp);
                Test.cc = Test.cc - 1;
                if (Test.cc == 0) {
                    if (Test.pp > 0) {
                        Test.pc = 1;
                        Test.pp = Test.pp - 1;
                        pis.release();
                    }
                }
                System.out.println("<<<(2) [C-" + id + ", " + i + "] :: [licz_czyt=" + Test.cc + ", licz_czyt_pocz=" + Test.cp + ", licz_pis=" + Test.pc + ", licz_pis_pocz=" + Test.pp);
                chron.release();
            }

            catch (InterruptedException e) {
                break;
            }

        }
    }
}
