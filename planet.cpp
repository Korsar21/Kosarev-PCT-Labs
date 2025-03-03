#include "planet.h"
#include <cstring>
#include <algorithm>

int Planet::total = 0;

Planet::Planet() : name(nullptr), diameter(0), hasLife(false), numMoons(0) {
    total++;
    std::cout << "Создание ID " << total << std::endl;
}

Planet::Planet(const char* name, int diameter, bool hasLife, int numMoons) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
    this->diameter = diameter;
    this->hasLife = hasLife;
    this->numMoons = numMoons;
    total++;
    std::cout << "Создание ID " << total << std::endl;
}

Planet::Planet(const Planet& other) {
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    diameter = other.diameter;
    hasLife = other.hasLife;
    numMoons = other.numMoons;
    total++;
    std::cout << "Создание ID " << total << " (копирование)" << std::endl;
}

Planet::~Planet() {
    delete[] name;
    total--;
    std::cout << "Удаление ID " << total + 1 << std::endl;
}

Planet& Planet::operator=(const Planet& other) {
    if (this != &other) {
        delete[] name;
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        diameter = other.diameter;
        hasLife = other.hasLife;
        numMoons = other.numMoons;
    }
    return *this;
}

const char* Planet::getName() const { return name; }
int Planet::getDiameter() const { return diameter; }
bool Planet::getHasLife() const { return hasLife; }
int Planet::getNumMoons() const { return numMoons; }

void Planet::setName(const char* name) {
    delete[] this->name;
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

void Planet::setDiameter(int diameter) { this->diameter = diameter; }
void Planet::setHasLife(bool hasLife) { this->hasLife = hasLife; }
void Planet::setNumMoons(int numMoons) { this->numMoons = numMoons; }

std::ostream& operator<<(std::ostream& os, const Planet& planet) {
    os << planet.name << " " << planet.diameter << " " << planet.hasLife << " " << planet.numMoons;
    return os;
}

std::istream& operator>>(std::istream& is, Planet& planet) {
    char buffer[100];
    is >> buffer >> planet.diameter >> planet.hasLife >> planet.numMoons;
    planet.setName(buffer);
    return is;
}

bool Planet::operator<(const Planet& other) const {
    return diameter < other.diameter;
}

bool Planet::operator==(const Planet& other) const {
    return strcmp(name, other.name) == 0 && diameter == other.diameter &&
           hasLife == other.hasLife && numMoons == other.numMoons;
}

void Planet::readFromFile(const char* filename, Planet*& planets, int& count) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return;
    }
    file >> count;
    planets = new Planet[count];
    for (int i = 0; i < count; i++) {
        file >> planets[i];
    }
    file.close();
}

void Planet::writeToFile(const char* filename, Planet* planets, int count) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return;
    }
    file << count << std::endl;
    for (int i = 0; i < count; i++) {
        file << planets[i] << std::endl;
    }
    file.close();
}

void Planet::sortPlanets(Planet* planets, int count) {
    std::sort(planets, planets + count);
}

void Planet::addPlanet(Planet*& planets, int& count, const Planet& newPlanet) {
    Planet* newPlanets = new Planet[count + 1];
    for (int i = 0; i < count; i++) {
        newPlanets[i] = planets[i];
    }
    newPlanets[count] = newPlanet;
    delete[] planets;
    planets = newPlanets;
    count++;
}

void Planet::removePlanet(Planet*& planets, int& count, int index) {
    if (index < 0 || index >= count) return;
    Planet* newPlanets = new Planet[count - 1];
    for (int i = 0, j = 0; i < count; i++) {
        if (i != index) {
            newPlanets[j++] = planets[i];
        }
    }
    delete[] planets;
    planets = newPlanets;
    count--;
}

void Planet::editPlanet(Planet* planets, int count, int index) {
    if (index < 0 || index >= count) return;
    std::cout << "Введите новые данные для планеты:" << std::endl;
    std::cin >> planets[index];
}

void Planet::printPlanets(Planet* planets, int count) {
    for (int i = 0; i < count; i++) {
        std::cout << planets[i] << std::endl;
    }
}
