package Zad1;

import java.util.Random;

class Konsument extends Thread {
    private final int idk;
    private final int N;

    public Konsument(int idk, int N) {
        this.idk = idk;
        this.N = N;
    }

    public void run() {
        Random random = new Random();
        for (int i = 0; i < 80; i++) {
            try {
                Bufor.lock.lock();
                while (Bufor.bufor[i % N] == null) {
                    Bufor.empty.await();
                }
                String element = "[K-" + idk + ", " + i + "] >> " + Bufor.bufor[i % N];
                int time = random.nextInt(10) + 2;
                Thread.sleep(time);
                System.out.println(element);
                Bufor.bufor[i % N] = null;
                Bufor.full.signal();
            } catch (InterruptedException e) {
                e.printStackTrace();
            } finally {
                Bufor.lock.unlock();
            }
        }
    }
}
