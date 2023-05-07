#pragma once
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
        memcpy_s((char*)key, sizeof(key), from.key, sizeof(from.key));
        value = from.value;
        return *this;
    }

    PairEq(const PairEq& from) {
        value = from.value;
        memcpy_s((char*)key, sizeof(key), from.key, sizeof(from.key));
    }

    PairEq(const char* _key) {
        strncpy_s((char*)key, _countof(key), _key, _TRUNCATE);
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