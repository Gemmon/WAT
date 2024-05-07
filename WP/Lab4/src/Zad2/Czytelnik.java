package Zad2;


class Czytelnik extends Thread {
    private final Czytelnia czytelnia;
    private final int id;
    private final int nr_powtorzenia;

    public Czytelnik(Czytelnia czytelnia, int id, int nr_powtorzenia) {
        this.czytelnia = czytelnia;
        this.id = id;
        this.nr_powtorzenia = nr_powtorzenia;
    }

    @Override
    public void run() {
        try {
            for (int i = 1; i < 200; i++) {
                czytelnia.czytelnikWejdz(id, i);
                czytelnia.czytelnikWyjdz(id, i);
            }
        } catch (InterruptedException e) {
            return;
        }
    }
}
