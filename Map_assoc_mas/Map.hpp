#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

const size_t max_key_length = 256;

struct Pair {
    const char key[max_key_length]{};
    int value{};
};

struct PairEq : Pair {
    PairEq() = default;
    PairEq& operator=(const PairEq& from) {
        if (this == &from)
            return *this;
        memcpy((char*)key, from.key, max_key_length);
        value = from.value;
        return *this;
    }

    PairEq(const PairEq& from) /*: value{ from.value } */{
        value = from.value;
        std::strncpy((char*)key, from.key, strlen(from.key));
    }
    PairEq(const char* _key) {
        std::strncpy((char*)key, _key, strlen(_key));//strcpy с ограничением
    }
};

class Map {
public:
    Map();
    ~Map();
    Map(const Map& from);
    Map& operator=(const Map& from);

    size_t size() const;
    int& insert(const char* key);
    Pair* at(size_t index);
    Pair* find(const char* key);
    void erase(const char* key);
    const int& operator[](const char* key) const;
    int& operator[](const char* key);

protected:
    std::vector <PairEq> list;
};