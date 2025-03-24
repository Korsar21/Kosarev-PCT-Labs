#include "Fraction.h"
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>

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
    if (denominator == 0) {
        std::cerr << "Ошибка: знаменатель равен 0" << std::endl;
        numerator = 0;
        denominator = 1;
        return;
    }

    int common_divisor = gcd(numerator, denominator);
    numerator /= common_divisor;
    denominator /= common_divisor;

    normalize();
}

void Fraction::normalize() {
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
}

bool hasZeroDenominator(const char* str) {
    if (!str || *str == '\0') return false;

    char* temp = new char[strlen(str) + 1];
    strcpy(temp, str);

    char* slashPos = nullptr;
    for (char* c = temp; *c; c++) {
        if (*c == '/') {
            slashPos = c;
            break;
        }
    }

    bool result = false;
    if (slashPos) {
        char* denomStart = slashPos + 1;
        while (*denomStart && isspace(*denomStart)) denomStart++;

        int denom = atoi(denomStart);
        if (denom == 0) {
            result = true;
        }
    }

    delete[] temp;
    return result;
}

Fraction::Fraction(int num, int denom) : numerator(num), denominator(denom) {
    // std::cout << "Вызван конструктор Fraction(int, int)" << std::endl;

    if (denominator == 0) {
        std::cerr << "Ошибка: знаменатель равен 0" << std::endl;
        numerator = 0;
        denominator = 1;
    } else {
        reduce();
    }
}

Fraction::Fraction(const Fraction& other) : numerator(other.numerator), denominator(other.denominator) {
    // std::cout << "Вызван конструктор копирования" << std::endl;
}

Fraction::Fraction(const char* str) : numerator(0), denominator(1) {
    // std::cout << "Вызван конструктор Fraction(const char*)" << std::endl;

    if (!str || *str == '\0') return;

    char* temp = new char[strlen(str) + 1];
    strcpy(temp, str);

    bool negative = false;
    char* ptr = temp;

    if (*ptr == '-') {
        negative = true;
        ptr++;
    } else if (*ptr == '+') {
        ptr++;
    }

    while (*ptr && isspace(*ptr)) ptr++;

    char* slashPos = nullptr;
    for (char* c = ptr; *c; c++) {
        if (*c == '/') {
            slashPos = c;
            break;
        }
    }

    if (slashPos) {

        char* numEnd = slashPos;
        while (numEnd > ptr && isspace(*(numEnd - 1))) numEnd--;
        char* numStart = ptr;

        char* wholeEnd = nullptr;
        for (char* c = ptr; c < numEnd; c++) {
            if (isspace(*c) && c > ptr && isdigit(*(c-1))) {
                wholeEnd = c;

                char* nextDigit = c + 1;
                while (*nextDigit && isspace(*nextDigit)) nextDigit++;
                if (*nextDigit && isdigit(*nextDigit)) {
                    break;
                }
                wholeEnd = nullptr;
            }
        }

        int whole = 0;
        int num = 0;

        if (wholeEnd) {
            char wholePartTemp = *wholeEnd;
            *wholeEnd = '\0';
            whole = atoi(numStart);
            *wholeEnd = wholePartTemp;

            numStart = wholeEnd;
            while (*numStart && isspace(*numStart)) numStart++;
        }

        char numTemp = *numEnd;
        *numEnd = '\0';
        num = atoi(numStart);
        *numEnd = numTemp;

        char* denomStart = slashPos + 1;
        while (*denomStart && isspace(*denomStart)) denomStart++;

        int denom = atoi(denomStart);

        if (denom == 0) {
            std::cerr << "Ошибка: знаменатель равен 0" << std::endl;
            numerator = 0;
            denominator = 1;
        } else {
            numerator = whole * denom + num;
            if (negative) numerator = -numerator;
            denominator = denom;
            reduce();
        }
    } else {
        char* end = ptr + strlen(ptr) - 1;
        while (end > ptr && isspace(*end)) {
            *end = '\0';
            end--;
        }

        int whole = atoi(ptr);
        numerator = whole;
        if (negative) numerator = -numerator;
        denominator = 1;
    }

    delete[] temp;
}

Fraction::Fraction(double value, int n_dec) : numerator(0), denominator(1) {
    // std::cout << "Вызван конструктор Fraction(double)" << std::endl;

    double abs_value = std::abs(value);
    int sign = (value < 0) ? -1 : 1;

    int multiplier = 1;
    for (int i = 0; i < n_dec; i++) {
        multiplier *= 10;
    }

    numerator = sign * static_cast<int>(round(abs_value * multiplier));
    denominator = multiplier;
    reduce();
}

std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
    int whole = frac.numerator / frac.denominator;
    int remainder = std::abs(frac.numerator) % frac.denominator;

    if (remainder == 0) {
        os << whole;
    } else if (std::abs(whole) == 0) {
        os << frac.numerator << "/" << frac.denominator;
    } else {
        if (whole < 0) {
            os << whole << " " << remainder << "/" << frac.denominator;
        } else {
            os << whole << " " << remainder << "/" << frac.denominator;
        }
    }

    return os;
}

std::istream& operator>>(std::istream& is, Fraction& frac) {
    char buffer[100] = {0};

    is.getline(buffer, sizeof(buffer));

    if (hasZeroDenominator(buffer)) {
        std::cerr << "Ошибка: знаменатель не может быть равен 0!" << std::endl;
        exit(1);
    }

    Fraction temp(buffer);
    frac = temp;

    return is;
}

Fraction Fraction::operator+(const Fraction& other) const {
    // std::cout << "Вызвана операция Fraction+Fraction" << std::endl;

    int new_num = numerator * other.denominator + other.numerator * denominator;
    int new_denom = denominator * other.denominator;

    return Fraction(new_num, new_denom);
}

Fraction& Fraction::operator+=(const Fraction& other) {
    // std::cout << "Вызвана операция Fraction+=Fraction" << std::endl;

    numerator = numerator * other.denominator + other.numerator * denominator;
    denominator = denominator * other.denominator;
    reduce();

    return *this;
}

Fraction Fraction::operator+(int value) const {
    // std::cout << "Вызвана операция Fraction+int" << std::endl;

    int new_num = numerator + value * denominator;
    return Fraction(new_num, denominator);
}

Fraction& Fraction::operator+=(int value) {
    // std::cout << "Вызвана операция Fraction+=int" << std::endl;

    numerator += value * denominator;
    reduce();

    return *this;
}

Fraction operator+(int value, const Fraction& frac) {
    // std::cout << "Вызвана операция int+Fraction" << std::endl;

    int new_num = value * frac.denominator + frac.numerator;
    return Fraction(new_num, frac.denominator);
}

Fraction::operator double() const {
    return static_cast<double>(numerator) / denominator;
}

Fraction Fraction::operator+(double value) const {
    // std::cout << "Вызвана операция Fraction+double" << std::endl;

    Fraction value_frac(value);
    return *this + value_frac;
}

Fraction& Fraction::operator+=(double value) {
    // std::cout << "Вызвана операция Fraction+=double" << std::endl;

    Fraction value_frac(value);
    *this += value_frac;

    return *this;
}

Fraction operator+(double value, const Fraction& frac) {
    // std::cout << "Вызвана операция double+Fraction" << std::endl;

    Fraction value_frac(value);
    return value_frac + frac;
}
