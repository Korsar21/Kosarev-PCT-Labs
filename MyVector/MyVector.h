#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <iostream>
#include <algorithm>
#include <cstring>
#include "MyStack.h" // Подключаем MyStack

template <typename T = int>
class MyVector {
protected:
    MyStack<T> stack;  // Используем MyStack вместо массива
    size_t size;       // Текущий размер
    size_t max_size;   // Максимальный размер

    // Вспомогательная функция для получения элемента по индексу
    T getAt(size_t index) const {
        if(index >= size) throw std::out_of_range("Index out of range");

        MyStack<T> tempStack = stack; // Создаем копию стека

        // Извлекаем элементы до нужного индекса
        for(size_t i = 0; i < size - index - 1; ++i) {
            tempStack.pop();
        }

        return tempStack.get();
    }

public:
    // Конструкторы
    MyVector(size_t initial_size = 1) : size(0), max_size(initial_size) {}

    MyVector(const T& first_element) : size(1), max_size(1) {
        stack.append(first_element);
    }

    MyVector(const MyVector& other) : size(other.size), max_size(other.max_size) {
        // Копируем элементы из other.stack в правильном порядке
        MyStack<T> temp;
        MyStack<T> otherCopy = other.stack;

        while(!otherCopy.any()) {
            temp.append(otherCopy.get());
            otherCopy.pop();
        }

        while(!temp.any()) {
            stack.append(temp.get());
            temp.pop();
        }
    }

    virtual ~MyVector() {
        while(!stack.any()) {
            stack.pop();
        }
    }

    MyVector& operator=(const MyVector& other) {
        if(this == &other) return *this;

        // Очищаем текущий стек
        while(!stack.any()) {
            stack.pop();
        }

        size = other.size;
        max_size = other.max_size;

        // Копируем элементы из other.stack в правильном порядке
        MyStack<T> temp;
        MyStack<T> otherCopy = other.stack;

        while(!otherCopy.any()) {
            temp.append(otherCopy.get());
            otherCopy.pop();
        }

        while(!temp.any()) {
            stack.append(temp.get());
            temp.pop();
        }

        return *this;
    }

    virtual void add_element(const T& element) {
        // Добавляем элемент в конец вектора (в начало стека)
        MyStack<T> temp;

        while(!stack.any()) {
            temp.append(stack.get());
            stack.pop();
        }

        stack.append(element);

        while(!temp.any()) {
            stack.append(temp.get());
            temp.pop();
        }

        size++;
        if(size > max_size) max_size = size;
    }

    void delete_element(size_t index) {
        if(index >= size) return;

        MyStack<T> temp;
        size_t current = 0;

        while(!stack.any()) {
            T value = stack.get();
            stack.pop();

            if(current != size - index - 1) {
                temp.append(value);
            }
            current++;
        }

        size--;

        while(!temp.any()) {
            stack.append(temp.get());
            temp.pop();
        }

        if(size < max_size / 4 && max_size > 1) max_size /= 2;
    }

    int find(const T& element) const {
        for(size_t i = 0; i < size; ++i) {
            if(getAt(i) == element) {
                return i;
            }
        }

        return -1;
    }

    class ElementProxy {
    private:
        MyVector& vector;
        size_t index;

    public:
        ElementProxy(MyVector& vec, size_t idx) : vector(vec), index(idx) {}

        ElementProxy& operator=(const T& value) {
            // Создаем временный массив
            T* temp = new T[vector.size];

            // Копируем элементы в массив
            for(size_t i = 0; i < vector.size; ++i) {
                temp[i] = vector.getAt(i);
            }

            // Изменяем нужный элемент
            temp[index] = value;

            // Очищаем стек
            while(!vector.stack.any()) {
                vector.stack.pop();
            }

            // Восстанавливаем стек с измененным элементом
            for(int i = vector.size - 1; i >= 0; --i) {
                vector.stack.append(temp[i]);
            }

            delete[] temp;

            return *this;
        }

        operator T() const {
            return vector.getAt(index);
        }
    };

    ElementProxy operator[](size_t index) {
        if(index >= size) throw std::out_of_range("Index out of range");
        return ElementProxy(*this, index);
    }

    const T operator[](size_t index) const {
        return getAt(index);
    }

    void sort() {
        // Извлекаем элементы в массив
        T* temp = new T[size];

        for(size_t i = 0; i < size; ++i) {
            temp[i] = getAt(i);
        }

        // Сортируем
        std::sort(temp, temp + size);

        // Очищаем стек
        while(!stack.any()) {
            stack.pop();
        }

        // Возвращаем элементы в стек
        for(int i = size - 1; i >= 0; --i) {
            stack.append(temp[i]);
        }

        delete[] temp;
    }

    size_t get_size() const { return size; }
    size_t get_max_size() const { return max_size; }
};

// Специализация для int
template<>
void MyVector<int>::add_element(const int& element) {
    // Добавляем элемент в конец вектора (в начало стека)
    MyStack<int> temp;

    while(!stack.any()) {
        temp.append(stack.get());
        stack.pop();
    }

    stack.append(element);

    while(!temp.any()) {
        stack.append(temp.get());
        temp.pop();
    }

    size++;
    if(size > max_size) max_size = size;
}

// Специализация для char*
template<>
class MyVector<char*> {
protected:
    MyStack<char*> stack;  // Основной стек
    size_t size;           // Текущий размер
    size_t max_size;       // Максимальный размер

    char* getAt(size_t index) const {
        if(index >= size) throw std::out_of_range("Index out of range");

        MyStack<char*> tempStack = stack;

        for(size_t i = 0; i < size - index - 1; ++i) {
            tempStack.pop();
        }

        return tempStack.get();
    }

public:
    MyVector(size_t initial_size = 1) : size(0), max_size(initial_size) {}

    MyVector(const char* str) : size(1), max_size(1) {
        char* copy = new char[strlen(str) + 1];
        strcpy(copy, str);
        stack.append(copy);
    }

    MyVector(const MyVector& other) : size(other.size), max_size(other.max_size) {
        MyStack<char*> temp;
        MyStack<char*> otherCopy = other.stack;

        while(!otherCopy.any()) {
            char* str = otherCopy.get();
            char* copy = new char[strlen(str) + 1];
            strcpy(copy, str);
            temp.append(copy);
            otherCopy.pop();
        }

        while(!temp.any()) {
            stack.append(temp.get());
            temp.pop();
        }
    }

    ~MyVector() {
        while(!stack.any()) {
            char* str = stack.get();
            delete[] str;
            stack.pop();
        }
    }

    MyVector& operator=(const MyVector& other) {
        if(this == &other) return *this;

        while(!stack.any()) {
            char* str = stack.get();
            delete[] str;
            stack.pop();
        }

        size = other.size;
        max_size = other.max_size;

        MyStack<char*> temp;
        MyStack<char*> otherCopy = other.stack;

        while(!otherCopy.any()) {
            char* str = otherCopy.get();
            char* copy = new char[strlen(str) + 1];
            strcpy(copy, str);
            temp.append(copy);
            otherCopy.pop();
        }

        while(!temp.any()) {
            stack.append(temp.get());
            temp.pop();
        }

        return *this;
    }

    void add_element(const char* element) {
        char* copy = new char[strlen(element) + 1];
        strcpy(copy, element);

        MyStack<char*> temp;

        while(!stack.any()) {
            temp.append(stack.get());
            stack.pop();
        }

        stack.append(copy);

        while(!temp.any()) {
            stack.append(temp.get());
            temp.pop();
        }

        size++;
        if(size > max_size) max_size = size;
    }

    void delete_element(size_t index) {
        if(index >= size) return;

        MyStack<char*> temp;
        size_t current = 0;

        while(!stack.any()) {
            char* value = stack.get();
            stack.pop();

            if(current != size - index - 1) {
                temp.append(value);
            } else {
                delete[] value;
            }
            current++;
        }

        size--;

        while(!temp.any()) {
            stack.append(temp.get());
            temp.pop();
        }

        if(size < max_size / 4 && max_size > 1) max_size /= 2;
    }

    int find(const char* element) const {
        for(size_t i = 0; i < size; ++i) {
            char* current = getAt(i);
            if(strcmp(current, element) == 0) {
                return i;
            }
        }

        return -1;
    }

    class ElementProxy {
    private:
        MyVector& vector;
        size_t index;

    public:
        ElementProxy(MyVector& vec, size_t idx) : vector(vec), index(idx) {}

        ElementProxy& operator=(const char* value) {
            char** temp = new char*[vector.size];

            for(size_t i = 0; i < vector.size; ++i) {
                char* str = vector.getAt(i);
                if(i == index) {
                    temp[i] = new char[strlen(value) + 1];
                    strcpy(temp[i], value);
                } else {
                    temp[i] = new char[strlen(str) + 1];
                    strcpy(temp[i], str);
                }
            }

            while(!vector.stack.any()) {
                char* str = vector.stack.get();
                delete[] str;
                vector.stack.pop();
            }

            for(int i = vector.size - 1; i >= 0; --i) {
                vector.stack.append(temp[i]);
            }

            delete[] temp;

            return *this;
        }

        operator char*() const {
            return vector.getAt(index);
        }
    };

    ElementProxy operator[](size_t index) {
        if(index >= size) throw std::out_of_range("Index out of range");
        return ElementProxy(*this, index);
    }

    const char* operator[](size_t index) const {
        return getAt(index);
    }

    void sort() {
        char** temp = new char*[size];

        for(size_t i = 0; i < size; ++i) {
            char* str = getAt(i);
            temp[i] = new char[strlen(str) + 1];
            strcpy(temp[i], str);
        }

        std::sort(temp, temp + size, [](const char* a, const char* b) {
            return strcmp(a, b) < 0;
        });

        while(!stack.any()) {
            char* str = stack.get();
            delete[] str;
            stack.pop();
        }

        for(int i = size - 1; i >= 0; --i) {
            stack.append(temp[i]);
        }

        delete[] temp;
    }

    size_t get_size() const { return size; }
    size_t get_max_size() const { return max_size; }
};

// Сохраняем операторы вывода
std::ostream& operator<<(std::ostream& os, const MyVector<int>& vec) {
    os << "\n{";
    for(size_t i = 0; i < vec.get_size(); ++i) {
        if(i > 0) os << ", ";
        os << vec[i];
    }
    return os << "}\n";
}

std::ostream& operator<<(std::ostream& os, const MyVector<char*>& vec) {
    os << "\n{";
    for(size_t i = 0; i < vec.get_size(); ++i) {
        if(i > 0) os << ", ";
        os << vec[i];
    }
    return os << "}\n";
}

#endif // MYVECTOR_H
