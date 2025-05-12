#ifndef MYSET_H
#define MYSET_H

#include "../MyVector/MyVector.h"


class MySet : public MyVector<char*> {
public:
    MySet(size_t initial_size = 1) : MyVector<char*>(initial_size) {}
    MySet(const char* str) : MyVector<char*>(str) {}
    MySet(const MySet& other) : MyVector<char*>(other) {}

    bool is_element(const char* element) const {
        return find(element) != -1;
    }

    void add_element(const char* element) {
        if (!is_element(element)) {
            MyVector<char*>::add_element(element);
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
    }

    void delete_element(const char* element) {
        int index = find(element);
        if (index != -1) {
            MyVector<char*>::delete_element(index);
        }
    }

    MySet& operator+=(const MySet& other) {
        apply_from(other, [this](const char* el) { add_element(el); });
        return *this;
    }

    MySet& operator-=(const MySet& other) {
        apply_from(other, [this](const char* el) { delete_element(el); });
        return *this;
    }

    MySet& operator*=(const MySet& other) {
        for (size_t i = 0; i < get_size(); ) {
            if (!other.is_element((*this)[i])) {
                delete_element((*this)[i]);
            } else {
                ++i;
            }
        }
        return *this;
    }

private:
    template <typename Func>
    void apply_from(const MySet& other, Func func) {
        for (size_t i = 0; i < other.get_size(); ++i) {
            func(other[i]);
        }
    }
};

inline MySet operator+(const MySet& a, const MySet& b) {
    MySet result = a;
    result += b;
    return result;
}

inline MySet operator-(const MySet& a, const MySet& b) {
    MySet result = a;
    result -= b;
    return result;
}

inline MySet operator*(const MySet& a, const MySet& b) {
    MySet result;
    for (size_t i = 0; i < a.get_size(); ++i) {
        if (b.is_element(a[i])) {
            result.add_element(a[i]);
        }
    }
    return result;
}

inline bool operator==(const MySet& a, const MySet& b) {
    if (a.get_size() != b.get_size()) return false;
    for (size_t i = 0; i < a.get_size(); ++i) {
        if (!b.is_element(a[i])) return false;
    }
    return true;
}

inline std::ostream& operator<<(std::ostream& os, const MySet& set) {
    return os << static_cast<const MyVector<char*>&>(set);
}

#define MAX_SIZE 100

#endif // MYSET_H
