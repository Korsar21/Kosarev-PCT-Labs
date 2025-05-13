#ifndef PRINTED_EDITION_H
#define PRINTED_EDITION_H

#include <iostream>
#include <string>

// Абстрактный базовый класс
class PrintedEdition {
protected:
    std::string title;
    int year;

public:
    PrintedEdition(const std::string& t, int y);
    virtual ~PrintedEdition();

    std::string getTitle() const { return title; }
    int getYear() const { return year; }

    virtual void show() const = 0; // Абстрактный метод
};

// Производный класс Книга
class Book : public PrintedEdition {
protected:
    std::string author;
    int pages;

public:
    Book(const std::string& t, int y, const std::string& a, int p);
    ~Book() override;
    void show() const override;
};

// Производный класс Учебник
class Textbook : public Book {
private:
    std::string subject;
    int grade;

public:
    Textbook(const std::string& t, int y, const std::string& a, int p,
            const std::string& s, int g);
    ~Textbook() override;
    void show() const override;
};

// Производный класс Журнал
class Magazine : public PrintedEdition {
    protected:
        std::string publisher;
        int issue;

    public:
        Magazine(const std::string& t, int y, const std::string& p, int i);
        virtual ~Magazine();

        // Добавляем геттеры
        std::string getPublisher() const { return publisher; }
        int getIssue() const { return issue; }

        void show() const override;
    };

#endif // PRINTED_EDITION_H
