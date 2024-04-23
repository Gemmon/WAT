package Zad2;


public class Test {
    public static void main(String[] args) {
        Czytelnia czytelnia = new Czytelnia();

        Thread[] czytelnicy = new Thread[4];
        Thread[] pisarze = new Thread[2];

        for (int i = 0; i < 2; i++) {
            pisarze[i] = new Pisarz(czytelnia, i + 1, 1);
        }
        for (int i = 0; i < 4; i++) {
            czytelnicy[i] = new Czytelnik(czytelnia, i + 1, 1);
        }


        for (Thread t : czytelnicy) {
            t.start();
        }

        for (Thread t : pisarze) {
            t.start();
        }

        try {
            Thread.sleep(5000);
            System.out.println("Przerwanie");
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        for (Thread t : czytelnicy) {
            t.interrupt();
        }

        for (Thread t : pisarze) {
            t.interrupt();
        }

        for (Thread t : czytelnicy) {
            try {
                t.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        for (Thread t : pisarze) {
            try {
                t.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
