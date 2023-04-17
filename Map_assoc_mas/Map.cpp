#include "Map.hpp"
#include <string>

class Predicate {
private:
	/*const */std::string key;
public:
	Predicate(const /*std::string&*/ char* _key) /*:key(_key)*/{
		//(std::string)key=_key;

		key = (std::string)_key;
		/*if (strlen(_key) > 255) {
			key.resize(255);
		}*/
		//if (key.size() > max_key_length) {
		//	key.resize(max_key_length);
		//}
	}
	
	bool operator() (const Pair& p) {
		return key.compare(0, max_key_length, p.key);// можно сравнивать с ограничениями
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
	if (key == nullptr || *key == 0)
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
	/*if (strlen(key) > max_key_length)
		return nullptr;*/
	if (key == nullptr)
		throw std::out_of_range("Key is null");
	if (key == std::string())
		throw std::out_of_range("Key is empty");
	if (strlen(key) >= max_key_length)
		throw std::out_of_range("Key too long");
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
	if (key == nullptr)
		throw std::out_of_range("Key is null");
	if (key == std::string())
		throw std::out_of_range("Key is empty");
	if (strlen(key) >= max_key_length)
		throw std::out_of_range("Key too long");
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
