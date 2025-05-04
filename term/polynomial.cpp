#include "polynomial.h"
#include <sstream>
#include <string>
#include <cctype>

void Polynomial::resize(int newCapacity) {
    Term* newPoly = new Term[newCapacity];
    for (int i = 0; i < size; ++i) {
        newPoly[i] = poly[i];
    }
    delete[] poly;
    poly = newPoly;
    capacity = newCapacity;
}

void Polynomial::addTerm(const Term& term) {
    if (term.coefficient == 0) {
        return;
    }

    for (int i = 0; i < size; ++i) {
        if (poly[i].exponent == term.exponent) {
            poly[i].coefficient += term.coefficient;

            if (poly[i].coefficient == 0) {
                for (int j = i; j < size - 1; ++j) {
                    poly[j] = poly[j + 1];
                }
                --size;
            }

            updateDegree();
            sortTerms();
            return;
        }
    }

    if (size == capacity) {
        resize(capacity * 2);
    }

    poly[size++] = term;

    if (term.exponent > degree) {
        degree = term.exponent;
    }

    sortTerms();
}

void Polynomial::updateDegree() {
    degree = 0;
    for (int i = 0; i < size; ++i) {
        if (poly[i].exponent > degree) {
            degree = poly[i].exponent;
        }
    }
}

void Polynomial::sortTerms() {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            bool shouldSwap;

            if (order_ == ASCENDING) {
                shouldSwap = poly[j].exponent > poly[j + 1].exponent;
            } else {
                shouldSwap = poly[j].exponent < poly[j + 1].exponent;
            }

            if (shouldSwap) {
                Term temp = poly[j];
                poly[j] = poly[j + 1];
                poly[j + 1] = temp;
            }
        }
    }
}

Polynomial::Polynomial() : poly(new Term[10]), size(0), capacity(10), degree(0), order_(DESCENDING) {}

Polynomial::Polynomial(int constant) : poly(new Term[10]), size(0), capacity(10), degree(0), order_(DESCENDING) {
    if (constant != 0) {
        addTerm(Term(constant, 0));
    }
}

Polynomial::Polynomial(const Term& term) : poly(new Term[10]), size(0), capacity(10), degree(0), order_(DESCENDING) {
    if (term.coefficient != 0) {
        addTerm(term);
    }
}

Polynomial::Polynomial(const Polynomial& other) : poly(new Term[other.capacity]), size(other.size), capacity(other.capacity), degree(other.degree), order_(other.order_) {
    for (int i = 0; i < size; ++i) {
        poly[i] = other.poly[i];
    }
}

Polynomial::~Polynomial() {
    delete[] poly;
}

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        delete[] poly;
        capacity = other.capacity;
        size = other.size;
        degree = other.degree;
        order_ = other.order_;

        poly = new Term[capacity];
        for (int i = 0; i < size; ++i) {
            poly[i] = other.poly[i];
        }
    }
    return *this;
}

Polynomial& Polynomial::operator+=(const Polynomial& other) {
    for (int i = 0; i < other.size; ++i) {
        addTerm(other.poly[i]);
    }
    return *this;
}

Polynomial& Polynomial::operator-=(const Polynomial& other) {
    for (int i = 0; i < other.size; ++i) {
        Term negatedTerm(-(other.poly[i].coefficient), other.poly[i].exponent);
        addTerm(negatedTerm);
    }
    return *this;
}
Polynomial& Polynomial::operator*=(const Polynomial& other) {
    Polynomial result;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < other.size; ++j) {
            int coef = poly[i].coefficient * other.poly[j].coefficient;
            int exp = poly[i].exponent + other.poly[j].exponent;
            result.addTerm(Term(coef, exp));
        }
    }

    *this = result;
    return *this;
}

Polynomial operator+(const Polynomial& p1, const Polynomial& p2) {
    Polynomial result = p1;
    result += p2;
    return result;
}

Polynomial operator-(const Polynomial& p1, const Polynomial& p2) {
    Polynomial result = p1;
    result -= p2;
    return result;
}

Polynomial operator*(const Polynomial& p1, const Polynomial& p2) {
    Polynomial result = p1;
    result *= p2;
    return result;
}

std::istream& operator>>(std::istream& is, Polynomial& poly) {
    poly = Polynomial();

    std::string input;
    std::getline(is, input);

    if (input == ""){
        return is;
    }

    input = "    " + input + " + 0    ";
    if (!input.empty() && input[0] != '+' && input[0] != '-') {
        input = "     +" + input;
    }

    size_t pos = 0;
    while (pos < input.length()) {
        while (pos < input.length() && std::isspace(input[pos])) {
            pos++;
        }

        if (pos >= input.length()) {
            break;
        }

        bool isNegative = (input[pos] == '-');
        pos++;

        while (pos < input.length() && std::isspace(input[pos])) {
            pos++;
        }

        size_t termStart = pos;
        size_t termEnd = pos;

        while (termEnd < input.length()) {
            if (input[termEnd] == '+' || input[termEnd] == '-') {
                break;
            }
            termEnd++;
        }

        std::string termStr = input.substr(termStart, termEnd - termStart);

        std::istringstream termStream(termStr);
        Term term;
        termStream >> term;

        if (isNegative) {
            term.setCoefficient(-term.getCoefficient());
        }

        poly.addTerm(term);

        pos = termEnd;
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& poly) {
    if (poly.size == 0) {
        return os << "0";
    }

    bool firstTerm = true;

    for (int i = 0; i < poly.size; ++i) {
        const Term& term = poly.poly[i];

        if (term.getCoefficient() == 0) {
            continue;
        }

        if (firstTerm) {
            firstTerm = false;

            if (term.getCoefficient() < 0) {
                if (term.getCoefficient() == -1) {
                    if (term.getExponent() == 0) {
                        os << "-1";
                    } else if (term.getExponent() == 1) {
                        os << "-x";
                    } else {
                        os << "-x^" << term.getExponent();
                    }
                } else {
                    if (term.getExponent() == 0) {
                        os << term.getCoefficient();
                    } else if (term.getExponent() == 1) {
                        os << term.getCoefficient() << "x";
                    } else {
                        os << term.getCoefficient() << "x^" << term.getExponent();
                    }
                }
            } else {
                if (term.getCoefficient() == 1) {
                    if (term.getExponent() == 0) {
                        os << "1";
                    } else if (term.getExponent() == 1) {
                        os << "x";
                    } else {
                        os << "x^" << term.getExponent();
                    }
                } else {
                    if (term.getExponent() == 0) {
                        os << term.getCoefficient();
                    } else if (term.getExponent() == 1) {
                        os << term.getCoefficient() << "x";
                    } else {
                        os << term.getCoefficient() << "x^" << term.getExponent();
                    }
                }
            }
        } else {
            if (term.getCoefficient() > 0) {
                os << " + ";

                if (term.getCoefficient() == 1) {
                    if (term.getExponent() == 0) {
                        os << "1";
                    } else if (term.getExponent() == 1) {
                        os << "x";
                    } else {
                        os << "x^" << term.getExponent();
                    }
                } else {
                    if (term.getExponent() == 0) {
                        os << term.getCoefficient();
                    } else if (term.getExponent() == 1) {
                        os << term.getCoefficient() << "x";
                    } else {
                        os << term.getCoefficient() << "x^" << term.getExponent();
                    }
                }
            } else {
                os << " - ";

                if (term.getCoefficient() == -1) {
                    if (term.getExponent() == 0) {
                        os << "1";
                    } else if (term.getExponent() == 1) {
                        os << "x";
                    } else {
                        os << "x^" << term.getExponent();
                    }
                } else {
                    if (term.getExponent() == 0) {
                        os << -term.getCoefficient();
                    } else if (term.getExponent() == 1) {
                        os << -term.getCoefficient() << "x";
                    } else {
                        os << -term.getCoefficient() << "x^" << term.getExponent();
                    }
                }
            }
        }
    }

    return os;
}
