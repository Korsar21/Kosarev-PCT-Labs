#include "Fraction.h"
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <algorithm>


bool Fraction::isValidFractionString(const char* str) {
    if (!str || *str == '\0') return false;

    std::string s(str);
    s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());

    if (s.empty()) return false;

    size_t slashPos = s.find('/');

    if (slashPos != std::string::npos) {
        if (slashPos == 0 || slashPos == s.length() - 1) return false;

        std::string numStr = s.substr(0, slashPos);
        std::string denomStr = s.substr(slashPos + 1);

        auto isValidNumber = [](const std::string& num) -> bool {
            if (num.empty()) return false;
            size_t start = 0;
            if (num[0] == '+' || num[0] == '-') start = 1;
            if (start == num.length()) return false;

            for (size_t i = start; i < num.length(); ++i) {
                if (!isdigit(num[i])) return false;
            }
            return true;
        };

        if (!isValidNumber(numStr)) return false;
        if (!isValidNumber(denomStr)) return false;

        int denom = std::stoi(denomStr);
        if (denom == 0) return false;
    } else {
        auto isValidInteger = [](const std::string& num) -> bool {
            if (num.empty()) return false;
            size_t start = 0;
            if (num[0] == '+' || num[0] == '-') start = 1;
            if (start == num.length()) return false;

            for (size_t i = start; i < num.length(); ++i) {
                if (!isdigit(num[i])) return false;
            }
            return true;
        };

        if (!isValidInteger(s)) return false;
    }

    return true;
}

int Fraction::gcd(int a, int b) const {
    a = std::abs(a);
    b = std::abs(b);
    while (b) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void Fraction::reduce() {
    if (m_denominator == 0) {
        throw std::invalid_argument("Denominator cannot be zero");
    }

    int commonDivisor = gcd(m_numerator, m_denominator);
    m_numerator /= commonDivisor;
    m_denominator /= commonDivisor;

    normalize();
}

void Fraction::normalize() {
    if (m_denominator < 0) {
        m_numerator = -m_numerator;
        m_denominator = -m_denominator;
    }
}

Fraction::Fraction(int num, int denom) : m_numerator(num), m_denominator(denom) {
    if (m_denominator == 0) {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    reduce();
}

Fraction::Fraction(const Fraction& other) : m_numerator(other.m_numerator), m_denominator(other.m_denominator) {
}

Fraction::Fraction(const char* str) : m_numerator(0), m_denominator(1) {
    if (!str || *str == '\0') {
        throw std::invalid_argument("Empty string input");
    }

    if (!isValidFractionString(str)) {
        throw std::invalid_argument("Invalid fraction format");
    }

    std::string s(str);
    s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());

    bool negative = false;
    size_t i = 0;

    if (s[i] == '-') {
        negative = true;
        i++;
    } else if (s[i] == '+') {
        i++;
    }

    size_t slashPos = s.find('/');

    if (slashPos != std::string::npos) {
        std::string numStr = s.substr(i, slashPos - i);
        std::string denomStr = s.substr(slashPos + 1);

        m_numerator = std::stoi(numStr);
        m_denominator = std::stoi(denomStr);

        if (negative) m_numerator = -m_numerator;
    } else {
        m_numerator = std::stoi(s.substr(i));
        m_denominator = 1;
    }

    reduce();
}

Fraction::Fraction(double value, int nDec) : m_numerator(0), m_denominator(1) {
    double absValue = std::abs(value);
    int sign = (value < 0) ? -1 : 1;

    int multiplier = 1;
    for (int i = 0; i < nDec; i++) {
        multiplier *= 10;
    }

    m_numerator = sign * static_cast<int>(round(absValue * multiplier));
    m_denominator = multiplier;
    reduce();
}

std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
    bool isNegative = frac.m_numerator < 0;
    int absNum = std::abs(frac.m_numerator);
    int whole = absNum / frac.m_denominator;
    int remainder = absNum % frac.m_denominator;

    if (remainder == 0) {
        os << (isNegative ? "-" : "") << whole;
    } else if (whole == 0) {
        os << (isNegative ? "-" : "") << remainder << "/" << frac.m_denominator;
    } else {
        os << (isNegative ? "-" : "") << whole << " " << remainder << "/" << frac.m_denominator;
    }

    return os;
}

std::istream& operator>>(std::istream& is, Fraction& frac) {
    char buffer[100] = {0};
    is.getline(buffer, sizeof(buffer));

    try {
        Fraction temp(buffer);
        frac = temp;
    } catch (const std::invalid_argument& e) {
        is.setstate(std::ios::failbit);
        throw std::invalid_argument(
            "Некорректный формат дроби."
            );
    }

    return is;
}

Fraction Fraction::operator+(const Fraction& other) const {
    int newNum = m_numerator * other.m_denominator + other.m_numerator * m_denominator;
    int newDenom = m_denominator * other.m_denominator;
    return Fraction(newNum, newDenom);
}

Fraction& Fraction::operator+=(const Fraction& other) {
    m_numerator = m_numerator * other.m_denominator + other.m_numerator * m_denominator;
    m_denominator = m_denominator * other.m_denominator;
    reduce();
    return *this;
}

Fraction Fraction::operator+(int value) const {
    return *this + Fraction(value);
}

Fraction& Fraction::operator+=(int value) {
    *this += Fraction(value);
    return *this;
}

Fraction operator+(int value, const Fraction& frac) {
    return Fraction(value) + frac;
}

Fraction Fraction::operator+(double value) const {
    return *this + Fraction(value);
}

Fraction& Fraction::operator+=(double value) {
    *this += Fraction(value);
    return *this;
}

Fraction operator+(double value, const Fraction& frac) {
    return Fraction(value) + frac;
}

Fraction::operator double() const {
    return static_cast<double>(m_numerator) / m_denominator;
}
