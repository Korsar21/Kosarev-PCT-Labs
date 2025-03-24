// fractionLib/Fraction.h
#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

class Fraction {
private:
    int numerator;   // числитель
    int denominator; // знаменатель

    // Вспомогательные функции
    void reduce();   // сокращение дроби
    int gcd(int a, int b) const; // наибольший общий делитель
    void normalize(); // нормализация дроби (перенос знака в числитель)

public:
    // Конструкторы
    Fraction(int num = 0, int denom = 1); // конструктор с двумя аргументами
    Fraction(const Fraction& other);       // конструктор копирования
    Fraction(const char* str);            // конструктор из строки
    Fraction(double value, int n_dec = 4); // конструктор из double

    // Перегруженные операторы ввода-вывода
    friend std::ostream& operator<<(std::ostream& os, const Fraction& frac);
    friend std::istream& operator>>(std::istream& is, Fraction& frac);

    // Операторы сложения для дробей
    Fraction operator+(const Fraction& other) const;
    Fraction& operator+=(const Fraction& other);

    // Операторы сложения для целых чисел
    Fraction operator+(int value) const;
    Fraction& operator+=(int value);
    friend Fraction operator+(int value, const Fraction& frac);

    // Операторы сложения для double
    Fraction operator+(double value) const;
    Fraction& operator+=(double value);
    friend Fraction operator+(double value, const Fraction& frac);

    // Конвертация в double для внутренних расчетов
    operator double() const;
};

#endif // FRACTION_H
