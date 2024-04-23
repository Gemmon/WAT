package zad4;

import java.util.concurrent.Semaphore;

public class Test {
    public static void main(String[] args) {
        boolean synchronizedExecution = true; // Change to false for unsynchronized execution

        Semaphore semaphore = new Semaphore(1);

        Semafor[] threads = new Semafor[5];

        for (int i = 0; i < 5; i++) {
            threads[i] = new Semafor(synchronizedExecution, i + 1, semaphore);
            threads[i].start();
        }
    }
}