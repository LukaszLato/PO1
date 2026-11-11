#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

class Wielomian
{
private:
    float* wspolczynnik;
    int stopien;

    const char* AnalizujJednomian(const char* napis);
    void AnalizujJednomiany(const char* napis);

public:
    Wielomian();
    Wielomian(const char* napis);
    Wielomian(const Wielomian& w);
    Wielomian(const float* tablica, int liczbaWspolczynnikow);
    ~Wielomian();

    Wielomian& operator=(const Wielomian& w);

    int PobierzStopien() const;
    float PobierzWspolczynnik(int i) const;
    void Pokaz() const;
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

float* PrzydzielPamiec(int stopien)
{
    float* tab = new float[stopien + 1];
    for (int i = 0; i <= stopien; i++)
        tab[i] = 0.0f;
    return tab;
}

const char* Wielomian::AnalizujJednomian(const char* napis)
{
    int wykladnik = 0;
    int znak = 1;
    float wsp;

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

Wielomian::Wielomian(const float* tablica, int liczbaWspolczynnikow)
{
    if (liczbaWspolczynnikow <= 0 || tablica == nullptr) {
        stopien = 0;
        wspolczynnik = PrzydzielPamiec(stopien);
    }
    else {
        stopien = liczbaWspolczynnikow - 1;
        wspolczynnik = PrzydzielPamiec(stopien);
        for (int i = 0; i < liczbaWspolczynnikow; i++)
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
        float* nowaTablica = PrzydzielPamiec(w.stopien);
        for (int i = 0; i <= w.stopien; i++)
            nowaTablica[i] = w.wspolczynnik[i];

        delete[] wspolczynnik;
        wspolczynnik = nowaTablica;
        stopien = w.stopien;
    }
    return *this;
}

int Wielomian::PobierzStopien() const
{
    return stopien;
}

float Wielomian::PobierzWspolczynnik(int i) const
{
    if (i >= 0 && i <= stopien)
        return wspolczynnik[i];
    return 0;
}

void Wielomian::Pokaz() const
{
    int pierwszy = 1;

    for (int i = stopien; i >= 0; i--) {
        float a = wspolczynnik[i];
        if (a != 0) {
            if (pierwszy == 0 && a > 0)
                cout << "+";
            if (a < 0)
                cout << "-";

            if (i == 0) {
                if (a < 0)
                    cout << -a;
                else
                    cout << a;
            }
            else {
                if (a != 1 && a != -1) {
                    if (a < 0)
                        cout << -a;
                    else
                        cout << a;
                }
                cout << "x";
                if (i > 1)
                    cout << "^" << i;
            }
            pierwszy = 0;
        }
    }
    if (pierwszy == 1)
        cout << "0";
    cout << endl;
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

    float tablica[] = { -7.5f, 2.0f, -1.0f, 1.0f };
    Wielomian zTablicy(tablica, 4);
    cout << "Z tablicy: ";
    zTablicy.Pokaz();

    cout << "Stopien: " << zTablicy.PobierzStopien() << endl;
    cout << "Wspolczynnik przy x^2: " << zTablicy.PobierzWspolczynnik(2) << endl;

    pusty = oryginal;
    cout << "Po przypisaniu: ";
    pusty.Pokaz();

    return 0;
}
