#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <iostream>
#include <cstring>

class Transport {
protected:
    char *name;
    int speed;

public:
    Transport(const char* n, int s) : speed(s) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        std::cout << "Transport()" << std::endl;
    }

    virtual ~Transport() {
        delete[] name;
        std::cout << "~Transport()" << std::endl;
    }

    virtual void show() const = 0;
};

#endif
