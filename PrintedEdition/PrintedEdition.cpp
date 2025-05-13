#include "PrintedEdition.h"

// PrintedEdition implementations
PrintedEdition::PrintedEdition(const std::string& t, int y) : title(t), year(y) {
    std::cout << "PrintedEdition()" << std::endl;
}

PrintedEdition::~PrintedEdition() {
    std::cout << "~PrintedEdition()" << std::endl;
}

// Book implementations
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

// Textbook implementations
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

// Magazine implementations
Magazine::Magazine(const std::string& t, int y, const std::string& p, int i)
    : PrintedEdition(t, y), publisher(p), issue(i) {
    std::cout << "Magazine()" << std::endl;
}

Magazine::~Magazine() {
    std::cout << "~Magazine()" << std::endl;
}

void Magazine::show() const {
    std::cout << "=== Журнал ===" << std::endl;
    std::cout << "Название: " << title << std::endl;
    std::cout << "Год: " << year << std::endl;
    std::cout << "Издатель: " << publisher << std::endl;
    std::cout << "Номер выпуска: " << issue << std::endl;
}
