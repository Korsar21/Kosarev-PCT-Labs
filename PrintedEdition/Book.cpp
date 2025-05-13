#include "PrintedEdition.h"

Book::Book(const std::string& t, int y, const std::string& a, int p)
    : PrintedEdition(t, y), author(a), pages(p) {
    std::cout << "Book()" << std::endl;
}

Book::~Book() {
    std::cout << "~Book()" << std::endl;
}

void Book::show() const {
    std::cout << "=== Книга ===" << std::endl;
    std::cout << "Название: " << title << std::endl;
    std::cout << "Год: " << year << std::endl;
    std::cout << "Автор: " << author << std::endl;
    std::cout << "Страниц: " << pages << std::endl;
}
