package zad2;


public class Test {
    public static void main(String[] args) {
        int powtorzenie = 100;
        boolean dzialanieSynchr = true;

        Peterson thread1 = new Peterson(1, powtorzenie, dzialanieSynchr);
        Peterson thread2 = new Peterson(2, powtorzenie, dzialanieSynchr);

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