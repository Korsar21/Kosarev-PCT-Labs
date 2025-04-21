#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

class Fraction {
private:
    int numerator;
    int denominator;

    void simplify();
    static int gcd(int a, int b);

public:
   // Fraction();
    Fraction(int num=0, int den = 1);
    Fraction(const char* str);
    Fraction(double d);

    friend std::ostream& operator<<(std::ostream& os, const Fraction& f);
    friend std::istream& operator>>(std::istream& is, Fraction& f);

    Fraction operator+(const Fraction& other) const;
    Fraction& operator+=(const Fraction& other);

    Fraction operator+(int i) const;
    Fraction& operator+=(int i);

    Fraction operator+(double d) const;
    Fraction& operator+=(double d);

    friend Fraction operator+(int i, const Fraction& f);
    friend Fraction operator+(double d, const Fraction& f);
};

#endif
