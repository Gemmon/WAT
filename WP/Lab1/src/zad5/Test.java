package zad5;

public class Test {
    public static void main(String[] args) {
        Licznik licz = new Licznik();
        Thread[] w = new MyThread[10];

        for (int i = 0; i < w.length; i++) {
            w[i] = new MyThread(licz);
        }

        for (int i = 0; i < 10; i++) {
            w[i].start();
        }

        for (int i = 0; i < 10; i++) {
            try {
                w[i].join();
            } catch (Exception e) {
                System.out.println("Błąd: _" + e.getMessage());
                break;
            }
        }

        // Wyświetlenie wyniku
        System.out.println("Licznik=" + licz.get());
    }
}