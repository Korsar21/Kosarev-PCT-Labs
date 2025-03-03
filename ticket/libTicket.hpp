#ifndef LIBTICKET_HPP
#define LIBTICKET_HPP

#include <iostream>

class Ticket {
 private:
    char* passengerName;
    int flightNumber;
    int price;
    bool hasTransfer;

 public:
    Ticket();
    Ticket(const char* addr, int f, int a, bool elevator);

    ~Ticket();

    Ticket(const Ticket& other);

    Ticket& operator=(const Ticket& other);

    const char* getPassengerName() const;
    int getFlightNumbers() const;
    int getPrice() const;
    bool getHasTransfer() const;

    void setPassengerName(const char* addr);
    void setFlightNumbers(int f);
    void setPrice(int a);
    void setHasTransfer(bool elevator);

    friend std::ostream& operator<<(std::ostream& os, const Ticket& ticket);
    friend std::istream& operator>>(std::istream& is, Ticket& ticket);

    bool operator<(const Ticket& other) const;
    bool operator>(const Ticket& other) const;
    bool operator==(const Ticket& other) const;

    static Ticket* readFromFile(const char* filename, int& count);
    static void writeToFile(const char* filename, Ticket* database, int count);
    static void sortTickets(Ticket* database, int count);
    static void addTicket(Ticket*& database, int& count, const Ticket& ticket);
    static void removeTicket(Ticket*& database, int& count, const char* ticketAddress);
    static bool editTicket(Ticket* database, int count, const char* ticketAddress, const Ticket& newTicketData);
    static void printTickets(Ticket* database, int count);
};

#endif
