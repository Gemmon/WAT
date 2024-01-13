#include<stdio.h>

template <typename T, typename Sort> class Kolekcja{
   T tablicaDanych[100];
   Sort rodzajSortowania;

   public:
   void dodaj(T wartosc);
   T zdejmij();
   void posortuj();
   void wydrukuj();
   void oproznij();

};

template <typename T, typename Sort> class LIFO : public Kolekcja <T, Sort>{
    public:
    LIFO(Sort rdzjSort);
};

template <typename T, typename Sort> class FIFO : public Kolekcja <T, Sort>{
    public:
    FIFO(Sort rdzjSort);
};


template <typename T> class Sortowanie{
    public:
    posortuj(T* tablica, int rozmiar);
};

template <typename T> class SortwanieRosnace : public Sortowanie <T>{
    
};

template <typename T> class SortwanieMalejace : public Sortowanie <T>{
    
};


int main(){

}