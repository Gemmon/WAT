/*package zad4;

import zad1.MyThread;

public class MyThread2 {

    public MyThread2(String threadName) {
        this.threadName = threadName;
    }

    public void run() {

        Thread[] w = new MyThread1[3];
        for (int i = 0; i < w.length; i++) {
            w[i] = new MyThread1("" + i);
        }
        for (int i = 0; i < 3; i++) {
            w[i].start();
        }
        try {
            int sleepTime = random.nextInt(500) + 2500;
            Thread.sleep(sleepTime);
            System.out.println(threadName + " " + i + " :: spałem przez: " + sleepTime + " ms");
        } catch (InterruptedException e) {
            System.out.println(threadName + " " + i + " :: zostałem obudzony");
        }

    }
}
*/