#include <iostream>
using namespace std;

class WezelListy{
    public:
    string imieStudenta;
    string nazwiskoStudenta;
    double sredniaOcenStudenta;
    char plecStudenta;
    WezelListy* wskNastepny;
    WezelListy* wskPoprzedni;

    WezelListy(string imStudenta, string nzStudenta, double srOcStudenta, char plStudenta){
        this->imieStudenta = imStudenta;
        this->nazwiskoStudenta = nzStudenta;
        this->sredniaOcenStudenta = srOcStudenta;
        this->plecStudenta = plStudenta;
        wskNastepny = NULL;
        wskPoprzedni = NULL;
    }
};

class ListaStudentow{
  public:
  WezelListy* glowa;
  WezelListy* ogon;
  int aktualnaDlugoscListy;


  void dodajNowegoStudentaNaPoczatekListy(string imStudenta, string nzStudenta, double srOcStudenta, char plStudenta){
      WezelListy* nowyStudent = new WezelListy(imStudenta, nzStudenta, srOcStudenta, plStudenta);

     if(glowa == NULL){
        glowa = nowyStudent;
        ogon = nowyStudent;
       } else {
        nowyStudent->wskNastepny = glowa;
        glowa->wskPoprzedni = nowyStudent;
        glowa = nowyStudent;
       }
    aktualnaDlugoscListy++;
  }

  void usunZListyStudentaOPodanymImieniuINazwisku(string imStudenta, string nzStudenta){


  }

  WezelListy* zwrocWezelZListyStudentaOPodanymNrPozycji(int nrPozycji){



       return NULL;
  }

  void wyswietlDaneWezlowZListyStudentowOSredniejOcenWyzszejOdZadanej(double srednia){

  }

  WezelListy* zwrocWezelZLIstyStudentowDlaKobietyOSredniejOcenNajblizszejZadanej(double srednia){

    return NULL;
  }


   ListaStudentow(): glowa(NULL), ogon(NULL), aktualnaDlugoscListy(0){
   }

  ~ListaStudentow();


};


int main(){

    ListaStudentow* listaStudentow = new ListaStudentow();

while(1){
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
    
    
    switch(choice){

        case 0:
        cout << "Konczenie programu..."<< endl;
        return 0;
        
        case 1:
        cout<< endl << "Podaj imie: ";
        cin >> imie;
        cout<< endl << "Podaj nazwisko: ";
        cin >> nazwisko;
        cout<< endl << "Podaj srednia:";
        cin >> srednia;
        cout<< endl << "Podaj plec: ";
        cin >> plec;
        listaStudentow->dodajNowegoStudentaNaPoczatekListy(imie, nazwisko, srednia, plec);
        cout<< endl << "Student zostal dodany";
        break;

        case 2:
         cout<< endl << "Podaj imie: ";
        cin >> imie;
        cout<< endl << "Podaj nazwisko: ";
        cin >> nazwisko;
        listaStudentow->usunZListyStudentaOPodanymImieniuINazwisku(imie, nazwisko);
        cout<< endl << "Student zostal usuniety";
        break;

        case 3:
        int nr;
        cout <<"Podaj nr studenta: ";
        cin >> nr;
        listaStudentow->zwrocWezelZListyStudentaOPodanymNrPozycji(nr);
          
        break;

        case 4:

        break;
    }

}
return 0;
}
