#include <fstream>
#include <iostream>
#include "ticket/libTicket.hpp"
#include "planet/libPlanet.hpp"
#include "planet.hpp"

int main() {
    int choice = choiceLib();
    int count = 0;
    Planet* planetDataBase = nullptr;
    Ticket* ticketDataBase = nullptr;
    const char* filename;

    switch (choice) {
        case 1: {
            filename = "planets.txt";
            planetSpace::switchPlanet(planetDataBase, count, filename);
            break;
        }
        case 2: {
            filename = "tickets.txt";
            ticketSpace::switchTicket(ticketDataBase, count, filename);
            break;
        }
        default:
            std::cout << "Некорректный выбор.\n";
            return 1;
    }

    if (choice == 1 && planetDataBase != nullptr) {
        delete[] planetDataBase;
    } else if (choice == 2 && ticketDataBase != nullptr) {
        delete[] ticketDataBase;
    }

    return 0;
}
