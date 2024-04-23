package zad4;

import java.util.Random;
import java.util.concurrent.Semaphore;

class Semafor extends Thread {
    private int nrPowt;
    private boolean synchronizedExecution;
    private final char[] characters = {'/', '*', ';', ',', '}'};
    private final Random random = new Random();
    private int threadNumber;
    private Semaphore semaphore;

    public Semafor(boolean synchronizedExecution, int threadNumber, Semaphore semaphore) {
        this.synchronizedExecution = synchronizedExecution;
        this.threadNumber = threadNumber;
        this.semaphore = semaphore;
        this.nrPowt = nrPowt;
    }

    private void sprawyWlasne() {
        try {
            Thread.sleep(random.nextInt(10) + 1);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    private synchronized void dzialanieSynchr1(int nrPowt) {
        sprawyWlasne();
        sekcjaKrytyczna(nrPowt);
    }

    private synchronized void dzialanieSynchr2(int nrPowt) {
        sprawyWlasne();
        sekcjaKrytyczna(nrPowt);
    }

    private void dzialanieNiesynchr(int nrPowt) {
        sprawyWlasne();
        sekcjaKrytyczna(nrPowt);
    }

    private void sekcjaKrytyczna(int nrPowt) {
        if (!synchronizedExecution) {

            System.out.println("Sekcja krytyczna wątku: Sem-" + threadNumber + ", nr powt.= " + nrPowt);
            for (int i = 0; i < 100; i++) {
                if (i % 2 == 0)
                    System.out.print(characters[threadNumber - 1]); // Wybór znaku z tablicy characters
            }
            System.out.println();
        } else {
            try {
                semaphore.acquire();

                System.out.println("Sekcja krytyczna wątku: Sem-" + threadNumber + ", nr powt.= " + nrPowt);
                for (int i = 0; i < 100; i++) {
                    System.out.print(characters[threadNumber - 1]); // Wybór znaku z tablicy characters
                }
                System.out.println();
                semaphore.release();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public void run() {
        for (int i = 0; i < 100; i++) {
            nrPowt++;
            if (!synchronizedExecution) {
                dzialanieNiesynchr(i + 1);
            } else {
                if (threadNumber % 2 == 0) {
                    dzialanieSynchr1(i + 1);
                } else {
                    dzialanieSynchr2(i + 1);
                }
            }
        }
    }
}

