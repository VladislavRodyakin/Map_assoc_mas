#include "Map.hpp"

class Predicate {
public:
	Predicate(const std::string&_key): key(_key){}
	bool operator() (const Pair& p) {
		return key == p.key;
	}
private:
	const std::string key;
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
	if (key == nullptr || strcmp(key, "") == 0)
		throw std::out_of_range("Key not found");
	if (strlen(key) > max_key_length)
		return (int&)max_key_length;
	Pair* tmp = this->find(key);
	if (tmp != nullptr)
		return tmp->value;
	list.push_back(PairEq(key));
	return list.back().value;
}

Pair* Map::find(const char* key) {
	if (strlen(key) > max_key_length)
		return nullptr;
	for (auto i = list.begin(); i != list.end(); i++)
		if (strcmp((*i).key, key) == 0)
			return &(*i);
	return nullptr;
}

Pair* Map::at(size_t index) {
	if (index >= size())
		return nullptr;
	return &(list[index]);
}

void Map::erase(const char* key) {
	//for (auto i = list.begin(); i != list.end(); i++) {
	//	if (strcmp((*i).key, key) == 0) {
	//		list.erase(i);
	//		return;
	//	}
	//}
	auto it = std::find_if(list.begin(), list.end(), Predicate(key));
	if (it != list.end())
		list.erase(it);
}

int& Map::operator[](const char* key) {
	return insert(key);
}

const int& Map::operator[](const char* key) const {
	for (auto i = list.begin(); i != list.end(); i++)
		if (strcmp((*i).key, key)==0)
			return (const int&)i->value;
	//auto i = std::find_if(list.begin(), list.end(), Predicate(key));
	//return (const int&)i->value;
	throw std::out_of_range("Key not found");
}
