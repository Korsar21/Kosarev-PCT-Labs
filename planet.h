#ifndef PLANET_H
#define PLANET_H

#include <iostream>
#include <fstream>

class Planet {
private:
    char* name;
    int diameter;
    bool hasLife;
    int numMoons;
    static int total;

public:
    Planet();
    Planet(const char* name, int diameter, bool hasLife, int numMoons);
    Planet(const Planet& other); // Конструктор копирования
    ~Planet();

    Planet& operator=(const Planet& other);

    const char* getName() const;
    int getDiameter() const;
    bool getHasLife() const;
    int getNumMoons() const;
    void setName(const char* name);
    void setDiameter(int diameter);
    void setHasLife(bool hasLife);
    void setNumMoons(int numMoons);

    friend std::ostream& operator<<(std::ostream& os, const Planet& planet);
    friend std::istream& operator>>(std::istream& is, Planet& planet);

    bool operator<(const Planet& other) const;
    bool operator==(const Planet& other) const;

    static void readFromFile(const char* filename, Planet*& planets, int& count);
    static void writeToFile(const char* filename, Planet* planets, int count);
    static void sortPlanets(Planet* planets, int count);
    static void addPlanet(Planet*& planets, int& count, const Planet& newPlanet);
    static void removePlanet(Planet*& planets, int& count, int index);
    static void editPlanet(Planet* planets, int count, int index);
    static void printPlanets(Planet* planets, int count);
};

#endif // PLANET_H
