#include "Map.h"

Map::Map(){
}

Map::~Map(){}

Map::Map(const Map& from) {
	_size = from._size;
	list.insert(list.begin(), from.list.begin(), from.list.end());
}

size_t Map::size() const {
	return _size;
}

