package zad2;

public class Test {
    public static void main(String[] args) {
        Thread[] w = new Thread[10];
        for (int i = 0; i < 10; i++) {
            Runnable runnable = new Runnable("" + i);
            w[i] = new Thread(runnable, "" + i);
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
