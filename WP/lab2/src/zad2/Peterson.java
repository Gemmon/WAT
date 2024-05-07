package zad2;

import java.util.Random;

class Peterson extends Thread {
    private int numer;
    private int powtorzenie;
    private boolean dzialanieSynchr;
    private volatile static boolean[] chce = {false, false};
    private volatile static int czyjaKolej = 1;

    public Peterson(int numer, int powtorzenie, boolean dzialanieSynchr) {
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
        chce[numer- 1] = true;
        czyjaKolej = 1 - (numer- 1);
        while (chce[1 - (numer- 1)] && czyjaKolej == 1 - (numer- 1)) {
            Thread.yield(); // Let other threads run while waiting
        }

        // Critical section
        sekcjaKrytycznaWypisz();
        chce[numer- 1] = false;
    }

    public void dzialanieNiesynchr() {
        chce[numer - 1] = true;
        while (chce[1 - (numer - 1)]) {
            chce[numer - 1] = false;
            while (chce[1 - (numer - 1)]) {
                Thread.yield();
            }
            chce[numer - 1] = true;
        }

        sekcjaKrytycznaWypisz();
        chce[numer - 1] = false;
    }
    int nrPow=1;
    private void sekcjaKrytycznaWypisz() {
        String prefix = (numer == 1) ? "Peterson-1" : "Peterson-2";
        String separator = (numer == 1) ? "+" : "-";
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < 100; i++) {
            sb.append(separator);
        }
        System.out.println("Sekcja krytyczna wątku: " + prefix + " nr pow: " + nrPow + "\n " + sb.toString());
        nrPow++;

    }
}
