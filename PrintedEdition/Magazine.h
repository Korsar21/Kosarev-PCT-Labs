#include "PrintedEdition.h"

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
