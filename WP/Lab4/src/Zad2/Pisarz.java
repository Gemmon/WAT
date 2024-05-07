package Zad2;

class Pisarz extends Thread {
    private final Czytelnia czytelnia;
    private final int id;
    private final int nr_powtorzenia;

    public Pisarz(Czytelnia czytelnia, int id, int nr_powtorzenia) {
        this.czytelnia = czytelnia;
        this.id = id;
        this.nr_powtorzenia = nr_powtorzenia;
    }

    @Override
    public void run() {
        try {
            for (int i = 1; i < 150; i++) {
                czytelnia.pisarzWejdz(id, i);
                // Pisanie...
                czytelnia.pisarzWyjdz(id, i);
            }
        } catch (InterruptedException e) {
            return;
        }
    }
}
