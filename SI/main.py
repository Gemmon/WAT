# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.
kredytobiorcy = \
{
    "Marek": {'wiek': 36, "stan_konta": 132128, "w_zwiazku_malzenskim": False, "zarobki_domostwa:": 96923,  "wartosc_kredytu": 834000},
    "Zofia": {'wiek': 24, "stan_konta": 23012, "w_zwiazku_malzenskim": True, "zarobki_domostwa:": 54986,  "wartosc_kredytu": 470000},
    "Zbigniew": {'wiek': 75, "stan_konta": 745128, "w_zwiazku_malzenskim": True, "zarobki_domostwa:": 67890, "wartosc_kredytu": 62300},
    "Hania": {'wiek': 68, "stan_konta": 190632, "w_zwiazku_malzenskim": True, "zarobki_domostwa:": 55890, "wartosc_kredytu": 5409}
}

def print_hi(name):
    # Use a breakpoint in the code line below to debug your script.
    print(f'Hi, {name}')  # Press Ctrl+F8 to toggle the breakpoint.

def ochrona(fakty):
    if fakty.get("stan_konta", 0) > 200000:
        return "konto jest objete ochrona"
    return None

def socjal(fakty):
    if fakty.get("zarobki_domostwa", 0) < 60000:
        return "moga otrzymac socjal"
    return None

def kredyt(fakty):
    if fakty.get("zarobki_domostwa", 0) > 0.1*fakty.get("wartosc_kredytu"):
        return "sa objete ochrona"
    return None
# czy pieniadze są objęte ochronioną/ mniej niż 200000
# czy zaliczaja sie do programu socjalnego/ zarobki domostwa dla malzenstw ponizej 60000
# dostac kredyt/ zarobki wieksze niz 10% kredytu
# finansowanie na mieszkania dla mlodych/ ponizej 26 roku i w malzenstwie
# wsparcie dla seniora/ od ponieżej 60 tys

# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    print_hi('PyCharm')
