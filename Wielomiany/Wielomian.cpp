#include "Wielomian.h"
#include <cstring>
#include <cstdlib>

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

    for (int i = w.PobierzStopien(); i >= 0; i--) {
        double a = w.PobierzWspolczynnik(i);

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
