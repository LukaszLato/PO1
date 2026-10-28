
#include <iostream>
#include <cstring>  // strlen
#include <cstdlib>  // strtol i strtod

typedef struct {
    float* wspolczynnik;
    int stopien;
} Wielomian;

char* UsunOdstepy(const char* napis) {
    char* napis2;
    int y = 0, dlugosc = strlen(napis);
    napis2 = new char[dlugosc + 1];

    for (int i = 0; i < dlugosc; i++)
        if (napis[i] != ' ')
            napis2[y++] = napis[i];

    napis2[y] = 0;
    return napis2;
}

int OkreslStopien(const char* napis) {
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

float* PrzydzielPamiec(int stopien) {
    float* tab = new float[stopien + 1];

    for (int i = 0; i <= stopien; i++)
        tab[i] = 0.0f;

    return tab;
}

const char* AnalizujJednomian(const char* napis, Wielomian* w)
{
    int wykladnik = 0;
    int znak = 1;
    float wspolczynnik;

    if (*napis == '-')
    {
        napis++;
        znak = -1;
    }
    else
        if (*napis == '+')
            napis++;

    if (*napis == 'x')
        wspolczynnik = 1;
    else {
        char* koniec;
        wspolczynnik = strtod(napis, &koniec);
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

    w->wspolczynnik[wykladnik] += znak * wspolczynnik;
    return napis;
}

void AnalizujJednomiany(const char* napis, Wielomian* w) {
    while (*napis)
        napis = AnalizujJednomian(napis, w);
}

Wielomian Analizuj(const char* napis)
{
    char* bezOdstepow = UsunOdstepy(napis);
    Wielomian w;

    w.stopien = OkreslStopien(bezOdstepow);
    w.wspolczynnik = PrzydzielPamiec(w.stopien);

    AnalizujJednomiany(bezOdstepow, &w);

    delete[] bezOdstepow;  
    return w;             
}

void Pokaz(Wielomian w)
{
    int pierwszy = 1;

    for (int i = w.stopien; i >= 0; i--)
    {
        float a = w.wspolczynnik[i];

        if (a != 0)
        {
            if (pierwszy == 0 && a > 0)
                std::cout << "+";

            if (a < 0)
                std::cout << "-";

            if (i == 0)
            {
                if (a < 0)
                    std::cout << -a;
                else
                    std::cout << a;
            }
            else
            {
                if (a != 1 && a != -1)
                {
                    if (a < 0)
                        std::cout << -a;
                    else
                        std::cout << a;
                }

                std::cout << "x";

                if (i > 1)
                    std::cout << "^" << i;
            }

            pierwszy = 0;
        }
    }

    if (pierwszy == 1)
        std::cout << "0";

    std::cout << std::endl;
}

int main()
{
    const char* napis = "x^3-x^2+2x-7.5";

    Wielomian w = Analizuj(napis);
    Pokaz(w);

    delete[] w.wspolczynnik;  
    return 0;                 
}
