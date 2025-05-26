// Planet.h
#pragma once
#include <iostream>
#include <string>

class Planet {
private:
    std::string name;
    int satellites;

public:
    Planet() : name(""), satellites(0) {}
    Planet(const std::string& n, int s) : name(n), satellites(s) {}

    const std::string& getName() const { return name; }
    int getSatellites() const { return satellites; }

    bool operator<(const Planet& other) const {
        return satellites < other.satellites;
    }

    friend std::ostream& operator<<(std::ostream& os, const Planet& p);
};

std::ostream& operator<<(std::ostream& os, const Planet& p) {
    os << p.name << " (" << p.satellites << " спутников)";
    return os;
}
