#include "Map.hpp"

Map::Map(){
}

Map::~Map(){
}

Map::Map(const Map& from) {
	_size = from._size;
	list.insert(list.begin(), from.list.begin(), from.list.end());
}

Map& Map::operator=(const Map& from) {
	if (this == &from)
		return *this;
	_size = from._size;
	list.insert(list.begin(), from.list.begin(), from.list.end());
	return *this;
}

size_t Map::size() const {
	return _size;
}

int& Map::insert(const char* key) {
	if (strlen(key) > max_key_length)
		return (int&)max_key_length;
	if (key == nullptr || strcmp(key, "") == 0)
		throw std::out_of_range("Key not found");
	Pair* tmp = this->find(key);
	if (tmp != nullptr)
		return (int&)tmp->value;
	list.push_back(Pair(key));
	_size++;
	return (int&)list.back().value;
}

Pair* Map::find(const char* key) {
	if (strlen(key) > max_key_length)
		return nullptr;
	for (auto i = list.begin(); i != list.end(); i++) {
		if (strcmp((*i).key, key) == 0)
			return &(*i);
	}
	return nullptr;
}

Pair* Map::at(size_t index) {
	if (index >= _size)
		return nullptr;
	return &(list[index]);
}

void Map::erase(const char* key) {
	for (auto i = list.begin(); i != list.end(); i++) {
		if (strcmp((*i).key, key) == 0) {
			list.erase(i);
			_size--;
		}
	}
	throw std::out_of_range("Key not found");
}

int& Map::operator[](const char* key) {
	return this->insert(key);
}

const int& Map::operator[](const char* key) const {
	for (auto i = list.begin(); i != list.end(); i++) {
		if (strcmp((*i).key, key)==0)
			return (const int&)i->value;
	}
	throw std::out_of_range("Key not found");
}
