#include <algorithm>
#include <cstring>
#include <iostream>
#include <limits>
#include "vehicle/Car.h"
#include "vehicle/Train.h"
#include "vehicle/Express.h"
#include "lib/stack.h"

void print(const MyStack<Transport*>& container) {
    if (container.empty()) {
        std::cout << "Контейнер пуст!" << std::endl;
        return;
    }

    MyStack<Transport*> temp(container);
    std::size_t i = 0;

    while (!temp.empty()) {
        std::cout << "index " << i++ << ": ";
        temp.topInf()->show();
        temp.pop();
    }
}

void remove(MyStack<Transport*>& container, std::size_t index) {
    if (container.empty()) {
        std::cerr << "Контейнер пуст!" << std::endl;
        return;
    }

    MyStack<Transport*> temp;
    std::size_t currentSize = 0;

    MyStack<Transport*> counter(container);
    while (!counter.empty()) {
        currentSize++;
        counter.pop();
    }

    if (index >= currentSize) {
        std::cerr << "Invalid index!" << std::endl;
        return;
    }

    for (std::size_t i = 0; i < index; ++i) {
        temp.push(container.topInf());
        container.pop();
    }

    Transport* toDelete = container.topInf();
    container.pop();
    delete toDelete;

    while (!temp.empty()) {
        container.push(temp.topInf());
        temp.pop();
    }
}

void clear(MyStack<Transport*>& container) {
    while (!container.empty()) {
        Transport* toDelete = container.topInf();
        container.pop();
        delete toDelete;
    }
}

int main() {
    MyStack<Transport*> container;
    int choice = -1;
    char bufferName[100];
    char bufferInfo[100];

    while (choice != 0) {
        std::cout << "\nМеню:\n"
                  << "1. Добавить автомобиль\n"
                  << "2. Добавить поезд\n"
                  << "3. Добавить экспресс\n"
                  << "4. Вывести все транспортные средства\n"
                  << "5. Удалить по индексу\n"
                  << "6. Очистить контейнер\n"
                  << "0. Выход\n"
                  << "Выберите действие: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                std::cout << "Введите название: ";
                std::cin.getline(bufferName, 100);

                std::cout << "Введите скорость: ";
                int speed;
                std::cin >> speed;
                std::cin.ignore();

                std::cout << "Введите марку: ";
                std::cin.getline(bufferInfo, 100);

                container.push(new Car(bufferName, speed, bufferInfo));
                break;
            }
            case 2: {
                std::cout << "Введите название: ";
                std::cin.getline(bufferName, 100);

                std::cout << "Введите скорость: ";
                int speed;
                std::cin >> speed;
                std::cin.ignore();

                std::cout << "Введите тип: ";
                std::cin.getline(bufferInfo, 100);

                container.push(new Train(bufferName, speed, bufferInfo));
                break;
            }
            case 3: {
                std::cout << "Введите название: ";
                std::cin.getline(bufferName, 100);

                std::cout << "Введите скорость: ";
                int speed;
                std::cin >> speed;
                std::cin.ignore();

                std::cout << "Введите маршрут: ";
                std::cin.getline(bufferInfo, 100);

                container.push(new Express(bufferName, speed, bufferInfo));
                break;
            }
            case 4:
                print(container);
                break;
            case 5: {
                std::size_t index;
                std::cout << "Введите индекс: ";
                std::cin >> index;
                remove(container, index);
                break;
            }
            case 6:
                clear(container);
                break;
            case 0:
                clear(container);
                break;
            default:
                std::cout << "Неверный выбор!" << std::endl;
        }
    }

    return 0;
}
