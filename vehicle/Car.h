#ifndef CAR_H
#define CAR_H

#include "Transport.h"
#include <cstring>
#include <iostream>

class Car : public Transport {
protected:
    char* brand;
public:
    Car(const char* n, int s, const char* b)
        : Transport(n, s) {
        brand = new char[strlen(b) + 1];
        strcpy(brand, b);
        std::cout << "Car()" << std::endl;
    }

    ~Car() override {
        delete[] brand;
        std::cout << "~Car()" << std::endl;
    }

    void show() const override {
        std::cout << "Автомобиль: " << name << ", скорость: " << speed
            << " км/ч, марка: " << brand << std::endl;
    }
};

#endif
