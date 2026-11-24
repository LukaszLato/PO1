#include <iostream>

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

};

ostream& operator<<(ostream& wyjscie, const Wielomian& w);
istream& operator>>(istream& wejscie, Wielomian& w);

Wielomian operator+(double liczba, const Wielomian& w);
Wielomian operator-(double liczba, const Wielomian& w);
Wielomian operator*(double liczba, const Wielomian& w);
