package Zad1;

import java.util.Random;


class Producent extends Thread {
    private final int idp;
    private final int N;

    public Producent(int idp, int N) {
        this.idp = idp;
        this.N = N;
    }

    public void run() {
        Random random = new Random();
        for (int i = 0; i < 100; i++) {
            try {
                Bufor.lock.lock();
                while (Bufor.bufor[i % N] != null) {
                    Bufor.full.await();
                }
                int wartosc = random.nextInt(100);
                String element = "Dana=[P-" + idp + ", " + i + ", " + wartosc + "]";
               Bufor.bufor[i % N] = element;
                Bufor.empty.signal();
            } catch (InterruptedException e) {
                e.printStackTrace();
            } finally {
                Bufor.lock.unlock();
            }
        }
    }
}
