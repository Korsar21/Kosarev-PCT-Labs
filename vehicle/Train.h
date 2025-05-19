#ifndef TRAIN_H
#define TRAIN_H

#include "Transport.h"
#include <cstring>

class Train : public Transport {
protected:
    char* type;
public:
    Train(const char* n, int s, const char* t)
        : Transport(n, s) {
        type = new char[strlen(t) + 1];
        strcpy(type, t);
        std::cout << "Train()" << std::endl;
    }

    ~Train() override {
        delete[] type;
        std::cout << "~Train()" << std::endl;
    }

    void show() const override {
        std::cout << "Поезд: " << name << ", скорость: " << speed
            << " км/ч, тип: " << type << std::endl;
    }
};

#endif
