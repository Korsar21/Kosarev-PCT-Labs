#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

class Fraction {
private:
    int numerator;
    int denominator;

    void reduce();
    int gcd(int a, int b) const;
    void normalize();

public:
    Fraction(int num = 0, int denom = 1);
    Fraction(const Fraction& other);
    Fraction(const char* str);
    Fraction(double value, int n_dec = 4);

    friend std::ostream& operator<<(std::ostream& os, const Fraction& frac);
    friend std::istream& operator>>(std::istream& is, Fraction& frac);

    Fraction operator+(const Fraction& other) const;
    Fraction& operator+=(const Fraction& other);

    Fraction operator+(int value) const;
    Fraction& operator+=(int value);
    friend Fraction operator+(int value, const Fraction& frac);

    Fraction operator+(double value) const;
    Fraction& operator+=(double value);
    friend Fraction operator+(double value, const Fraction& frac);

    operator double() const;
};

#endif // FRACTION_H
