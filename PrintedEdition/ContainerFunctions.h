#ifndef CONTAINER_FUNCTIONS_H
#define CONTAINER_FUNCTIONS_H

#include "../MyVector/MyStack.h"
#include "PrintedEdition.h"

// Функция для вывода всех объектов в стеке
void print(const MyStack<PrintedEdition*>& stack);

// Функция для удаления объекта по индексу
void remove(MyStack<PrintedEdition*>& stack, int index);

// Функция для очистки стека и удаления всех объектов
void clear(MyStack<PrintedEdition*>& stack);

#endif // CONTAINER_FUNCTIONS_H
