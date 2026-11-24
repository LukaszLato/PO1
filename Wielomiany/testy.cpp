#include "Wielomian.h"

int main()
{
    const char* przyklady[] = {
        "x^3-x^2+2x-7.5",
        "3x^2+5x+2",
        "x^4-2x^2+1",
        "-x^3+x-4",
        "5",
        "x",
        "-x",
        "0",
        "2x^2 + 3x^2 - x + 1"
    };

    for (int i = 0; i < 9; i++) {
        Wielomian w(przyklady[i]);
        cout << "Przyklad " << i + 1 << ": ";
        w.Pokaz();
    }

    Wielomian pusty;
    cout << "Bezargumentowy: ";
    pusty.Pokaz();

    Wielomian oryginal("x^2+3x-5");
    Wielomian kopia(oryginal);
    cout << "Kopia: ";
    kopia.Pokaz();

    double tablica[] = { -7.5, 2.0, -1.0, 1.0 };
    Wielomian zTablicy(3, tablica);
    cout << "Z tablicy: ";
    zTablicy.Pokaz();

    cout << "Stopien: " << zTablicy.PobierzStopien() << endl;
    cout << "Wspolczynnik przy x^2: " << zTablicy.PobierzWspolczynnik(2) << endl;

    pusty = oryginal;
    cout << "Po przypisaniu: ";
    pusty.Pokaz();

    //dod wiel
    Wielomian a("x^2+2x+1");
    Wielomian b("x^3-x^2+3");

    cout << "Pierwszy wielomian: ";
    a.Pokaz();
    cout << "Drugi wielomian: ";
    b.Pokaz();

    Wielomian suma = a + b;
    cout << "a + b: ";
    suma.Pokaz();

    a += b;
    cout << "a += b: ";
    a.Pokaz();

    //dod wiel te same stopnie
    Wielomian c("x^2+2x+1");
    Wielomian d("-x^2-2x-1");
    cout << "c + d: ";
    (c + d).Pokaz();

    //dod wiel o nizszym stopniu od wyzszego
    Wielomian e("x^4+1");
    Wielomian f("2x-3");
    e += f;
    cout << "e += f: ";
    e.Pokaz();

    //od wiel | przypisanie
    Wielomian g("3x^2+5x+7");
    Wielomian h("x^2+2x+4");

    cout << "g - h: ";
    (g - h).Pokaz();

    g -= h;
    cout << "g -= h: ";
    g.Pokaz();

    // Mnozenie wielomianow
    Wielomian k("x+2");
    Wielomian l("x+3");

    cout << "k * l: ";
    (k * l).Pokaz();

    k *= l;
    cout << "k *= l: ";
    k.Pokaz();

    // Dzielenie wielomianow
    Wielomian m("x^2+5x+6");
    Wielomian n("x+2");

    cout << "m / n: ";
    (m / n).Pokaz();

    m /= n;
    cout << "m /= n: ";
    m.Pokaz();

    // Mnozenie wielomianu przez liczbe
    Wielomian p("x^2+2x+1");

    p *= 3;

    cout << "p *= 3: ";
    p.Pokaz();

    Wielomian q("x^2+2x+1");

    cout << "q * 3: ";
    (q * 3).Pokaz();

    cout << "3 * q: ";
    (3 * q).Pokaz();

    // Dodawanie liczby do wielomianu
    Wielomian r("x^2+2x+1");

    r += 5;

    cout << "r += 5: ";
    r.Pokaz();

    cout << "r + 5: ";
    (r + 5).Pokaz();

    cout << "5 + r: ";
    (5 + r).Pokaz();

    // Odejmowanie liczby od wielomianu
    Wielomian s("x^2+2x+7");

    s -= 5;

    cout << "s -= 5: ";
    s.Pokaz();

    cout << "s - 5: ";
    (s - 5).Pokaz();

    cout << "5 - s: ";
    (5 - s).Pokaz();

    // Dzielenie wielomianu przez liczbe
    Wielomian t("6x^2+12x+18");

    t /= 3;

    cout << "t /= 3: ";
    t.Pokaz();

    cout << "t / 2: ";
    (t / 2).Pokaz();

    // Testy szczegolnych przypadkow dzielenia
    Wielomian u("x^2+3x+2");

    cout << "u / u: ";
    (u / u).Pokaz();

    Wielomian zero("0");
    cout << "u / zero: ";
    (u / zero).Pokaz();

    Wielomian maly("x+1");
    Wielomian duzy("x^3+2");

    cout << "maly / duzy: ";
    (maly / duzy).Pokaz();

    // Wartosc wielomianu - schemat Hornera
    Wielomian horner("2x^2+3x+1");

    cout << "W(2) = " << horner(2) << endl;
    cout << "W(0) = " << horner(0) << endl;

    // Operator [] - odczyt wspolczynnika
    Wielomian indeks("3x^2+5x+2");

    cout << "indeks[2] = " << indeks[2] << endl;
    cout << "indeks[1] = " << indeks[1] << endl;
    cout << "indeks[0] = " << indeks[0] << endl;
    cout << "indeks[5] = " << indeks[5] << endl;

    // Operator << - wypisywanie wielomianu
    Wielomian wypisz("3x^2-2x+7");

    cout << "Operator << : " << wypisz << endl;

    // Operator >> - wczytywanie wielomianu
    Wielomian wczytany;

    cout << "Podaj wielomian: ";
    cin >> wczytany;

    cout << "Wczytany wielomian: " << wczytany << endl;

    return 0;
}
