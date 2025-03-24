#ifndef TICKET_HPP
#define TICKET_HPP

#include <iostream>
#include <cstring>
#include "ticket/libTicket.hpp"
#include "planet/libPlanet.hpp"


int chooseLib();

namespace ticketSpace {

int ChoiceTicketMethod();

template<typename T>
void switchTicket(T* tickets, int& count, const char* filename);

void loadDataFromFileTicket(Ticket*& tickets, int& count, const char* filename);

void saveDataToFileTicket(Ticket* tickets, int count, const char* filename);

void addNewTicket(Ticket*& tickets, int& count);

void removeTicket(Ticket*& tickets, int& count);

void editTicket(Ticket* tickets, int count);

void sortTicketsByPrice(Ticket* tickets, int count);

void printAllTickets(Ticket* tickets, int count);

Ticket FillTicketParametrs();

}  // namespace ticketSpace

#endif
