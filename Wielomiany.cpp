#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

class Wielomian
{
private:
    double* wspolczynnik;
    int stopien;

    const char* AnalizujJednomian(const char* napis);
    void AnalizujJednomiany(const char* napis);
    int RzeczywistyStopien() const;

public:
    Wielomian();
    Wielomian(const char* napis);
    Wielomian(const Wielomian& w);
    Wielomian(int stopien, const double* tablica);
    ~Wielomian();

    Wielomian& operator=(const Wielomian& w);
    Wielomian& operator+=(const Wielomian& w);
    Wielomian& operator+=(double liczba);
    Wielomian operator+(double liczba) const;
    Wielomian operator+(const Wielomian& w) const;
    Wielomian& operator-=(const Wielomian& w);
    Wielomian& operator-=(double liczba);
    Wielomian operator-(double liczba) const;
    Wielomian operator-(const Wielomian& w) const;
    Wielomian& operator*=(const Wielomian& w);
    Wielomian operator*(const Wielomian& w) const;
    Wielomian& operator*=(double liczba);
    Wielomian operator*(double liczba) const;
    Wielomian& operator/=(const Wielomian& w);
    Wielomian& operator/=(double liczba);
    Wielomian operator/(double liczba) const;
    Wielomian operator/(const Wielomian& w) const;


    int PobierzStopien() const;
    double PobierzWspolczynnik(int i) const;
    double operator()(double x) const;
    double operator[](int i) const;
    void Pokaz() const;

    friend ostream& operator<<(ostream& wyjscie, const Wielomian& w);
    friend istream& operator>>(istream& wejscie, Wielomian& w);
};

char* UsunOdstepy(const char* napis)
{
    char* napis2;
    int y = 0, dlugosc = strlen(napis);
    napis2 = new char[dlugosc + 1];

    for (int i = 0; i < dlugosc; i++)
        if (napis[i] != ' ')
            napis2[y++] = napis[i];

    napis2[y] = 0;
    return napis2;
}

int OkreslStopien(const char* napis)
{
    int maksStopien = 0;
    int stopien = 0;
    int i = 0;

    while (napis[i]) {
        if (napis[i] == 'x') {
            if (napis[i + 1] == '^') {
                char* koniecNapisu;
                stopien = strtol(&napis[i + 2], &koniecNapisu, 10);
                i = koniecNapisu - napis;
            }
            else {
                stopien = 1;
                i++;
            }

            if (stopien > maksStopien)
                maksStopien = stopien;
        }
        else
            i++;
    }
    return maksStopien;
}

double* PrzydzielPamiec(int stopien)
{
    double* tab = new double[stopien + 1];
    for (int i = 0; i <= stopien; i++)
        tab[i] = 0.0;
    return tab;
}

int Wielomian::RzeczywistyStopien() const
{
    int i = stopien;

    while (i > 0 && wspolczynnik[i] == 0)
        i--;

    return i;
}

const char* Wielomian::AnalizujJednomian(const char* napis)
{
    int wykladnik = 0;
    int znak = 1;
    double wsp;

    if (*napis == '-') {
        napis++;
        znak = -1;
    }
    else if (*napis == '+')
        napis++;

    if (*napis == 'x')
        wsp = 1;
    else {
        char* koniec;
        wsp = strtod(napis, &koniec);
        if (koniec == napis)
            return napis;
        napis = koniec;
    }

    if (*napis == 'x') {
        if (*++napis == '^') {
            char* koniecNapisu;
            wykladnik = strtol(++napis, &koniecNapisu, 10);
            napis = koniecNapisu;
        }
        else
            wykladnik = 1;
    }

    if (wykladnik >= 0 && wykladnik <= stopien)
        wspolczynnik[wykladnik] += znak * wsp;

    return napis;
}

void Wielomian::AnalizujJednomiany(const char* napis)
{
    while (*napis) {
        const char* nowy = AnalizujJednomian(napis);
        if (nowy == napis)
            break;
        napis = nowy;
    }
}

Wielomian::Wielomian()
{
    stopien = 0;
    wspolczynnik = PrzydzielPamiec(stopien);
}

Wielomian::Wielomian(const char* napis)
{
    char* bezOdstepow = UsunOdstepy(napis);
    stopien = OkreslStopien(bezOdstepow);
    wspolczynnik = PrzydzielPamiec(stopien);
    AnalizujJednomiany(bezOdstepow);
    delete[] bezOdstepow;
}

Wielomian::Wielomian(const Wielomian& w)
{
    stopien = w.stopien;
    wspolczynnik = PrzydzielPamiec(stopien);
    for (int i = 0; i <= stopien; i++)
        wspolczynnik[i] = w.wspolczynnik[i];
}

Wielomian::Wielomian(int st, const double* tablica)
{
    if (st < 0 || tablica == nullptr) {
        stopien = 0;
        wspolczynnik = PrzydzielPamiec(stopien);
    }
    else {
        stopien = st;
        wspolczynnik = PrzydzielPamiec(stopien);
        for (int i = 0; i <= stopien; i++)
            wspolczynnik[i] = tablica[i];
    }
}

Wielomian::~Wielomian()
{
    delete[] wspolczynnik;
}

Wielomian& Wielomian::operator=(const Wielomian& w)
{
    if (this != &w) {
        double* nowaTablica = PrzydzielPamiec(w.stopien);
        for (int i = 0; i <= w.stopien; i++)
            nowaTablica[i] = w.wspolczynnik[i];

        delete[] wspolczynnik;
        wspolczynnik = nowaTablica;
        stopien = w.stopien;
    }
    return *this;
}

Wielomian& Wielomian::operator+=(const Wielomian& w)
{
    if (stopien < w.stopien) {
        double* nowaTablica = PrzydzielPamiec(w.stopien);

        for (int i = 0; i <= stopien; i++)
            nowaTablica[i] = wspolczynnik[i];

        delete[] wspolczynnik;
        wspolczynnik = nowaTablica;
        stopien = w.stopien;
    }

    for (int i = 0; i <= w.stopien; i++)
        wspolczynnik[i] += w.wspolczynnik[i];

    return *this;
}

Wielomian& Wielomian::operator+=(double liczba)
{
    wspolczynnik[0] += liczba;
    return *this;
}

Wielomian& Wielomian::operator-=(const Wielomian& w)
{
    if (stopien < w.stopien) {
        double* nowaTablica = PrzydzielPamiec(w.stopien);

        for (int i = 0; i <= stopien; i++)
            nowaTablica[i] = wspolczynnik[i];

        delete[] wspolczynnik;
        wspolczynnik = nowaTablica;
        stopien = w.stopien;
    }

    for (int i = 0; i <= w.stopien; i++)
        wspolczynnik[i] -= w.wspolczynnik[i];
    return *this;
}

Wielomian& Wielomian::operator-=(double liczba)
{
    wspolczynnik[0] -= liczba;
    return *this;
}

Wielomian& Wielomian::operator*=(const Wielomian& w)
{
    int nowyStopien = stopien + w.stopien;
    double* nowaTablica = PrzydzielPamiec(nowyStopien);

    for (int i = 0; i <= stopien; i++) {
        for (int j = 0; j <= w.stopien; j++) {
            nowaTablica[i + j] += wspolczynnik[i] * w.wspolczynnik[j];
        }
    }

    delete[] wspolczynnik;
    wspolczynnik = nowaTablica;
    stopien = nowyStopien;

    return *this;
}

Wielomian& Wielomian::operator*=(double liczba)
{
    for (int i = 0; i <= stopien; i++)
        wspolczynnik[i] *= liczba;

    return *this;
}

Wielomian& Wielomian::operator/=(const Wielomian& w)
{
    int stopienDzielnika = w.RzeczywistyStopien();

    if (stopienDzielnika == 0 && w.wspolczynnik[0] == 0) {
        cout << "Blad: dzielenie przez wielomian zerowy!" << endl;
        return *this;
    }

    int stopienDzielnej = RzeczywistyStopien();

    if (stopienDzielnej < stopienDzielnika) {
        delete[] wspolczynnik;
        stopien = 0;
        wspolczynnik = PrzydzielPamiec(stopien);
        return *this;
    }

    int nowyStopien = stopienDzielnej - stopienDzielnika;

    double* wynik = PrzydzielPamiec(nowyStopien);
    double* reszta = PrzydzielPamiec(stopienDzielnej);

    for (int i = 0; i <= stopienDzielnej; i++)
        reszta[i] = wspolczynnik[i];

    for (int i = nowyStopien; i >= 0; i--) {
        double liczba = reszta[i + stopienDzielnika]
            / w.wspolczynnik[stopienDzielnika];

        wynik[i] = liczba;

        for (int j = 0; j <= stopienDzielnika; j++)
            reszta[i + j] -= liczba * w.wspolczynnik[j];
    }

    delete[] reszta;
    delete[] wspolczynnik;

    wspolczynnik = wynik;
    stopien = nowyStopien;

    return *this;
}

Wielomian& Wielomian::operator/=(double liczba)
{
    if (liczba == 0) {
        cout << "Blad: dzielenie przez zero!" << endl;
        return *this;
    }

    for (int i = 0; i <= stopien; i++)
        wspolczynnik[i] /= liczba;

    return *this;
}

Wielomian Wielomian::operator+(const Wielomian& w) const
{
    Wielomian wynik(*this);
    wynik += w;
    return wynik;
}

Wielomian Wielomian::operator+(double liczba) const
{
    Wielomian wynik(*this);
    wynik += liczba;
    return wynik;
}

Wielomian operator+(double liczba, const Wielomian& w)
{
    return w + liczba;
}

Wielomian Wielomian::operator-(const Wielomian& w) const
{
    Wielomian wynik(*this);
    wynik -= w;
    return wynik;
}

Wielomian Wielomian::operator-(double liczba) const
{
    Wielomian wynik(*this);
    wynik -= liczba;
    return wynik;
}

Wielomian operator-(double liczba, const Wielomian& w)
{
    Wielomian wynik = w * (-1);
    wynik += liczba;
    return wynik;
}

Wielomian Wielomian::operator*(const Wielomian& w) const
{
    Wielomian wynik(*this);
    wynik *= w;
    return wynik;
}

Wielomian Wielomian::operator*(double liczba) const
{
    Wielomian wynik(*this);
    wynik *= liczba;
    return wynik;
}

Wielomian operator*(double liczba, const Wielomian& w)
{
    return w * liczba;
}

Wielomian Wielomian::operator/(const Wielomian& w) const
{
    Wielomian wynik(*this);
    wynik /= w;
    return wynik;
}

Wielomian Wielomian::operator/(double liczba) const
{
    Wielomian wynik(*this);
    wynik /= liczba;
    return wynik;
}

int Wielomian::PobierzStopien() const
{
    return stopien;
}

double Wielomian::PobierzWspolczynnik(int i) const
{
    if (i >= 0 && i <= stopien)
        return wspolczynnik[i];
    return 0;
}

double Wielomian::operator()(double x) const
{
    double wynik = 0;

    for (int i = stopien; i >= 0; i--)
        wynik = wynik * x + wspolczynnik[i];

    return wynik;
}

double Wielomian::operator[](int i) const
{
    if (i >= 0 && i <= stopien)
        return wspolczynnik[i];

    return 0;
}

void Wielomian::Pokaz() const
{
    cout << *this << endl;
}

ostream& operator<<(ostream& wyjscie, const Wielomian& w)
{
    int pierwszy = 1;

    for (int i = w.stopien; i >= 0; i--) {
        double a = w.wspolczynnik[i];

        if (a != 0) {
            if (pierwszy == 0 && a > 0)
                wyjscie << "+";
            if (a < 0)
                wyjscie << "-";

            if (i == 0) {
                if (a < 0)
                    wyjscie << -a;
                else
                    wyjscie << a;
            }
            else {
                if (a != 1 && a != -1) {
                    if (a < 0)
                        wyjscie << -a;
                    else
                        wyjscie << a;
                }

                wyjscie << "x";

                if (i > 1)
                    wyjscie << "^" << i;
            }

            pierwszy = 0;
        }
    }

    if (pierwszy == 1)
        wyjscie << "0";

    return wyjscie;
}

istream& operator>>(istream& wejscie, Wielomian& w)
{
    char napis[256];

    if (wejscie.getline(napis, 256)) {
        Wielomian nowy(napis);
        w = nowy;
    }

    return wejscie;
}

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

//wielomian.h
//wielomian.cpp
//main.cpp
