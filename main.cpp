#include "planet.h"
#include <iostream>

int main() {
    Planet* planets = nullptr;
    int count = 0;

    Planet::readFromFile("planets.txt", planets, count);

    Planet::printPlanets(planets, count);

    Planet newPlanet("NewPlanet", 10000, true, 3);
    Planet::addPlanet(planets, count, newPlanet);

    Planet::sortPlanets(planets, count);

    Planet::printPlanets(planets, count);

    Planet::removePlanet(planets, count, 1);

    Planet::editPlanet(planets, count, 0);

    Planet::writeToFile("planets_output.txt", planets, count);

    delete[] planets;

    return 0;
}
