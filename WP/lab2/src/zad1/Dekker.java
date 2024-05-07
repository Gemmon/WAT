package zad1;

import java.util.Random;

class Dekker extends Thread {
    private int numer;
    private int powtorzenie;
    private boolean dzialanieSynchr;
    private volatile static boolean[] chce = {false, false};
    private volatile static int czyjaKolej = 1;

    public Dekker(int numer, int powtorzenie, boolean dzialanieSynchr) {
        this.numer = numer;
        this.powtorzenie = powtorzenie;
        this.dzialanieSynchr = dzialanieSynchr;
    }

    public void run() {
        for (int i = 0; i < powtorzenie; i++) {
            if (dzialanieSynchr) {
                dzialanieSynchr();
            } else {
                dzialanieNiesynchr();
            }
        }
    }

    public void dzialanieSynchr() {
        chce[czyjaKolej] = true;
        while (chce[1 - (czyjaKolej)]) {
            chce[czyjaKolej] = false;
            while (chce[1 - (czyjaKolej)]) {
                Thread.yield();
            }
            chce[czyjaKolej] = true;
        }

        // Critical section
        sekcjaKrytycznaWypisz();
        chce[czyjaKolej] = false;
    }

    public void dzialanieNiesynchr() {
        try {
            Thread.sleep((long) (Math.random() * 10) + 1); // Corrected syntax
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        sekcjaKrytycznaWypisz();
    }


    int nrPow=1;
    private void sekcjaKrytycznaWypisz() {
        String prefix = (numer == 1) ? "Dekker-1" : "Dekker-2";
        String separator = (numer == 1) ? "+" : "-";
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < 100; i++) {
            sb.append(separator);
        }
        System.out.println("Sekcja krytyczna wątku: " + prefix + " nr pow: " + nrPow + "\n " + sb.toString());
        nrPow++;

    }
}
