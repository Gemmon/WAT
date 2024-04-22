# fakty
osoby = \
{
    "Marek": {'wiek': 36, "stan_konta": 132128, "zarobki_domostwa": 96923, "w_zwiazku_malzenskim": False,  "wartosc_kredytu": 834000},
    "Zofia": {'wiek': 24, "stan_konta": 23012, "zarobki_domostwa": 54986, "w_zwiazku_malzenskim": True,  "wartosc_kredytu": 470000},
    "Zbigniew": {'wiek': 75, "stan_konta": 745128, "zarobki_domostwa": 87890, "w_zwiazku_malzenskim": True, "wartosc_kredytu": 62300},
    "Hania": {'wiek': 68, "stan_konta": 190632, "zarobki_domostwa": 55890, "w_zwiazku_malzenskim": True, "wartosc_kredytu": 5409}
}

#reguły
def ochrona(fakty):
    if fakty.get("stan_konta", False) <= 200000:
        return "jest całkowicie objęte ochroną"
    return None

def socjal(fakty):
    if fakty.get("zarobki_domostwa", False) <= 60000:
        return "może otrzymać pomoc socjalną"
    return None

def kredyt(fakty):
    if fakty.get("zarobki_domostwa", False) > 0.1*fakty.get("wartosc_kredytu"):
        return "może otrzymać chciany kredyt"
    return None

def dofinansowanie(fakty):
    if fakty.get("wiek", False) < 30 and fakty.get("wartosc_kredytu") < 500000 and fakty.get("w_zwiazku_malzenskim", False) is True:
        return "kwalifikuje się na dofinansowanie"
    return None

def zniżka_seniora(fakty):
    if fakty.get("wiek", False) >= 65:
        return "posiada zniżkę seniora"
    return None

#zdefiniowanie reguł
reguly = [ochrona, socjal, kredyt, dofinansowanie, zniżka_seniora]

# sprawdzanie czy dana osoba spełnia reguły
def wnioskowanie(fakty, reguly):
    wnioski = []
    for regula in reguly:
        wynik = regula(fakty)
        if wynik is not None:
            wnioski.append(wynik)
    return wnioski

# tworzenie wniosków, by zapewnić nie przyjmowanie None dodany jest filtr
for imie, fakty_osoby in osoby.items():
    wnioski = wnioskowanie(fakty_osoby, reguly)
    filtrowane_wnioski = [wnioski for wnioski in wnioski if wnioski is not None]
    if filtrowane_wnioski:
        print(f"Konto użytkownika: {imie}")
        for wnioski in filtrowane_wnioski:
            print(f"    {wnioski}")
    else:
        print(f"Konto użytkownika: {imie} nie ma żadnych przywileji.")
