#include "term.h"

Term::Term() : coefficient(0), exponent(0) {}
Term::Term(int coef) : coefficient(coef), exponent(0) {}
Term::Term(int coef, int exp) : coefficient(coef), exponent(exp) {}

int Term::getCoefficient() const { return coefficient; }
int Term::getExponent() const { return exponent; }

void Term::setCoefficient(int c) {coefficient = c;}
void Term::setExponent(int c) {exponent = c;}

Term operator+(const Term& t1, const Term& t2) {
    if (t1.exponent != t2.exponent) {
        throw std::invalid_argument("Нельзя складывать term'ы с разными степенями");
    }
    return Term(t1.coefficient + t2.coefficient, t1.exponent);
}

std::istream& operator>>(std::istream& is, Term& term) {
    is >> std::ws;

    int coef = 1;
    int exp = 0;

    if (isdigit(is.peek())) {
        is >> coef;
    }

    is >> std::ws;
    if (is.peek() == 'x') {
        is.get();
        exp = 1;


        is >> std::ws;
        if (is.peek() == '^') {
            is.get();
            is >> std::ws;
            is >> exp;
        }
    }

    term.coefficient = coef;
    term.exponent = exp;

    return is;
}

std::ostream& operator<<(std::ostream& os, const Term& term) {
    if (term.coefficient == 0) {
        return os;
    }

    if (term.exponent == 0) {
        os << term.coefficient;
    } else if (term.exponent == 1) {
        if (term.coefficient == 1) {
            os << "x";
        } else if (term.coefficient == -1) {
            os << "-x";
        } else {
            os << term.coefficient << "x";
        }
    } else {
        if (term.coefficient == 1) {
            os << "x^" << term.exponent;
        } else if (term.coefficient == -1) {
            os << "-x^" << term.exponent;
        } else {
            os << term.coefficient << "x^" << term.exponent;
        }
    }

    return os;
}
