package zad1;


public class Test {
    public static void main(String[] args) {
        int powtorzenie = 100;
        boolean dzialanieSynchr = true;

        Dekker thread1 = new Dekker(1, powtorzenie, dzialanieSynchr);
        Dekker thread2 = new Dekker(2, powtorzenie, dzialanieSynchr);

        thread1.start();
        thread2.start();

        try {
            thread1.join();
            thread2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

    }
}