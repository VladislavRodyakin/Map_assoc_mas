#pragma once
#include <iostream>
#include <vector>

const size_t max_key_length = 256;

struct Pair {
    Pair() = default;

    const char key[max_key_length]{};
    int value{};

    Pair& operator=(const Pair& from) {
        if (this == &from)
            return *this;
        memcpy((char*)key, from.key, max_key_length);
        return *this;
    }

    Pair(const Pair& from) : value{ from.value } {
        memcpy((char*)key, from.key, max_key_length);
    }
};

class Map {
public:
    Map();
    ~Map();
    Map(const Map& from);// скорее всего не может привоить пару напрямую
    //Map& operator=(const Map& from);

    size_t size() const;
    /*int& insert(const char* key);
    Pair* at(size_t index) const;
    Pair* find(const char* key) const;
    void erase(const char* key);
    const int& operator[](const char* key) const;
    int& operator[](const char* key);*/

protected:
    size_t _size = 0;
    std::vector <Pair> list;
};