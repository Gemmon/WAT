#include <iostream>
using namespace std;


class Autobus{
    private:
    int aktualnaLiczbaPasazerow;
    int limitPasazerow;
    bool zajeteMiejsceKierowcy;
    
    public:

    int zwrocPasazer(){
        return aktualnaLiczbaPasazerow;
    };

    void usiadzZaKierownica()
    {
       if(this->zajeteMiejsceKierowcy == false) this->zajeteMiejsceKierowcy = true;
    };

    void wysiadzZzaKierownicy()
    {
       if(this->zajeteMiejsceKierowcy == true) this->zajeteMiejsceKierowcy = false;
    };

    void wpuscPasazerow(int liczba)
    {
       if(this->zajeteMiejsceKierowcy == true)
       {
        if(this->aktualnaLiczbaPasazerow + liczba < this->limitPasazerow + 1 ){  
        this->aktualnaLiczbaPasazerow += liczba;
        cout << "Liczba pasazerow: " << this->aktualnaLiczbaPasazerow <<endl;
        }
        else
        {
        int oczek = 0;
        oczek = this->aktualnaLiczbaPasazerow + liczba - this->limitPasazerow; 
        this->aktualnaLiczbaPasazerow = this->limitPasazerow;
        cout << "Liczba pasazerow: " << this->aktualnaLiczbaPasazerow <<endl; 
        cout << "Liczba oczekujacych: " << oczek <<endl; 
        };

       } else cout << "Nie ma kierowcy" <<endl;
    };
    void wypuscPasazerow(int liczba)
    {
        if(this->zajeteMiejsceKierowcy == true){

        if(this->aktualnaLiczbaPasazerow - liczba >= 0)
        { 
           this->aktualnaLiczbaPasazerow -= liczba;
           cout << "Liczba pasazerow: " << this->aktualnaLiczbaPasazerow <<endl;}
        else 
        {
        cout << "Nie ma tyle osob w autobusie " <<endl; 
        cout << "Liczba pasazerow: " << this->aktualnaLiczbaPasazerow <<endl;
        };

    } else cout << "Nie ma kierowcy " <<endl;
    };

    Autobus(int limitPasazerow)
    {
    this->aktualnaLiczbaPasazerow = 0;
    this->zajeteMiejsceKierowcy = false;
    this->limitPasazerow = limitPasazerow;
    };
    
};


int main(void){


    Autobus* A = new Autobus(65);
    
    A->wpuscPasazerow(12);
    A->usiadzZaKierownica();
    A->wpuscPasazerow(67); 
    A->wypuscPasazerow(82);
    A->wypuscPasazerow(21);

    delete A;

    return 0;
}
