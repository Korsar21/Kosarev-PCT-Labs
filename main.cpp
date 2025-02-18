#include <iostream>
#include "include/mymath2.h"


int main() {
    setlocale(LC_ALL, "Russian");
    std::cout << "Я умею умножать! Зацени 2*3 =";
    std::cout << mymath2::multiplication(2, 3) << std::endl;
    return 0;
}
