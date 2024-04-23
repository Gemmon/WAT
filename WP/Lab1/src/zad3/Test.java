package zad3;

public class Test {
    public static void main(String[] args) {
        Thread[] threads = new Thread[10];

        for (int i = 0; i < 10; i++) {

            Runnable runnable = new Runnable() {
                @Override
                public void run() {
                    for (int j = 1; j <= 10; j++) {
                        System.out.println("Pozdrowienia z wątku " + Thread.currentThread().getName() + " nr powtórzenia " + j);
                        try {
                            // Wstrzymanie wątku na losowy czas
                            int czasOczekiwania = (int) (Math.random() * 100) + 100; // [100, 200)
                            Thread.sleep(czasOczekiwania);
                        } catch (Exception e) {
                            System.out.println("Błąd: _" + e.getMessage());
                            break;
                        }
                    }
                }
            };

            threads[i] = new Thread(runnable, "" + i);
        }

        for (Thread thread : threads) {
            thread.start();
        }

        for (int i = 0; i < 10; i++) {
            try {
                threads[i].join();
            } catch (Exception e) {
                System.out.println("Błąd: _" + e.getMessage());
                break;
            }

        }

        System.out.println("Koniec");
    }
}

