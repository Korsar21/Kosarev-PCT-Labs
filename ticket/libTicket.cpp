#include "libTicket.hpp"
#include <cstring>
#include <fstream>
#include <iostream>

Ticket::Ticket() : passengerName(nullptr), flightNumber(0), price(0), hasTransfer(false) {
}

Ticket::Ticket(const char* name, int f, int a, bool transfer) : flightNumber(f), price(a), hasTransfer(transfer) {
    passengerName = new char[strlen(name) + 1];
    std::strncpy(passengerName, name, strlen(name) + 1);
    passengerName[strlen(name)] = '\0';
}

Ticket::~Ticket() {
    delete[] passengerName;
}

Ticket::Ticket(const Ticket& other) : flightNumber(other.flightNumber), price(other.price), hasTransfer(other.hasTransfer) {
    passengerName = new char[strlen(other.passengerName) + 1];
    std::strncpy(passengerName, other.passengerName, strlen(other.passengerName) + 1);
    passengerName[strlen(other.passengerName)] = '\0';
}

Ticket& Ticket::operator=(const Ticket& other) {
    if (this != &other) {
        delete[] passengerName;
        passengerName = new char[strlen(other.passengerName) + 1];
        std::strncpy(passengerName, other.passengerName, strlen(other.passengerName) + 1);
        passengerName[strlen(other.passengerName)] = '\0';
        flightNumber = other.flightNumber;
        price = other.price;
        hasTransfer = other.hasTransfer;
    }
    return *this;
}

const char* Ticket::getPassengerName() const {
    return passengerName;
}
int Ticket::getFlightNumbers() const {
    return flightNumber;
}
int Ticket::getPrice() const {
    return price;
}
bool Ticket::getHasTransfer() const {
    return hasTransfer;
}

void Ticket::setPassengerName(const char* name) {
    delete[] passengerName;
    passengerName = new char[strlen(name) + 1];
    std::strncpy(passengerName, name, strlen(name) + 1);
    passengerName[strlen(name)] = '\0';
}
void Ticket::setFlightNumbers(int f) {
    flightNumber = f;
}
void Ticket::setPrice(int a) {
    price = a;
}
void Ticket::setHasTransfer(bool transfer) {
    hasTransfer = transfer;
}

std::ostream& operator<<(std::ostream& os, const Ticket& ticket) {
    os << ticket.passengerName << " " << ticket.flightNumber << " " << ticket.price << " " << (ticket.hasTransfer ? 1 : 0);
    return os;
}

std::istream& operator>>(std::istream& is, Ticket& ticket) {
    char buffer[256];
    is >> buffer >> ticket.flightNumber >> ticket.price >> ticket.hasTransfer;
    ticket.setPassengerName(buffer);
    return is;
}

bool Ticket::operator<(const Ticket& other) const {
    return flightNumber < other.flightNumber;
}

bool Ticket::operator>(const Ticket& other) const {
    return other < *this;
}

bool Ticket::operator==(const Ticket& other) const {
    return std::strcmp(passengerName, other.passengerName) == 0 && flightNumber == other.flightNumber && price == other.price &&
           hasTransfer == other.hasTransfer;
}

Ticket* Ticket::readFromFile(const char* filename, int& count) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        count = 0;
        return nullptr;
    }

    file >> count;
    if (count <= 0) {
        std::cerr << "Некорректное количество билетов в файле." << std::endl;
        file.close();
        return nullptr;
    }

    Ticket* database = new Ticket[count];

    for (int i = 0; i < count; ++i) {
        char name[100];
        int flightNumber;
        int price;
        bool hasTransfer;

        file >> name >> flightNumber >> price >> hasTransfer;

        database[i] = Ticket(name, flightNumber, price, hasTransfer);
    }

    file.close();
    return database;
}

void Ticket::writeToFile(const char* filename, Ticket* database, int count) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << count << '\n' << std::flush;

        for (int i = 0; i < count; ++i) {
            file << database[i] << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Не удалось открыть файл для записи: " << filename << std::endl;
    }
}

void Ticket::sortTickets(Ticket* database, int count) {
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (database[j] > database[j + 1]) {
                Ticket temp = database[j];
                database[j] = database[j + 1];
                database[j + 1] = temp;
            }
        }
    }
}

void Ticket::addTicket(Ticket*& database, int& count, const Ticket& ticket) {
    Ticket* newDatabase = new Ticket[count + 1];
    for (int i = 0; i < count; ++i) {
        newDatabase[i] = database[i];
    }
    newDatabase[count] = ticket;
    count++;
    delete[] database;
    database = newDatabase;
}

void Ticket::removeTicket(Ticket*& database, int& count, const char* namePassenger) {
    int indexToRemove = -1;
    for (int i = 0; i < count; ++i) {
        if (std::strcmp(database[i].getPassengerName(), namePassenger) == 0) {
            indexToRemove = i;
            break;
        }
    }

    if (indexToRemove == -1) {
        std::cerr << "Имя пассажира " << namePassenger << " не найдено." << std::endl;
        return;
    }

    Ticket* newDatabase = new Ticket[count - 1];
    int newIndex = 0;
    for (int i = 0; i < count; ++i) {
        if (i != indexToRemove) {
            newDatabase[newIndex++] = database[i];
        }
    }

    std::cout << "Билет на имя: " << '"' << namePassenger << '"' << " удален." << std::endl;

    count--;
    delete[] database;
    database = newDatabase;
}

bool Ticket::editTicket(Ticket* database, int count, const char* namePassenger, const Ticket& newTicketData) {
    for (int i = 0; i < count; ++i) {
        if (std::strcmp(database[i].getPassengerName(), namePassenger) == 0) {
            database[i] = newTicketData;
            return true;
        }
    }
    std::cerr << "Билет на имя: " << '"' << namePassenger << '"' << " не найден." << std::endl;
    return false;
}

void Ticket::printTickets(Ticket* database, int count) {
    for (int i = 0; i < count; ++i) {
        std::cout << database[i] << std::endl;
    }
}
