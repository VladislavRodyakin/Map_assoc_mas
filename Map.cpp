#include "Map.hpp"
#include <string>

class Predicate {
private:
	std::string key;
public:
	Predicate(const char* _key) :key{ _key } {
	}
	
	bool operator() (const Pair& p) {
		return strncmp(key.c_str(), p.key, _countof(p.key) - 1) == 0;// можно сравнивать с ограничениями
	}
};

Map::Map(){
}

Map::~Map(){
}

Map::Map(const Map& from) {
	list.insert(list.begin(), from.list.begin(), from.list.end());
}

Map& Map::operator=(const Map& from) {
	if (this == &from)
		return *this;
	list.insert(list.begin(), from.list.begin(), from.list.end());
	return *this;
}

size_t Map::size() const {
	return list.size();
}

int& Map::insert(const char* key) {
	if (key == nullptr)
		throw std::out_of_range("Key is null");
	if (*key == 0)
		throw std::out_of_range("Key is empty");
	Pair* tmp = find(key);
	if (tmp != nullptr)
		return tmp->value;
	list.push_back(PairEq(key));
	//list.emplace_back(key);
	return list.back().value;
}

Pair* Map::find(const char* key) {
	if (key == nullptr)
		return nullptr;
	if (*key == 0)
		return nullptr;
	
	auto it = std::find_if(list.begin(), list.end(), Predicate(key));
	if (it != list.end())
		return &(*it);
	return nullptr;
}

Pair* Map::at(size_t index) {
	if (index >= size())
		return nullptr;
	return &(list[index]);
}

void Map::erase(const char* key) {
	if (key == nullptr)
		throw std::out_of_range("Key is null");
	if (*key == 0)
		throw std::out_of_range("Key is empty");
	auto it = std::find_if(list.begin(), list.end(), Predicate(key));
	if (it != list.end())
		list.erase(it);
}

int& Map::operator[](const char* key) {
	return insert(key);
}

const int& Map::operator[](const char* key) const {
	if (key == nullptr)
		throw std::out_of_range("Key is null");
	if (*key == 0)
		throw std::out_of_range("Key is empty");

	auto it = std::find_if(list.begin(), list.end(), Predicate(key));
	if (it != list.end())
		return (const int&)it->value;

	throw std::out_of_range("Key not found");
}
