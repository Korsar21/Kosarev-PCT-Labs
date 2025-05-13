#include <iostream>
#include "MyVector/MyStack.h"
#include "PrintedEdition/PrintedEdition.h"
#include "PrintedEdition/ContainerFunctions.h"

int main() {
    // Создаем стек для хранения указателей на объекты
    MyStack<PrintedEdition*> editions;

    int choice = 0;
    bool running = true;

    while (running) {
        std::cout << "\n=== Меню ===\n";
        std::cout << "1. Добавить книгу\n";
        std::cout << "2. Добавить учебник\n";
        std::cout << "3. Добавить журнал\n";
        std::cout << "4. Показать все элементы\n";
        std::cout << "5. Удалить элемент по индексу\n";
        std::cout << "6. Очистить все элементы\n";
        std::cout << "7. Демо-режим\n";
        std::cout << "8. Выход\n";
        std::cout << "Введите ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string title, author;
                int year, pages;

                std::cout << "Введите название: ";
                std::cin.ignore();
                std::getline(std::cin, title);

                std::cout << "Введите год: ";
                std::cin >> year;

                std::cout << "Введите автора: ";
                std::cin.ignore();
                std::getline(std::cin, author);

                std::cout << "Введите количество страниц: ";
                std::cin >> pages;

                editions.append(new Book(title, year, author, pages));
                std::cout << "Книга успешно добавлена" << std::endl;
                break;
            }
            case 2: {
                std::string title, author, subject;
                int year, pages, grade;

                std::cout << "Введите название: ";
                std::cin.ignore();
                std::getline(std::cin, title);

                std::cout << "Введите год: ";
                std::cin >> year;

                std::cout << "Введите автора: ";
                std::cin.ignore();
                std::getline(std::cin, author);

                std::cout << "Введите количество страниц: ";
                std::cin >> pages;

                std::cout << "Введите предмет: ";
                std::cin.ignore();
                std::getline(std::cin, subject);

                std::cout << "Введите класс: ";
                std::cin >> grade;

                editions.append(new Textbook(title, year, author, pages, subject, grade));
                std::cout << "Учебник успешно добавлен" << std::endl;
                break;
            }
            case 3: {
                std::string title, publisher;
                int year, issue;

                std::cout << "Введите название: ";
                std::cin.ignore();
                std::getline(std::cin, title);

                std::cout << "Введите год: ";
                std::cin >> year;

                std::cout << "Введите издателя: ";
                std::cin.ignore();
                std::getline(std::cin, publisher);

                std::cout << "Введите номер выпуска: ";
                std::cin >> issue;

                editions.append(new Magazine(title, year, publisher, issue));
                std::cout << "Журнал успешно добавлен" << std::endl;
                break;
            }
            case 4:
                print(editions);
                break;
            case 5: {
                int index;
                std::cout << "Введите индекс для удаления: ";
                std::cin >> index;
                remove(editions, index);
                break;
            }
            case 6:
                clear(editions);
                break;
            case 7:
                // Демонстрационный режим
                clear(editions);  // Очищаем сначала

                editions.append(new Book("Война и мир", 1869, "Лев Толстой", 1225));
                editions.append(new Textbook("Физика 101", 2020, "Доктор Смит", 350, "Физика", 10));
                editions.append(new Magazine("National Geographic", 2023, "NGS", 256));
                editions.append(new Book("Преступление и наказание", 1866, "Федор Достоевский", 671));

                std::cout << "Демонстрационные элементы успешно добавлены" << std::endl;
                print(editions);
                break;
            case 8:
                running = false;
                clear(editions);  // Очищаем перед выходом
                std::cout << "Выход из программы..." << std::endl;
                break;
            default:
                std::cout << "Неверный выбор. Пожалуйста, попробуйте снова." << std::endl;
        }
    }

    return 0;
}
