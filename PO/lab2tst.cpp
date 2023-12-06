#include <iostream>
using namespace std;

class WezelListy {
public:
    string imieStudenta;
    string nazwiskoStudenta;
    double sredniaOcenStudenta;
    char plecStudenta;
    WezelListy* wskNastepny;
    WezelListy* wskPoprzedni;

    WezelListy(string imStudenta, string nzStudenta, double srOcStudenta, char plStudenta) {
        this->imieStudenta = imStudenta;
        this->nazwiskoStudenta = nzStudenta;

        if (srOcStudenta < 2.0) {
            this->sredniaOcenStudenta = 2.0;
        } else if (srOcStudenta > 5.0) {
            this->sredniaOcenStudenta = 5.0;
        } else {
            this->sredniaOcenStudenta = srOcStudenta;
        }

        if (plStudenta != 'm' && plStudenta != 'k') {
            this->plecStudenta = 'm';
        } else {
            this->plecStudenta = plStudenta;
        }

        wskNastepny = NULL;
        wskPoprzedni = NULL;
    }
};

class ListaStudentow {
public:
    WezelListy* glowa;
    WezelListy* ogon;
    int aktualnaDlugoscListy;

    void dodajNowegoStudentaNaPoczatekListy(string imStudenta, string nzStudenta, double srOcStudenta, char plStudenta) {
        WezelListy* nowyStudent = new WezelListy(imStudenta, nzStudenta, srOcStudenta, plStudenta);

        if (glowa == NULL) {
            glowa = nowyStudent;
            ogon = nowyStudent;
        } else {
            nowyStudent->wskNastepny = glowa;
            glowa->wskPoprzedni = nowyStudent;
            glowa = nowyStudent;
        }
         
        cout << "Podaj imie: ";
        cin >> nowyStudent->imieStudenta;
        cout << "Podaj nazwisko: ";
        cin >> nowyStudent->nazwiskoStudenta;
        cout << "Podaj srednia: ";
        cin >> nowyStudent->sredniaOcenStudenta;
        cout << "Podaj plec: ";
        cin >> nowyStudent->plecStudenta;

 
        aktualnaDlugoscListy++;
    }

    void usunZListyStudentaOPodanymImieniuINazwisku(string imStudenta, string nzStudenta) {
        WezelListy* obecny = glowa;

        while (obecny != NULL) {
            if (obecny->imieStudenta == imStudenta && obecny->nazwiskoStudenta == nzStudenta) {
                if (obecny->wskNastepny != NULL) {
                    obecny->wskNastepny->wskPoprzedni = obecny->wskPoprzedni;
                } else {
                    ogon = obecny->wskPoprzedni;
                }

                if (obecny->wskPoprzedni != NULL) {
                    obecny->wskPoprzedni->wskNastepny = obecny->wskNastepny;
                } else {
                    glowa = obecny->wskNastepny;
                }

                delete obecny;
                aktualnaDlugoscListy--;
                cout << "Student zostal usuniety" << endl;
                return;
            }

            obecny = obecny->wskNastepny;
        }

        cout << "Student o podanym imieniu i nazwisku nie zostal znaleziony" << endl;
    }

    WezelListy* zwrocWezelZListyStudentaOPodanymNrPozycji(int nrPozycji) {
        WezelListy* obecny = glowa;
        int pozycja = 1;

        while (obecny != NULL) {
            if (pozycja == nrPozycji) {
                cout << "Informacje o studencie na pozycji " << nrPozycji << ":" << endl;
                cout << "Imie: " << obecny->imieStudenta << endl;
                cout << "Nazwisko: " << obecny->nazwiskoStudenta << endl;
                cout << "Srednia ocen: " << obecny->sredniaOcenStudenta << endl;
                cout << "Plec: " << obecny->plecStudenta << endl;
                return obecny;
            }

            obecny = obecny->wskNastepny;
            pozycja++;
        }

        cout << "Brak studenta na podanej pozycji" << endl;
        return NULL;
    }

    void wyswietlDaneWezlowZListyStudentowOSredniejOcenWyzszejOdZadanej(double srednia) {
        WezelListy* obecny = glowa;

        while (obecny != NULL) {
            if (obecny->sredniaOcenStudenta > srednia) {
                cout << "Imie: " << obecny->imieStudenta << " Nazwisko: " << obecny->nazwiskoStudenta << " Srednia ocen: " << obecny->sredniaOcenStudenta << endl;
            }

            obecny = obecny->wskNastepny;
        }
    }

    WezelListy* zwrocWezelZLIstyStudentowDlaKobietyOSredniejOcenNajblizszejZadanej(double srednia) {
        WezelListy* obecny = glowa;
        WezelListy* najblizszaStudentka = NULL;
        double roznicaMin = 3;

        while (obecny != NULL) {
            if (obecny->plecStudenta == 'k') {
                double roznica = abs(obecny->sredniaOcenStudenta - srednia);
                if (roznica < roznicaMin) {
                    najblizszaStudentka = obecny;
                    roznicaMin = roznica;
                }
            }

            obecny = obecny->wskNastepny;
        }

        if (najblizszaStudentka != NULL) {
            cout << "Najblizsza studentka:" << endl;
            cout << "Imie: " << najblizszaStudentka->imieStudenta << " Nazwisko: " << najblizszaStudentka->nazwiskoStudenta << " Srednia ocen: " << najblizszaStudentka->sredniaOcenStudenta << endl;
            return najblizszaStudentka;
        } else {
            cout << "Brak studentek w liscie" << endl;
            return NULL;
        }
    }

    ListaStudentow() : glowa(NULL), ogon(NULL), aktualnaDlugoscListy(0) {}

    ~ListaStudentow() {
        WezelListy* obecny = glowa;
        WezelListy* nastepny = NULL;

        while (obecny != NULL) {
            nastepny = obecny->wskNastepny;
            delete obecny;
            obecny = nastepny;
        }
    }
};

int main() {
    ListaStudentow* listaStudentow = new ListaStudentow();

    while (1) {
        int choice = 0;
        cout << "Program do zarzadzania lista studentow\n\
    [0] - wyjscie z programu\n\
    [1] - dodawanie nowego studenta na poczatek listy\n\
    [2] - usuwanie z listy studenta o podanym imieniu i nazwisku\n\
    [3] - wyswietlanie informacji o studencie na podanej pozycji listy\n\
    [4] - wyswielanie informacji o studentach majacych srednia wyzsza od podanej\n\
    [5] - wyswietlanie informacji o kobiecie majacej srednia najblizsza podanej\n\
    ==============================\nWprowadz nr operacji: ";
        cin >> choice;

        string imie, nazwisko;
        double srednia;
        char plec;
        int nr;

        switch (choice) {
        case 0:
            cout << "Konczenie programu..." << endl;
            delete listaStudentow;
            return 0;

        case 1:
            listaStudentow->dodajNowegoStudentaNaPoczatekListy(imie, nazwisko, srednia, plec);
            cout << endl << "Student zostal dodany";
            break;

        case 2:
            cout << endl << "Podaj imie: ";
            cin >> imie;
            cout << endl << "Podaj nazwisko: ";
            cin >> nazwisko;
            listaStudentow->usunZListyStudentaOPodanymImieniuINazwisku(imie, nazwisko);
            break;

        case 3:
            cout << "Podaj nr studenta: ";
            cin >> nr;
            listaStudentow->zwrocWezelZListyStudentaOPodanymNrPozycji(nr);
            break;

        case 4:
            cout << "Podaj srednia ocen: ";
            cin >> srednia;
            listaStudentow->wyswietlDaneWezlowZListyStudentowOSredniejOcenWyzszejOdZadanej(srednia);
            break;

        case 5:
            cout << "Podaj srednia ocen: ";
            cin >> srednia;
            listaStudentow->zwrocWezelZLIstyStudentowDlaKobietyOSredniejOcenNajblizszejZadanej(srednia);
            break;
        }
    }

    return 0;
}
