#include<iostream>
#include<string>
using namespace std;

class ProduktSpozywczy {
protected:
    string rodzaj;
    string nazwa;
    double cena;

public:
    virtual string getRodzaj() = 0; // Make it a pure virtual function
    virtual string getNazwa() = 0;
    virtual double getCena() = 0;
};

class SklepSpozywczy {
    ProduktSpozywczy* produktyNaStanie[1000];
    int akutalnaLiczbaProduktow;

public:
    void dodajNaStan(ProduktSpozywczy* produkt) {
        if (akutalnaLiczbaProduktow < 1000) {
            produktyNaStanie[akutalnaLiczbaProduktow++] = produkt;
            cout << "Produkt dodany do stanu: "<< produkt->getNazwa()<< endl;
        }
        else {
            cout << "Stan sklepu jest peĹ‚ny, nie moĹĽna dodaÄ‡ wiÄ™cej produktĂłw." << endl;
        }
    }

    void zdejmijZeStanu(ProduktSpozywczy* produkt) {
        for (int i = 0; i < akutalnaLiczbaProduktow; ++i) {
            if (produktyNaStanie[i] == produkt) {
                for (int j = i; j < akutalnaLiczbaProduktow - 1; ++j) {
                    produktyNaStanie[j] = produktyNaStanie[j + 1];
                }
                produktyNaStanie[--akutalnaLiczbaProduktow] = nullptr;
                cout << "Produkt zdjety ze stanu: "<< produkt->getNazwa()<< endl;
                return;
            }
        }
        cout << "Podany produkt nie znajduje siÄ™ na stanie sklepu." << endl;
    }

    ProduktSpozywczy* znajdzProdukt(string rodzaj, string nazwa) {
        for (int i = 0; i < akutalnaLiczbaProduktow; ++i) {
            if (produktyNaStanie[i]->getRodzaj() == rodzaj && produktyNaStanie[i]->getNazwa() == nazwa) {
                return produktyNaStanie[i];
            }
        }
        return NULL;
    }

    void wyswietlProdukty() {
        cout << "Produkty na stanie sklepu: {" << endl;
        for (int i = 0; i < akutalnaLiczbaProduktow; ++i) {
            cout << "Rodzaj: " << produktyNaStanie[i]->getRodzaj() << ", Nazwa: " << produktyNaStanie[i]->getNazwa() << ", Cena: " << produktyNaStanie[i]->getCena() << endl;
        }
        cout << " }" << endl;
    }

    SklepSpozywczy() {
        akutalnaLiczbaProduktow = 0;
        for (int i = 0; i < 1000; ++i) {
            produktyNaStanie[i] = nullptr;
        }
    }
};

class Pieczywo : public ProduktSpozywczy {
    double waga;

public:
    string getRodzaj() override { return rodzaj; }
    string getNazwa() override { return nazwa; }
    double getCena() override { return cena; }
    double getWaga() { return waga; }

    Pieczywo(string rodzaj, string nazwa, double cena, double waga)
        : waga(waga) {
        this->rodzaj = rodzaj;
        this->nazwa = nazwa;
        this->cena = cena;
    }
};

class Woda : public ProduktSpozywczy {
    int pojemnosc;

public:
    string getRodzaj() override { return rodzaj; }
    string getNazwa() override { return nazwa; }
    double getCena() override { return cena; }
    int getPojemnosc() { return pojemnosc; }

    Woda(string rodzaj, string nazwa, double cena, int pojemnosc)
        : pojemnosc(pojemnosc) {
        this->rodzaj = rodzaj;
        this->nazwa = nazwa;
        this->cena = cena;
    }
};

class Piwo : public ProduktSpozywczy {
    double procentAlkoholu;

public:
    string getRodzaj() override { return rodzaj; }
    string getNazwa() override { return nazwa; }
    double getCena() override { return cena; }
    double getPorcentAlkoholu() { return procentAlkoholu; }

    Piwo(string rodzaj, string nazwa, double cena, double procentAlkoholu)
        : procentAlkoholu(procentAlkoholu) {
        this->rodzaj = rodzaj;
        this->nazwa = nazwa;
        this->cena = cena;
    }
};

class Pracownik {
    string imie;
    string nazwisko;
    SklepSpozywczy* sklep;

public:
    string getImie() { return imie; }
    string getNazwisko() { return nazwisko; }
    SklepSpozywczy* getSklep() { return sklep; }

    void setSklep(SklepSpozywczy* sklep) {
        this->sklep = sklep;
    }

    Pracownik(string imie, string nazwisko, SklepSpozywczy* sklep = nullptr)
        : imie(imie), nazwisko(nazwisko), sklep(sklep) {}
};

class Sprzedawca : protected Pracownik {
    string nrKsiazkiSanepidu;

public:
    string getNrKsiazkiSanepidu() { return nrKsiazkiSanepidu; }

    void setNrKsiazkiSanepidu(string nrKsiazki) {
        nrKsiazkiSanepidu = nrKsiazki;
    }

   void sprzedajProdukt(string rodzaj, string nazwa) {
    ProduktSpozywczy* produkt = getSklep()->znajdzProdukt(rodzaj, nazwa);
    if (produkt != nullptr) {
        cout << "Produkt sprzedany: " << produkt->getNazwa() << ", Cena: " << produkt->getCena() << endl;
        getSklep()->zdejmijZeStanu(produkt);
    }
    else {
        cout << "Produkt o podanych parametrach nie istnieje w sklepie." << endl;
    }
}


    Sprzedawca(string imie, string nazwisko, SklepSpozywczy* sklep = nullptr, string nrKsiazkiSanepidu = "")
        : Pracownik(imie, nazwisko, sklep), nrKsiazkiSanepidu(nrKsiazkiSanepidu) {}
};

class Zaopatrzeniowiec : public Pracownik {
    ProduktSpozywczy* produktyNaPaca[100];
    int akutalnaLiczbaProduktow;

public:
    void zaladujProduktNaPake(ProduktSpozywczy* produkt) {
        if (akutalnaLiczbaProduktow < 100) {
            produktyNaPaca[akutalnaLiczbaProduktow++] = produkt;
            cout << "Produkt zaladowany: " << produkt->getNazwa()<< endl;
        }
        else {
            cout << "Pacja jest pelna, nie mozna zaladowaÄ‡ wiecej produktow." << endl;
        }
    }

    void dostarczWszystkieProdukty() {
        cout << "Dostarczono wszystkie produkty na pace." << endl;
        akutalnaLiczbaProduktow = 0;
    }

    Zaopatrzeniowiec(string imie, string nazwisko, SklepSpozywczy* sklep = nullptr)
        : Pracownik(imie, nazwisko, sklep), akutalnaLiczbaProduktow(0) {
        for (int i = 0; i < 100; ++i) {
            produktyNaPaca[i] = nullptr;
        }
    }
};


int main() {

    SklepSpozywczy sklep;
    Zaopatrzeniowiec zaopatrzeniowiec("Jan", "Kowalski", &sklep);
    Sprzedawca sprzedawca("Anna", "Nowak", &sklep, "123456");
    Pracownik pracownik("Adam", "Nowak", &sklep);

    Pieczywo pieczywo("Chleb", "Razowy", 2.5, 0.5);
    Woda woda("Napoj", "Woda mineralna", 1.0, 500);
    Piwo piwo("Alkohol", "Piwo", 3.0, 5.0);

    sklep.dodajNaStan(&pieczywo);
    sklep.dodajNaStan(&woda);
    sklep.dodajNaStan(&piwo);

    sklep.wyswietlProdukty();

    sprzedawca.sprzedajProdukt("Alkohol", "Piwo");

    zaopatrzeniowiec.zaladujProduktNaPake(&pieczywo);
    zaopatrzeniowiec.zaladujProduktNaPake(&woda);

    zaopatrzeniowiec.dostarczWszystkieProdukty();

    return 0;
}
