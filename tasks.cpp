#include "tasks.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <list>
#include <map>
#include <vector>
#include <cctype>
#include "Point.h"
#include "Planet.h"

void task1() {
    std::cout << "Выполняется Задание №1\n";
    std::string text;
    std::cout << "Введите текст: ";
    std::getline(std::cin, text);

    size_t firstSpace = text.find(' ');
    if (firstSpace == std::string::npos) {
        std::cout << "Ошибка: в тексте должно быть хотя бы два слова\n";
        return;
    }

    size_t secondWordStart = firstSpace + 1;
    if (secondWordStart >= text.length()) {
        std::cout << "Ошибка: второе слово отсутствует\n";
        return;
    }

    if (text.length() > 0) {
        char temp = text[0];
        text[0] = text[secondWordStart];
        text[secondWordStart] = temp;
    }

    std::cout << "Результат: " << text << std::endl;
}

void task2() {
    std::cout << "Выполняется Задание №2\n";
    std::string text;
    std::cout << "Введите текст: ";
    std::getline(std::cin, text);

    std::string result;
    for (char c : text) {
        if (c != ',') {
            result += c;
        }
    }

    std::cout << "Результат (без запятых): " << result << std::endl;
}

void task3() {
    std::cout << "Выполняется Задание №3\n";
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");
    char ch;

    if (!inputFile.is_open()) {
        std::cerr << "Ошибка: не удалось открыть input.txt\n";
        return;
    }
    if (!outputFile.is_open()) {
        std::cerr << "Ошибка: не удалось создать output.txt\n";
        return;
    }

    while (inputFile.get(ch)) {
        if (!ispunct(static_cast<unsigned char>(ch))) {
            outputFile << ch;
        }
    }

    inputFile.close();
    outputFile.close();
    std::cout << "Файл обработан. Результат записан в output.txt\n";
}

void PrintVec(const std::vector<float>& v) {
    for (float num : v) {
        std::cout << num << " ";
    }
    std::cout << "\n\n";
}

void task4() {
    std::cout << "Выполняется Задание №4\n";

    std::vector<float> numbers;
    for (int i = 0; i < 25; ++i) {
        numbers.push_back(static_cast<float>(i) * 1.5f);
    }

    std::cout << "Исходный вектор:\n";
    PrintVec(numbers);

    if (numbers.size() > 1) {
        numbers.erase(numbers.begin() + 1);
    }

    std::cout << "После удаления элемента с индексом 1:\n";
    PrintVec(numbers);
}

void PrintPoints(const std::vector<Point>& points) {
    for (const auto& p : points) {
        std::cout << p << std::endl;
    }
    std::cout << std::endl;
}

void task5() {
    std::cout << "Выполняется Задание №5\n";

    std::vector<Point> points = {
        Point(1.2, 6.3),
        Point(4.0, 0.7),
        Point(7.2, 0.8),
        Point(5.3, 3.0),
        Point(4.9, 6.6),
        Point(9.3, 0.2)
    };

    std::cout << "Исходные точки:\n";
    for (const auto& p : points) {
        std::cout << p << std::endl;
    }

    auto maxIt = std::max_element(points.begin(), points.end(),
        [](const Point& a, const Point& b) {
            return a.distanceToOrigin() < b.distanceToOrigin();
        });

    std::cout << "\nСамая удаленная точка: " << *maxIt
              << " (расстояние: " << maxIt->distanceToOrigin() << ")\n";

    double shift;
    std::cout << "\nВведите величину сдвига по оси X: ";
    std::cin >> shift;

    for (auto& p : points) {
        p.x -= shift;
    }

    std::cout << "\nТочки после сдвига:\n";
    for (const auto& p : points) {
        std::cout << p << std::endl;
    }
}

void PrintList(const std::list<int>& lst) {
    for (int num : lst) {
        std::cout << num << " ";
    }
    std::cout << "\n\n";
}

void task6() {
    std::cout << "Выполняется Задание №6\n";

    std::list<int> numbers = {1, -2, 3, -4, 5, -6};

    std::cout << "Исходный список:\n";
    PrintList(numbers);

    auto it = numbers.begin();
    while (it != numbers.end()) {
        numbers.insert(std::next(it), -*it);
        std::advance(it, 2);
    }

    std::cout << "После добавления элементов:\n";
    PrintList(numbers);

    numbers.remove_if([](int n) { return n < 0; });

    std::cout << "После удаления отрицательных элементов:\n";
    PrintList(numbers);
}

void task7() {
    std::cout << "Выполняется Задание №7\n";

    std::list<Planet> planets = {
        Planet("Меркурий", 0),
        Planet("Венера", 0),
        Planet("Земля", 1),
        Planet("Марс", 2),
        Planet("Юпитер", 69),
        Planet("Сатурн", 62),
        Planet("Уран", 27),
        Planet("Нептун", 14),
        Planet("Плутон", 10)
    };

    std::cout << "Список планет:\n";
    for (const auto& planet : planets) {
        std::cout << planet << std::endl;
    }

    auto maxIt = std::max_element(planets.begin(), planets.end());
    std::cout << "\nПланета с наибольшим количеством спутников: "
              << *maxIt << std::endl;
}

void task8() {
    std::cout << "Выполняется Задание №8\n";

    std::map<char, int> charMap = {
        {'A', 1},
        {'B', 2},
        {'C', 3},
        {'D', 4},
        {'E', 5}
    };

    std::cout << "Исходное отображение:\n";
    for (const auto& pair : charMap) {
        std::cout << pair.first << " : " << pair.second << std::endl;
    }

    charMap.erase('C');

    std::cout << "\nПосле удаления пары с ключом 'C':\n";
    for (const auto& pair : charMap) {
        std::cout << pair.first << " : " << pair.second << std::endl;
    }
}

void task9() {
    std::cout << "Выполняется Задание №9\n";

    std::string states[] = {"Wyoming", "Colorado", "Nevada", "Montana", "Arizona", "Idaho"};
    int pops[] = {470, 2890, 800, 787, 2718, 944};

    std::map<std::string, int> statePopulation;
    for (size_t i = 0; i < 6; ++i) {
        statePopulation[states[i]] = pops[i];
    }

    std::cout << "Все штаты и население (в тыс.):\n";
    for (const auto& pair : statePopulation) {
        std::cout << pair.first << " : " << pair.second << std::endl;
    }

    std::string input;
    do {
        std::cout << "\nВведите название штата: ";
        std::getline(std::cin, input);

        if (input != "exit") {
            auto it = statePopulation.find(input);
            if (it != statePopulation.end()) {
                std::cout << "Население: " << it->second << " тыс. человек\n";
            } else {
                std::cout << "Штат не найден!\n";
            }
        }
    } while (input != "exit");
}
