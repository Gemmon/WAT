package zad3;

import java.util.Random;

public class Lamport extends Thread {
    private int watek;
    private int powtorzenie;
    private boolean synchroniczne;
    private volatile static boolean[] wybieranie = new boolean[5];
    private volatile static int[] ticket = new int[2];
    private char[] znaki = {'-', '+'};

    public Lamport(int watek, int powtorzenie, boolean synchroniczne) {
        this.watek = watek;
        this.powtorzenie = powtorzenie;
        this.synchroniczne = synchroniczne;
    }

    @Override
    public void run() {
        for (int i = 0; i < powtorzenie; i++) {
            if (synchroniczne) {
                synchroniczne();
            } else {
                unsynchroniczne();
            }
        }
    }

    private void ownWork() throws InterruptedException {
        Random random = new Random();
        int sleepTime = random.nextInt(10) + 1;
        Thread.sleep(sleepTime);
    }

    private void criticalSection(int repetition) {
        StringBuilder separator = new StringBuilder();
        for (int i = 0; i < 100; i++) {
            separator.append(znaki[watek]);
        }
        System.out.println("Sekcja krytyczna wątku: Lamport-" + watek + ", nr powt.= " + repetition);
        System.out.println(separator.toString());
    }

    private void unsynchroniczne() {
        for (int i = 1; i <= powtorzenie; i++) {
            try {
                ownWork();
                criticalSection(i);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    private synchronized void synchroniczne() {
        for (int i = 1; i <= powtorzenie; i++) {
            try {
                wybieranie[watek] = true;
                ticket[watek] = findMax() + 1;
                wybieranie[watek] = false;
                for (int j = 0; j < ticket.length; j++) {
                    while (wybieranie[j] && j != watek) {
                        wait(); // Czekaj dopóki inny wątek o wyższym priorytecie czeka
                    }
                    while ((ticket[j] != 0) && ((ticket[j] < ticket[watek]) || ((ticket[j] == ticket[watek]) && (j < watek)))) {
                        wait(); // Czekaj dopóki inny wątek o wyższym priorytecie czeka
                    }
                }
                ownWork();
                criticalSection(i);
                ticket[watek] = 0;
                notifyAll(); // Powiadom wszystkie wątki, które czekają
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    private int findMax() {
        int max = ticket[0];
        for (int i = 1; i < ticket.length; i++) {
            if (ticket[i] > max) {
                max = ticket[i];
            }
        }
        return max;
    }
}
