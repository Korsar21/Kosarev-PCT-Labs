#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
#include <stdexcept>
#include <string>

class Fraction {
private:
    int m_numerator;
    int m_denominator;

    void reduce();
    int gcd(int a, int b) const;
    void normalize();
    static bool isValidFractionString(const char* str);

public:
    Fraction(int num = 0, int denom = 1);
    Fraction(const Fraction& other);
    Fraction(const char* str);
    explicit Fraction(double value, int nDec = 4);

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
