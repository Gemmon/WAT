/*
package zad4;

import java.util.Random;

// Klasa reprezentująca wątek
class MyThread1 extends Thread {
    String threadName;

    public MyThread1(String threadName) {
        this.threadName = threadName;
    }

    public void run() {
        Random random = new Random();
        for (int i = 1; i <= 1000; i++) {
            try {

                int sleepTime = random.nextInt(600) + 500;
                Thread.sleep(sleepTime);
                System.out.println(threadName + " " + i + " :: spałem przez: " + sleepTime + " ms");
            } catch (InterruptedException e) {
                System.out.println(threadName + " " + i + " :: zostałem obudzony");
            }
        }
        System.out.println(threadName + " - KONIEC");
    }
}
*/