package zad1;

public class Test {
    public static void main(String[] args) {
        Thread[] w = new Thread[10];
        for (int i = 0; i < w.length; i++) {
            w[i] = new MyThread("" + i);
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

        // Wypisanie komunikatu "Koniec"
        System.out.println("Koniec");
    }
}

