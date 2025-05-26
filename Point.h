#pragma once
#include <iostream>
#include <cmath>

class Point {
public:
    double x, y;

    Point() : x(0), y(0) {}
    Point(double a, double b) : x(a), y(b) {}

    double distanceToOrigin() const {
        return std::sqrt(x*x + y*y);
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& p);
};

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}
