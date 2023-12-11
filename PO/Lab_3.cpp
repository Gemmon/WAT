#include<iostream>
#include<string>
using namespace std;

class PC;
class KontoAdministratora;
class KontoUzytkownika;

class KontoAdministratora{
    string login;


    public:
    void zalogujAdministracyjnie(PC* host);

    void zmienAdresIP(PC* host, string nowyAdres);

    void wylogujUzytkownika(KontoUzytkownika* uzyt, PC* host);

    KontoAdministratora(string login){
     this->login = login;
    }
    
};

class PC{
    string adresIP;
    KontoAdministratora* zalogowanyAdministrator;
    KontoUzytkownika* zalogowanyUzytkownik;

    public:
    friend class KontoAdministratora;

    PC(string adrIP, KontoAdministratora* zalogowanyAdministrator, KontoUzytkownika* zalogowanyUzytkownik){};
    PC() : adresIP("192.168.0.1"), zalogowanyAdministrator(nullptr), zalogowanyUzytkownik(nullptr) {};
};

class KontoUzytkownika{
    string login;
    PC* host;

    public:
    friend class KontoAdministratora;

    KontoUzytkownika(string login, PC* host) {
    this->login = login;
    this->host = host;
}
    
};

void KontoAdministratora::zalogujAdministracyjnie(PC* host){
    // Sprawdź, czy administrator już jest zalogowany
    if (host->zalogowanyAdministrator != NULL) {
        cout << "Administrator " << host->zalogowanyAdministrator->login << " jest już zalogowany na tym komputerze." << endl;
    } else {
        host->zalogowanyAdministrator = this; // Zaloguj administratora
        cout << "Zalogowano administratora " << login << " na komputerze o adresie IP: " << host->adresIP << endl;
    }
}

void KontoAdministratora::zmienAdresIP(PC* host, string nowyAdres){
    if (host->adresIP == "") {
        cout << "Brak adresu " << endl;
    } else {
        host->adresIP = nowyAdres;
        cout << "Uzytkownikowi" << login << " zmieniono adresie IP na : " << host->adresIP << endl;
    }
}

void KontoAdministratora::wylogujUzytkownika(KontoUzytkownika* uzyt, PC* host) {
    // Sprawdź, czy użytkownik jest zalogowany na danym komputerze
    if (uzyt->host == host) {
        cout << "Wylogowano użytkownika " << uzyt->login << " z komputera o adresie IP: " << host->adresIP << endl;
        host->zalogowanyUzytkownik = NULL; // Wyloguj użytkownika
    } else {
        cout << "Użytkownik " << uzyt->login << " nie jest zalogowany na tym komputerze." << endl;
    }
}


int main() {
    // Create instances of PC and accounts
    PC myPC;
    KontoAdministratora adminAccount("admin1");
    KontoUzytkownika userAccount("user1", &myPC);

    // Test logging in as an administrator
    adminAccount.zalogujAdministracyjnie(&myPC);

    // Test changing IP address
    adminAccount.zmienAdresIP(&myPC, "192.168.0.2");

    // Test logging out a user
    adminAccount.wylogujUzytkownika(&userAccount, &myPC);

    return 0;
}