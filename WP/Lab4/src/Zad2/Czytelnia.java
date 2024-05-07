package Zad2;

import java.util.Random;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;


class Czytelnia extends Thread {
    private int licz_czyt = 0;
    private int licz_pis = 0;
    private int licz_czytP = 0;
    private int licz_pisP = 0;
    private final ReentrantLock lock = new ReentrantLock();
    private final Condition czytelnicy = lock.newCondition();
    private final Condition pisarze = lock.newCondition();
    private final Random random = new Random();
    private boolean czyOstatnimBylCzytelnik = true;


    public void czytelnikWejdz(int id, int nr_powtorzenia) throws InterruptedException {


        lock.lock();
        try {
            System.out.println(">>>(1) [C-" + id + ", " + nr_powtorzenia + "] :: [licz_czyt=" + licz_czyt + ", licz_czyt_pocz=" + licz_czytP + ", licz_pis=" + licz_pis + ", licz_pis_pocz=" + licz_pisP + "]");
            if (licz_pis != 0) {
                if (licz_czytP < 6) {
                    licz_czytP++;
                }
            } else licz_czyt++;
            int time2 = random.nextInt(5) + 1;
            Thread.sleep(time2);
            pisarze.signal();
            czyOstatnimBylCzytelnik = true;
            System.out.println(">>>(2) [C-" + id + ", " + nr_powtorzenia + "] :: [licz_czyt=" + licz_czyt + ", licz_czyt_pocz=" + licz_czytP + ", licz_pis=" + licz_pis + ", licz_pis_pocz=" + licz_pisP + "]");
        } finally {
            lock.unlock();
        }
        int time = random.nextInt(11) + 5; // Losowy czas w czytelni
        Thread.sleep(time);
    }

    public void czytelnikWyjdz(int id, int nr_powtorzenia) throws InterruptedException {
        int time = random.nextInt(10) + 2;
        Thread.sleep(time);

        lock.lock();
        try {
            int time2 = random.nextInt(4) + 2;
            Thread.sleep(time2);

            System.out.println("<<<(1) [C-" + id + ", " + nr_powtorzenia + "] :: [licz_czyt=" + licz_czyt + ", licz_czyt_pocz=" + licz_czytP + ", licz_pis=" + licz_pis + ", licz_pis_pocz=" + licz_pisP + "]");
            if(licz_czyt != 0) licz_czyt--;
            System.out.println("<<<(2) [C-" + id + ", " + nr_powtorzenia + "] :: [licz_czyt=" + licz_czyt + ", licz_czyt_pocz=" + licz_czytP + ", licz_pis=" + licz_pis + ", licz_pis_pocz=" + licz_pisP + "]");

            czyOstatnimBylCzytelnik = false;
            pisarze.signal();
        } finally {
            lock.unlock();
        }
    }

    public void pisarzWejdz(int id, int nr_powtorzenia) throws InterruptedException {
        int time2 = random.nextInt(5) + 1;
        Thread.sleep(time2);
        lock.lock();
        try {
            int time1 = random.nextInt(4) + 2;
            Thread.sleep(time1);
            System.out.println("==>(1) [P-" + id + ", " + nr_powtorzenia + "] :: [licz_czyt=" + licz_czyt + ", licz_czyt_pocz=" + licz_czytP + ", licz_pis=" + licz_pis + ", licz_pis_pocz=" + licz_pisP + "]");

            if (licz_czyt != 0) {
                if (licz_pisP < 3) {
                    licz_pisP++;
                }
            }
            else if (licz_pis != 1) licz_pis++;
            czyOstatnimBylCzytelnik = false;
            System.out.println("==>(2) [P-" + id + ", " + nr_powtorzenia + "] :: [licz_czyt=" + licz_czyt + ", licz_czyt_pocz=" + licz_czytP + ", licz_pis=" + licz_pis + ", licz_pis_pocz=" + licz_pisP + "]");
        } finally {
            lock.unlock();
        }
        int time = random.nextInt(5) + 1; // Losowy czas w czytelni
        Thread.sleep(time);
    }

    public void pisarzWyjdz(int id, int nr_powtorzenia) {

        lock.lock();
        try {
            System.out.println("<==(2) [P-" + id + ", " + nr_powtorzenia + "] :: [licz_czyt=" + licz_czyt + ", licz_czyt_pocz=" + licz_czytP + ", licz_pis=" + licz_pis + ", licz_pis_pocz=" + licz_pisP + "]");
            if (licz_pis == 0) {
                licz_pisP--;
            }
            else licz_pis--;
            if(licz_pis == 0){
                licz_czyt = licz_czytP;
                licz_czytP = 0;
            }
            System.out.println("<==(2) [P-" + id + ", " + nr_powtorzenia + "] :: [licz_czyt=" + licz_czyt + ", licz_czyt_pocz=" + licz_czytP + ", licz_pis=" + licz_pis + ", licz_pis_pocz=" + licz_pisP + "]");
            czytelnicy.signalAll();
            pisarze.signal();
        } finally {
            lock.unlock();
        }
    }
}
