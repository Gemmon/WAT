package zad5;

public class Licznik {
    private long c = 0;

    public void incNiesynch() {
        c++;
    }

    public long get() {
        return c;
    }

}

