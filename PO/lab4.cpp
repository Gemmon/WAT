#include<iostream>
using namespace std;


class SklepSpozywczy{
    ProduktSpozywczy* produktyNaStanie[1000];
    int akutalnaLiczbaProduktow;

    public:

    void dodajNaStan( ProduktSpozywczy* produkt);

    void zdejmijZeStanu(ProduktSpozywczy* produkt);

    ProduktSpozywczy* znajdzProdukt( string rodzaj, string nazwa);

    void wyswietlProdukty();

    SklepSpozywczy();
};

class ProduktSpozywczy{
    protected:
    string rodzaj;
    string nazwa;
    double cena;
    
    public:
    string getRodzaj();
    string getNazwa();
    double getCena();
};

class Pieczywo{
    double waga;

    public:
    string getRodzaj();
    string getNazwa();
    double getCena();
    double getWaga();

    Pieczywo(string rodzaj, string nazwa, double cena, double waga);

};

class Pracownik{
    string imie;
    string nazwisko;
    SklepSpozywczy* sklep;

    public:
    string getImie();
    string getNazwisko();
    SklepSpozywczy* getSklep();
    
    void setSklep(SklepSpozywczy* sklep);

    Pracownik(string imie, string sklep, SklepSpozywczy* = NULL);

};

