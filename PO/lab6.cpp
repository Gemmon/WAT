#include <iostream>

using namespace std;

template<typename T, typename Sort> class Kolekcja{
    protected:
    T tablicaDanych[100];
    Sort rodzajSortowania;
    public:
    int counter = 0;
    public:
    void dodaj(T wartosc);
    T zdejmij();
    void posortuj();
    void wydrukuj();
    void oproznij();

};

template<typename T, typename Sort> class LIFO : public Kolekcja<T, Sort>{
    public:
    LIFO(Sort rdzSort){
        this->rodzajSortowania = rdzSort;
    };
    void dodaj(T wartosc){
        if(this->counter < 99){
            this->tablicaDanych[this->counter] = wartosc;
            this->counter++;
        }else cout << "Tablica jest pelna, nie dodano elementu";
    }
    void wydrukuj(){
        cout << "Aktualny wydruk tablicy: \n";
        for(int i = 0 ; i < this->counter; i++){
            cout << this->tablicaDanych[i] << " ";
        }
        cout << endl;
    }
    void posortuj(){
        this->rodzajSortowania.posortuj(this->tablicaDanych,this->counter);
    };
    T zdejmij(){
        if(this->counter > 0){
            this->counter--;
            return this->tablicaDanych[this->counter]; 
        }else cout << "Tablica jest pusta, brak elementu do zwrotu\n";
            return -1;

    }
    void oproznij(){
        this->counter = 0;
    }
};

template<typename T, typename Sort> class FIFO : public Kolekcja<T, Sort>{
    public:
    FIFO(Sort rdzSort){
        this->rodzajSortowania = rdzSort;
    };
        void dodaj(T wartosc){
        if(this->counter < 99){
            this->tablicaDanych[this->counter] = wartosc;
            this->counter++;
        }else cout << "Tablica jest pelna, nie dodano elementu";
    }
    void wydrukuj(){
        cout << "Aktualny wydruk tablicy: \n";
        for(int i = 0 ; i < this->counter; i++){
            cout << this->tablicaDanych[i] << " ";
        }
        cout << endl;
    }
    void posortuj(){
        this->rodzajSortowania.posortuj(this->tablicaDanych,this->counter);
    };
    void zdejmij(){
        if(this->counter > 0)
        int pom = this->tablicaDanych[0];
        for(int i = 0 ; i < this->counter ; i++){
            this->tablicaDanych[i] = this->tablicaDanych[i+1];
        }
        this->counter--;
    }
    void oproznij(){
        this->counter = 0;
    }
};

template<typename T> class Sortowanie{
    public:
    void posortuj(T* tablica, int rozmiar);
};

template<typename T> class SortowanieMalejaco : public Sortowanie<T>{
public:
    void posortuj(T* tab, int size){
        cout << "Sortuje malejaco...\n";
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (tab[j] < tab[j + 1]) {
                    swap(tab[j], tab[j + 1]);
                }
            }
        }
    }
};


template<typename T> class SortowanieRosnaco : public Sortowanie<T>{
public:
    void posortuj(T* tab, int size){
        cout << "Sortuje rosnaco...\n";
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (tab[j] > tab[j + 1]) {
                    swap(tab[j], tab[j + 1]);
                }
            }
        }
    }
};




int main(){
    SortowanieMalejaco<double> sMal; 
    SortowanieRosnaco<double> sRos;

    FIFO<double, SortowanieMalejaco <double>> fifo(sMal); 
    LIFO<double, SortowanieRosnaco <double>> lifo2(sRos); 


    fifo.dodaj(51);
    fifo.dodaj(162);
    fifo.dodaj(12.85);
    fifo.dodaj(2.32);
    fifo.dodaj(123.21);

    lifo2.dodaj(123.32);
    lifo2.dodaj(86);
    lifo2.dodaj(11.32);
    lifo2.dodaj(23.92);
    lifo2.dodaj(11.82);
    
    fifo.wydrukuj();
    fifo.posortuj();
    fifo.wydrukuj();
    fifo.oproznij();
    fifo.wydrukuj();

    fifo.dodaj(34.32);
    fifo.dodaj(4323.322);
    fifo.posortuj();
    fifo.wydrukuj();

    lifo2.posortuj();
    lifo2.wydrukuj();


    return 0;
}