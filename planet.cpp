#include "planet.hpp"
#include <fstream>
#include <iostream>
#include "ticket/libTicket.hpp"
#include "planet/libPlanet.hpp"

int choiceLib() {
    int choice;
    std::cout << "Выберите библиотеку:\n";
    std::cout << "1. Planet\n";
    std::cout << "2. Ticket\n";
    std::cout << "Введите номер выбранной библиотеки: ";
    std::cin >> choice;

    while (choice != 1 && choice != 2) {
        std::cout << "Некорректный выбор. Попробуйте снова.\n";
        std::cout << "Введите номер выбранной библиотеки: ";
        std::cin >> choice;
    }

    return choice;
}

namespace planetSpace {

Planet FillPlanetsParametrs() {
    char newName[100];
    long long newDiameter;
    int newSatellites;
    bool newHasLife;

    std::cin.ignore();

    std::cout << "Enter planet name: ";
    std::cin.getline(newName, 100);

    std::cout << "Enter planet diameter: ";
    std::cin >> newDiameter;

    std::cout << "Enter number of satellites: ";
    std::cin >> newSatellites;

    std::cout << "Does the planet have life? (1 for yes, 0 for no): ";
    int lifeInput;
    std::cin >> lifeInput;
    newHasLife = lifeInput == 1;

    std::cin.ignore();

    Planet newPlanetData(newName, newDiameter, newSatellites, newHasLife);
    return newPlanetData;
}

int ChoicePlanetMethod() {
    int choice;
    while (true) {
        std::cout << "========== Меню ==========" << std::endl;
        std::cout << "1. Загрузить данные из файла\n";
        std::cout << "2. Сохранить данные в файл\n";
        std::cout << "3. Добавить новую планету\n";
        std::cout << "4. Удалить планету\n";
        std::cout << "5. Редактировать данные о планете\n";
        std::cout << "6. Сортировать планеты по диаметру\n";
        std::cout << "7. Вывести все планеты на экран\n";
        std::cout << "8. Выход\n";
        std::cout << "==========================" << std::endl;

        if (std::cin >> choice) {
            if (choice >= 1 && choice <= 8) {
                return choice;
            } else {
                std::cout << "Недопустимый выбор. Пожалуйста, выберите опцию от 1 до 8.\n";
            }
        } else {
            std::cout << "Некорректный ввод. Пожалуйста, введите целое число.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    }
}

template<typename T>
void switchPlanet(T* planets, int& count, const char* filename) {
    while (true) {
        switch (ChoicePlanetMethod()) {
            case 1:
                loadDataFromFile(planets, count, filename);
                break;

            case 2:
                saveDataToFile(planets, count, filename);
                break;

            case 3:
                addNewPlanet(planets, count);
                break;

            case 4:
                removePlanet(planets, count);
                break;

            case 5:
                editPlanet(planets, count);
                break;

            case 6:
                sortPlanetsByDiameter(planets, count);
                break;

            case 7:
                printAllPlanets(planets, count);
                break;

            case 8:
                delete[] planets;
                std::cout << "Выход из программы.\n";
                return;

            default:
                std::cout << "Некорректный выбор. Попробуйте снова.\n";
                break;
        }
    }
}

void loadDataFromFile(Planet*& planets, int& count, const char* filename) {
    planets = Planet::readFromFile(filename, count);
    std::cout << "Данные загружены из файла.\n";
}

void saveDataToFile(Planet* planets, int count, const char* filename) {
    Planet::writeToFile(filename, planets, count);
    std::cout << "Данные сохранены в файл.\n";
}

void addNewPlanet(Planet*& planets, int& count) {
    Planet newPlanet = FillPlanetsParametrs();
    Planet::addPlanet(planets, count, newPlanet);
    std::cout << "Планета добавлена.\n";
}

void removePlanet(Planet*& planets, int& count) {
    char name[100];
    std::cout << "Введите название планеты для удаления: ";
    std::cin >> name;
    Planet::removePlanet(planets, count, name);
}

void editPlanet(Planet* planets, int count) {
    char name[100];
    std::cout << "Введите название планеты для редактирования: ";
    std::cin >> name;

    Planet newPlanetData = FillPlanetsParametrs();

    Planet::editPlanet(planets, count, name, newPlanetData);
}

void sortPlanetsByDiameter(Planet* planets, int count) {
    Planet::sortPlanets(planets, count);
    std::cout << "Планеты отсортированы по диаметру.\n";
}

void printAllPlanets(Planet* planets, int count) {
    Planet::printPlanets(planets, count);
}
}  // namespace planetSpace

namespace ticketSpace {
int ChoiceTicketMethod() {
    int choice;
    while (true) {
        std::cout << "========== Меню ==========" << std::endl;
        std::cout << "1. Загрузить данные из файла\n";
        std::cout << "2. Сохранить данные в файл\n";
        std::cout << "3. Добавить новый билет\n";
        std::cout << "4. Удалить билет\n";
        std::cout << "5. Редактировать данные о билете\n";
        std::cout << "6. Сортировать билеты по цене\n";
        std::cout << "7. Вывести все билеты на экран\n";
        std::cout << "8. Выход\n";
        std::cout << "==========================" << std::endl;

        if (std::cin >> choice) {
            if (choice >= 1 && choice <= 8) {
                return choice;
            } else {
                std::cout << "Недопустимый выбор. Пожалуйста, выберите опцию от 1 до 8.\n";
            }
        } else {
            std::cout << "Некорректный ввод. Пожалуйста, введите целое число.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    }
}

template<typename T>
void switchTicket(T* tickets, int& count, const char* filename) {
    while (true) {
        switch (ChoiceTicketMethod()) {
            case 1:
                loadDataFromFileTicket(tickets, count, filename);
                break;

            case 2:
                saveDataToFileTicket(tickets, count, filename);
                break;

            case 3:
                addNewTicket(tickets, count);
                break;

            case 4:
                removeTicket(tickets, count);
                break;

            case 5:
                editTicket(tickets, count);
                break;

            case 6:
                sortTicketsByPrice(tickets, count);
                break;

            case 7:
                printAllTickets(tickets, count);
                break;

            case 8:
                delete[] tickets;
                std::cout << "Выход из программы.\n";
                return;

            default:
                std::cout << "Некорректный выбор. Попробуйте снова.\n";
                break;
        }
    }
}

void loadDataFromFileTicket(Ticket*& tickets, int& count, const char* filename) {
    tickets = Ticket::readFromFile(filename, count);
    std::cout << "Данные загружены из файла.\n";
}

void saveDataToFileTicket(Ticket* tickets, int count, const char* filename) {
    Ticket::writeToFile(filename, tickets, count);
    std::cout << "Данные сохранены в файл.\n";
}

void addNewTicket(Ticket*& tickets, int& count) {
    Ticket newTicket = FillTicketParametrs();
    Ticket::addTicket(tickets, count, newTicket);
    std::cout << "Билет добавлен.\n";
}

void removeTicket(Ticket*& tickets, int& count) {
    char name[100];
    std::cout << "Введите имя пассажира для удаления: ";
    std::cin >> name;
    Ticket::removeTicket(tickets, count, name);
}

void editTicket(Ticket* tickets, int count) {
    char name[100];
    std::cout << "Введите имя пассажира для редактирования: ";
    std::cin >> name;

    Ticket newTicketData = FillTicketParametrs();

    Ticket::editTicket(tickets, count, name, newTicketData);
}

void sortTicketsByPrice(Ticket* tickets, int count) {
    Ticket::sortTickets(tickets, count);
    std::cout << "Билеты отсортированы по цене.\n";
}

void printAllTickets(Ticket* tickets, int count) {
    Ticket::printTickets(tickets, count);
}

Ticket FillTicketParametrs() {
    char name[100];
    std::cout << "Введите имя пассажира: ";
    std::cin >> name;
    int flightNumber;
    std::cout << "Введите номер рейса: ";
    std::cin >> flightNumber;
    int price;
    std::cout << "Введите стоимость: ";
    std::cin >> price;
    bool hasTransfer;
    std::cout << "Наличие пересадки (1 - да, 0 - нет): ";
    std::cin >> hasTransfer;

    return Ticket(name, flightNumber, price, hasTransfer);
}

}  // namespace ticketSpace

template void planetSpace::switchPlanet<Planet>(Planet* planets, int& count, const char* filename);
template void ticketSpace::switchTicket<Ticket>(Ticket* tickets, int& count, const char* filename);
