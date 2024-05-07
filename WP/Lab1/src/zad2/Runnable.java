package zad2;

public class Runnable implements java.lang.Runnable {
    private String nazwaWatku;

    public Runnable(String nazwa) {
        this.nazwaWatku = nazwa;
    }

    public void run() {
        for (int i = 1; i <= 10; i++) {
            System.out.println("Pozdrowienia z wątku " + nazwaWatku + " nr powtórzenia " + i);
            try {
                // Wstrzymanie wątku na losowy czas
                int czasOczekiwania = (int) (Math.random() * 100) + 100; // [100, 200)
                Thread.sleep(czasOczekiwania);
            } catch (Exception e) {
                System.out.println("Błąd: _" + e.getMessage());
            }
        }
    }
}
