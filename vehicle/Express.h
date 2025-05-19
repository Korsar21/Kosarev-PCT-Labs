#ifndef EXPRESS_H
#define EXPRESS_H

#include "Transport.h"
#include <cstring>

class Express : public Transport {
protected:
    char* route;
public:
    Express(const char* n, int s, const char* r)
        : Transport(n, s) {
        route = new char[strlen(r) + 1];
        strcpy(route, r);
        std::cout << "Express()" << std::endl;
    }

    ~Express() override {
        delete[] route;
        std::cout << "~Express()" << std::endl;
    }

    void show() const override {
        std::cout << "Экспресс: " << name << ", скорость: " << speed
            << " км/ч, маршрут: " << route << std::endl;
    }
};

#endif
