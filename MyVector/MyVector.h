#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <stdexcept>

namespace char_utils {
    inline size_t strlen(const char* str) {
        if (!str) return 0;
        size_t len = 0;
        while (str[len]) len++;
        return len;
    }

    inline char* copy_cstr(const char* src) {
        if (!src) return nullptr;
        char* dst = new char[strlen(src) + 1];
        size_t i = 0;
        while (src[i]) {
            dst[i] = src[i];
            i++;
        }
        dst[i] = '\0';
        return dst;
    }

    inline void delete_cstr(char* str) {
        delete[] str;
    }

    inline bool equal_cstr(const char* a, const char* b) {
        if (!a && !b) return true;
        if (!a || !b) return false;
        size_t i = 0;
        while (a[i] && b[i] && a[i] == b[i]) i++;
        return a[i] == b[i];
    }

    inline int strcmp(const char* a, const char* b) {
        if (!a && !b) return 0;
        if (!a) return -1;
        if (!b) return 1;

        size_t i = 0;
        while (a[i] && b[i]) {
            if (a[i] < b[i]) return -1;
            if (a[i] > b[i]) return 1;
            i++;
        }

        if (!a[i] && !b[i]) return 0;
        if (!a[i]) return -1; // a короче
        return 1; // b короче
    }

    // Сравнение "меньше"
    inline bool less_cstr(const char* a, const char* b) {
        return strcmp(a, b) < 0;
    }
}

template <typename T = int>
class MyVector {
protected:
    T* pdata;
    size_t size;
    size_t max_size;

    void resize(size_t new_size) {
        if (new_size < 1) new_size = 1;
        T* new_data = new T[new_size];
        for (size_t i = 0; i < size; i++) {
            new_data[i] = pdata[i];
        }
        delete[] pdata;
        pdata = new_data;
        max_size = new_size;
    }

public:
    MyVector(size_t initial_size = 1) : size(0), max_size(initial_size) {
        pdata = new T[max_size];
    }

    MyVector(const T& first_element) : size(1), max_size(1) {
        pdata = new T[1];
        pdata[0] = first_element;
    }

    MyVector(const MyVector& other) : size(other.size), max_size(other.max_size) {
        pdata = new T[max_size];
        for (size_t i = 0; i < size; i++) {
            pdata[i] = other.pdata[i];
        }
    }

    virtual ~MyVector() {
        delete[] pdata;
    }

    MyVector& operator=(const MyVector& other) {
        if (this == &other) return *this;
        delete[] pdata;
        size = other.size;
        max_size = other.max_size;
        pdata = new T[max_size];
        for (size_t i = 0; i < size; i++) {
            pdata[i] = other.pdata[i];
        }
        return *this;
    }

    virtual void add_element(const T& element) {
        if (size >= max_size) resize(max_size * 2);
        pdata[size++] = element;
    }

    void delete_element(size_t index) {
        if (index >= size) return;
        for (size_t i = index; i < size - 1; ++i) {
            pdata[i] = pdata[i + 1];
        }
        size--;
        if (size < max_size / 4 && max_size > 1) resize(max_size / 2);
    }

    int find(const T& element) const {
        for (size_t i = 0; i < size; ++i) {
            if (pdata[i] == element) return i;
        }
        return -1;
    }

    T& operator[](size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        return pdata[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) throw std::out_of_range("Index out of range");
        return pdata[index];
    }

    template <int>
    void sort() {
        for (size_t i = 0; i < size; i++) {
            int maxx = i;
            for (size_t ii = i; ii < size; ii++){
                if (pdata[maxx] < pdata[ii]) {
                    maxx = ii;
                }
            }
            T c = pdata[i];
            pdata[i] = pdata[maxx];
            pdata[maxx] = c;
        }
    }

    template <const char*>
    void sort() {
        for (size_t i = 0; i < size - 1; i++) {
            for (size_t ii = 0; ii < size - i - 1; ii++) {
                if (char_utils::strcmp(pdata[ii], pdata[ii + 1]) > 0) {
                    T temp = pdata[ii];
                    pdata[ii] = pdata[ii + 1];
                    pdata[ii + 1] = temp;
                }
            }
        }
    }

    size_t get_size() const { return size; }
    size_t get_max_size() const { return max_size; }
};

template <>
class MyVector<char*> {
protected:
    char** pdata;
    size_t size;
    size_t max_size;

    void resize(size_t new_size) {
        if (new_size < 1) new_size = 1;
        char** new_data = new char*[new_size];
        for (size_t i = 0; i < size; i++) {
            new_data[i] = pdata[i];
        }
        delete[] pdata;
        pdata = new_data;
        max_size = new_size;
    }

    void clear() {
        for (size_t i = 0; i < size; ++i) {
            char_utils::delete_cstr(pdata[i]);
        }
        delete[] pdata;
    }

    void copy_from(const MyVector& other) {
        size = other.size;
        max_size = other.max_size;
        pdata = new char*[max_size];
        for (size_t i = 0; i < size; ++i) {
            pdata[i] = char_utils::copy_cstr(other.pdata[i]);
        }
    }

public:
    MyVector(size_t initial_size = 1) : size(0), max_size(initial_size) {
        pdata = new char*[max_size];
    }

    MyVector(const char* str) : size(1), max_size(1) {
        pdata = new char*[1];
        pdata[0] = char_utils::copy_cstr(str);
    }

    MyVector(const MyVector& other) {
        copy_from(other);
    }

    ~MyVector() {
        clear();
    }

    MyVector& operator=(const MyVector& other) {
        if (this == &other) return *this;
        clear();
        copy_from(other);
        return *this;
    }

    void add_element(const char* element) {
        if (size >= max_size) resize(max_size * 2);
        pdata[size++] = char_utils::copy_cstr(element);
    }

    void delete_element(size_t index) {
        if (index >= size) return;
        char_utils::delete_cstr(pdata[index]);
        for (size_t i = index; i < size - 1; ++i) {
            pdata[i] = pdata[i + 1];
        }
        size--;
        if (size < max_size / 4 && max_size > 1) resize(max_size / 2);
    }

    int find(const char* element) const {
        for (size_t i = 0; i < size; ++i) {
            if (char_utils::equal_cstr(pdata[i], element)) return i;
        }
        return -1;
    }

    char* operator[](size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        return pdata[index];
    }

    const char* operator[](size_t index) const {
        if (index >= size) throw std::out_of_range("Index out of range");
        return pdata[index];
    }

    template <int>
    void sort() {
        for (size_t i = 0; i < size; i++) {
            int maxx = i;
            for (size_t ii = i; ii < size; ii++){
                if (char_utils::strcmp(pdata[maxx], pdata[ii]) < 0) {
                    maxx = ii;
                }
            }
            char* c = pdata[i];
            pdata[i] = pdata[maxx];
            pdata[maxx] = c;
        }
    }

    template <const char*>
    void sort() {
        for (size_t i = 0; i < size - 1; i++) {
            for (size_t ii = 0; ii < size - i - 1; ii++) {
                if (char_utils::strcmp(pdata[ii], pdata[ii + 1]) > 0) {
                    char* temp = pdata[ii];
                    pdata[ii] = pdata[ii + 1];
                    pdata[ii + 1] = temp;
                }
            }
        }
    }

    size_t get_size() const { return size; }
    size_t get_max_size() const { return max_size; }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const MyVector<T>& vec) {
    os << "\n{";
    for (size_t i = 0; i < vec.get_size(); ++i) {
        if (i > 0) os << ", ";
        os << vec[i];
    }
    return os << "}\n";
}

#endif // MYVECTOR_H
