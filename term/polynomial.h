#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "term.h"
#include <iostream>

class Polynomial {
private:
    Term* poly;
    int size;
    int capacity;
    int degree;

    enum Order {
        ASCENDING,
        DESCENDING
    };
    Order order_;

    void resize(int newCapacity);
    void addTerm(const Term& term);
    void updateDegree();
    void sortTerms();

public:
    Polynomial();
    Polynomial(int constant);
    Polynomial(const Term& term);
    Polynomial(const Polynomial& other);
    ~Polynomial();

    Polynomial& operator=(const Polynomial& other);
    Polynomial& operator+=(const Polynomial& other);
    Polynomial& operator-=(const Polynomial& other);
    Polynomial& operator*=(const Polynomial& other);


    friend Polynomial operator+(const Polynomial& p1, const Polynomial& p2);
    friend Polynomial operator-(const Polynomial& p1, const Polynomial& p2);
    friend Polynomial operator*(const Polynomial& p1, const Polynomial& p2);


    friend std::istream& operator>>(std::istream& is, Polynomial& poly);
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);
};

#endif // POLYNOMIAL_H
