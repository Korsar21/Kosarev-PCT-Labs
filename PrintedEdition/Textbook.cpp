#include "PrintedEdition.h"

Textbook::Textbook(const std::string& t, int y, const std::string& a, int p,
                  const std::string& s, int g)
    : Book(t, y, a, p), subject(s), grade(g) {
    std::cout << "Textbook()" << std::endl;
}

Textbook::~Textbook() {
    std::cout << "~Textbook()" << std::endl;
}

void Textbook::show() const {
    std::cout << "=== Учебник ===" << std::endl;
    std::cout << "Название: " << title << std::endl;
    std::cout << "Год: " << year << std::endl;
    std::cout << "Автор: " << author << std::endl;
    std::cout << "Страниц: " << pages << std::endl;
    std::cout << "Предмет: " << subject << std::endl;
    std::cout << "Класс: " << grade << std::endl;
}
