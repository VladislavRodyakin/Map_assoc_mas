#include "Map.h"

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
	Pair* tmp = this->find(key);
	if (tmp != nullptr)
		return (int&)tmp->value;
	list.push_back(Pair(key));
	return (int&)list.back().value;
}

Pair* Map::find(const char* key){
	for (auto i = list.begin(); i != list.end(); i++) {
		if (strcmp((*i).key, key)==0)
			return &(*i);
	}
	return nullptr;
}
