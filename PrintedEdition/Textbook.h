#ifndef TEXTBOOK_H
#define TEXTBOOK_H

#include "PrintedEdition.h"
#include <string>

class Textbook : public Book {
protected:
    std::string subject;
    std::string gradeLevel;

public:
    Textbook(const std::string& t, int y, const std::string& a, int p,
             const std::string& s, const std::string& g);
    virtual ~Textbook();

    void show() const override;
};

#endif // TEXTBOOK_H
