#include <iostream>
#include "mymath/mymath.h"
#include "mymath2/mymath2.h"


int main() {
    setlocale(LC_ALL, "Russian");
    std::cout << "Я умею суммировать! Зацени 1+1=";
    std::cout << mymath::sum(1, 1) << std::endl;
    std::cout << "Я умею умножать! Зацени 2*3 =";
    std::cout << mymath2::multiplication(2, 3) << std::endl;
    return 0;
}
