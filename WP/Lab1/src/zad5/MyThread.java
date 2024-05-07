package zad5;

public class MyThread extends Thread {
    private Licznik licz;

    public MyThread(Licznik licz) {
        this.licz = licz;
    }

    public void run() {
        for (int i = 0; i < 5000000; i++) {
            licz.incNiesynch();
        }
    }
}

