#ifndef PLANET_HPP
#define PLANET_HPP

#include <iostream>
#include <string>
#include "ticket/libTicket.hpp"
#include "planet/libPlanet.hpp"

int choiceLib();

namespace planetSpace {

Planet FillPlanetsParametrs();

int ChoicePlanetMethod();

template<typename T>
void switchPlanet(T* planets, int& count, const char* filename);

void loadDataFromFile(Planet*& planets, int& count, const char* filename);

void saveDataToFile(Planet* planets, int count, const char* filename);

void addNewPlanet(Planet*& planets, int& count);

void removePlanet(Planet*& planets, int& count);

void editPlanet(Planet* planets, int count);

void sortPlanetsByDiameter(Planet* planets, int count);

void printAllPlanets(Planet* planets, int count);

}  // namespace planetSpace

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
