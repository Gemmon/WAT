package zad3;

public class Test {
    public static void main(String[] args) {
        int repetitions = 100;
        boolean synchronizedExecution = true;

        for (int i = 1; i < 2; i++) {
            Lamport thread = new Lamport(i, repetitions, synchronizedExecution);
            thread.start();
        }
    }
}