package zad1;

public class MyThread extends Thread {
    public MyThread(String num) {
        super(num);
    }

    public void run() {
        for (int i = 1; i <= 10; i++) {
            System.out.println("Pozdrowienia z wątku " + getName() + " nr powtórzenia " + i);
            try {
                // Wstrzymanie wątku na losowy czas
                int czasOczekiwania = (int) (Math.random() * 100) + 100; // [100, 200)
                Thread.sleep(czasOczekiwania);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}