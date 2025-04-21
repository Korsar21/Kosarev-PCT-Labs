#include "Fraction.h"
#include <cstdlib>
#include <cmath>

const int N_DEC = 4;


Fraction::Fraction(int num, int den) : numerator(num), denominator(den) {
    if (denominator == 0) {
        throw std::invalid_argument("Знаменатель не может быть равен нулю!!!");
    }
    simplify();
}

Fraction::Fraction(const char* str) {
    char* end;
    numerator = strtol(str, &end, 10);

    if (*end == '/') {
        denominator = strtol(end + 1, nullptr, 10);
    } else if (*end == ' ') {
        int whole = numerator;
        numerator = strtol(end + 1, &end, 10);
        if (*end == '/') {
            denominator = strtol(end + 1, nullptr, 10);
            if (whole < 0) {
                numerator = whole * denominator - numerator;
            } else {
                numerator = whole * denominator + numerator;
            }
        } else {
            denominator = 1;
        }
    } else {
        denominator = 1;
    }

    if (denominator == 0) {
        throw std::invalid_argument("Ошибка формата ввода!!!");
    }

    simplify();
}

Fraction::Fraction(double d) {
    int sign = (d >= 0) ? 1 : -1;
    d = std::abs(d);

    int wholePart = static_cast<int>(d);
    double fractionalPart = d - wholePart;

    int den = std::pow(10, N_DEC);
    int num = std::round(fractionalPart * den);

    numerator = sign * (wholePart * den + num);
    denominator = den;

    simplify();
}

void Fraction::simplify() {
    int g = gcd(std::abs(numerator), denominator);
    numerator /= g;
    denominator /= g;

    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
}

int Fraction::gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

std::ostream& operator<<(std::ostream& os, const Fraction& f) {
    if (f.numerator == 0) {
        return os << "0";
    }

    int whole = f.numerator / f.denominator;
    int num = std::abs(f.numerator % f.denominator);

    if (whole != 0) {
        os << whole;
        if (num != 0) {
            os << ' ' << num << '/' << f.denominator;
        }
    } else {
        os << f.numerator << '/' << f.denominator;
    }

    return os;
}

std::istream& operator>>(std::istream& is, Fraction& f) {
    char buffer[100];
    is.getline(buffer, 100);

        for (int i = 0; buffer[i] != '\0'; i++) {
            if (!(isdigit(buffer[i]) || buffer[i] == '/' || buffer[i] == ' ' || buffer[i] == '-' || buffer[i] == '+')) {
                throw std::invalid_argument("Некорректный ввод: строка содержит недопустимые символы");
            }
        }

        if (buffer[0] == '\0') {
            throw std::invalid_argument("Пустая строка ввода");
        }

        f = Fraction(buffer);

    return is;
}


Fraction Fraction::operator+(const Fraction& other) const {
    int num = numerator * other.denominator + other.numerator * denominator;
    int den = denominator * other.denominator;
    return Fraction(num, den);
}

Fraction& Fraction::operator+=(const Fraction& other) {
    *this = *this + other;
    return *this;
}

Fraction Fraction::operator+(int i) const {
    return *this + Fraction(i);
}

Fraction& Fraction::operator+=(int i) {
    *this = *this + i;
    return *this;
}

Fraction Fraction::operator+(double d) const {
    return *this + Fraction(d);
}

Fraction& Fraction::operator+=(double d) {
    *this = *this + d;
    return *this;
}

Fraction operator+(int i, const Fraction& f) {
    return f + i;
}

Fraction operator+(double d, const Fraction& f) {
    return f + d;
}
