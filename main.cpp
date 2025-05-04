#include <iostream>
#include <string>
#include "term/term.h"
#include "term/polynomial.h"

void demoTerm() {
    std::cout << "Демонстрация класса Term:" << std::endl;

    Term t1(-5, 2);  // -5x^2
    Term t2(1, 2);  // x^2
    Term t3(3, 5);  // 3x^5
    Term t4(2, 1);  // 2x
    Term t5(3);  // 3

    std::cout << "t1 = " << t1 << std::endl;
    std::cout << "t2 = " << t2 << std::endl;
    std::cout << "t3 = " << t3 << std::endl;
    std::cout << "t4 = " << t4 << std::endl;
    std::cout << "t5 = " << t5 << std::endl;

    Term t6 = t1 + t2;
    std::cout << "t1 + t2 = " << t6 << std::endl;
}

void demoPolynomial() {
    std::cout << "Демонстрация класса Polynomial" << std::endl;

    Polynomial p1;  // 0
    Polynomial p2(3);  // 3
    Polynomial p3(Term(5, 2));  // 5x^2

    std::cout << "p1 = " << p1 << std::endl;
    std::cout << "p2 = " << p2 << std::endl;
    std::cout << "p3 = " << p3 << std::endl;

    Polynomial p4 = p2 + p3;  // 3 + 5x^2
    std::cout << "p3 + p2 = " << p4 << std::endl;

    Polynomial p5 = p2 * p3;
    std::cout << "p2 * p3 = " << p5 << std::endl;

    p1 += p2;
    std::cout << "p1 += p2: " << p1 << std::endl;

    p1 *= p3;
    std::cout << "p2 *= p3: " << p1 << std::endl;
}

int main() {
    char choice1;
    std::cout << "Выберите режим:" << std::endl;
    std::cout << "1. Демонстрационный режим" << std::endl;
    std::cout << "2. Интерактивный режим" << std::endl;
    std::cout << "Выбор: ";
    std::cin >> choice1;

    if (choice1 == '1') {
        char choice2;
        std::cout << "Выберите класс:" << std::endl;
        std::cout << "1. Term" << std::endl;
        std::cout << "2. Polynomial" << std::endl;
        std::cout << "Выбор: ";
        std::cin >> choice2;

        if (choice2 == '1')
            demoTerm();
        else if (choice2 == '2')
            demoPolynomial();

    } else if (choice1 == '2') {
        char choice2;
        std::cout << "Выберите класс:" << std::endl;
        std::cout << "1. Term" << std::endl;
        std::cout << "2. Polynomial" << std::endl;
        std::cout << "Выбор: ";
        std::cin >> choice2;

        if (choice2 == '1') {

            std::cout << "Операции с term'ами" << std::endl;
            std::cout << "Введите первый term: ";
            Term t1;
            std::cin >> t1;
            std::cout << "Распознанный term: " << t1 << std::endl;

            std::cout << "Введите второй term (с той же степенью): ";
            Term t2;
            std::cin >> t2;
            std::cout << "Распознанный term: " << t2 << std::endl;

            try {
                Term t3 = t1 + t2;
                std::cout << "t1 + t2: " << t3 << std::endl;
            } catch (const std::invalid_argument& e) {
                std::cout << "Ошибка: " << e.what() << std::endl;
            }

    } else if (choice2 == '2') {

            std::cout << "Операции с полиномами" << std::endl;
            std::cout << "Введите первый полином: " << std::endl;
            std::cin.ignore();
            Polynomial p1;
            std::cin >> p1;
            std::cout << "Распознанный полином: " << std::endl << p1 << std::endl;

            std::cout << "Введите второй полином: " << std::endl;
            Polynomial p2;
            std::cin >> p2;
            std::cout << "Распознанный полином: " << std::endl << p2 << std::endl;

            Polynomial p3 = p1 + p2;
            std::cout << "p3 = p1 + p2 = " << p3 << std::endl;


            Polynomial p5 = p1 - p2;
            std::cout << "p5 = p1 - p2 = " << p5 << std::endl;

            Polynomial p4 = p1 * p2;
            std::cout << "p4 = p1 * p2 = " << p4 << std::endl;

        }
    } else {
        std::cout << "Неверный выбор!" << std::endl;
    }

    char choice;
    std::cout << "Для продолжения нажмите 1" << std::endl;
    std::cout << "Для выхода нажмите любую клавишу" << std::endl;
    std::cout << "Выбор: ";
    std::cin >> choice;
    if (choice == '1')
        return main();

    return 0;
}
