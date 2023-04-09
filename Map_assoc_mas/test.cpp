#include "gtest/gtest.h"
//#include "F:\!!Универ\Прога\4 сем\Map_assoc_mas\Map.h"
//#include "F:\\!!Универ\\Прога\\4 сем\\Map_assoc_mas\\Map.h"
#include"../Map.h"

char keys[] = { '1','2','3','4','5','6', '7', '8','9' };

//Map();
TEST(MapStart, MapStartsEmpty) {
	Map MapExample{};
	EXPECT_EQ(0, MapExample.size());
}

//Map(const Map& first);
TEST(MapCopy, MapRightCopied) {
	Map MapExample1{};
	MapExample1.insert("ExampleKey") = 5;
	Map MapExample2(MapExample1);
	EXPECT_EQ(5, MapExample2.find("ExampleKey")->value);
}
TEST(MapCopy, MapRightCopiedManyElem) {
	Map MapExample1{};
	for (int i = 0; i < 9; i++) {
		MapExample1.insert(keys + i) = i;
	}
	Map MapExample2(MapExample1);
	for (int i = 0; i < 9; i++) {
		EXPECT_EQ(i, MapExample2.find(keys + i)->value);
	}
}

//Map& operator=(const Map&);
TEST(MapOperatorEq, MapEqEmpty) {
	Map MapExample1{};
	Map MapExample2{};
	MapExample1 = MapExample2;
	EXPECT_EQ(nullptr, MapExample1.at(0));
}
TEST(MapOperatorEq, NotEmptySizeTest) {
	Map MapExample1{};
	MapExample1.insert("ExampleKey");
	Map MapExample2{};
	MapExample2 = MapExample1;
	EXPECT_EQ(MapExample2.size(), MapExample1.size());
}
TEST(MapOperatorEq, NonEmptyCopyElemnt) {
	Map MapExample1{};
	MapExample1.insert("ExampleKey") = 5;
	Map MapExample2{};
	MapExample2 = MapExample1;
	EXPECT_EQ(5, MapExample2.find("ExampleKey")->value);
}
TEST(MapOperatorEq, NonEmptyCopyManyElemnts) {
	Map MapExample1{};
	for (int i = 0; i < 9; i++) {
		MapExample1.insert(keys + i) = i;
	}
	Map MapExample2{};
	MapExample2 = MapExample1;
	for (int i = 0; i < 9; i++) {
		EXPECT_EQ(MapExample1.find(keys + i)->value, MapExample2.find(keys + i)->value);
		EXPECT_EQ(MapExample1.find(keys + i)->key, MapExample1.find(keys + i)->key);
	}
}

//size_t size() const;
TEST(MapSize, SizeOfEmpty) {
	Map MapExample{};
	EXPECT_EQ(0, MapExample.size());
}
TEST(MapSize, SizeOfNotEmptyMap) {
	Map MapExample{};
	for (int i = 0; i < 9; i++) {
		MapExample.insert(keys + i);
	}
	EXPECT_EQ(9, MapExample.size());
}
TEST(MapSize, SizeAfterErase) {
	Map MapExample{};
	for (int i = 0; i < 9; i++) {
		MapExample.insert(keys + i);
	}
	MapExample.erase(keys);
	EXPECT_EQ(8, MapExample.size());
}

//int& insert(const char* key);
TEST(MapInsert, InsertOneElementWithoutVal) {
	Map MapExample{};
	int& example1Value = MapExample.insert("ExampleKey");
	EXPECT_EQ(1, MapExample.size());
}
TEST(MapInsert, InsertManyElementsWithoutVal) {
	Map MapExample{};
	for (int i = 0; i < 9; i++) {
		MapExample.insert(keys + i);
	}
	EXPECT_EQ(9, MapExample.size());

}
TEST(MapInsert, InsertOneElementWithVal) {
	Map MapExample{};
	int& example1Value = MapExample.insert("ExampleKey") = 5;
	EXPECT_EQ(5, MapExample.find("ExampleKey")->value);
}
TEST(MapInsert, InsertManyElementWithVal) {
	Map MapExample{};
	for (int i = 0; i < 9; i++) {
		MapExample.insert(keys + i) = i;
	}
	for (int i = 0; i < 9; i++) {
		EXPECT_EQ(i, MapExample.find(keys + i)->value);
	}
}

//Pair* at(size_t index);
TEST(IndexTest, EmptyMap) {
	Map MapExample{};
	EXPECT_EQ(nullptr, MapExample.at(0));
	EXPECT_EQ(nullptr, MapExample.at(1));
	EXPECT_EQ(nullptr, MapExample.at(10));
}
TEST(IndexTest, EmptyMapAndNegativeIndex) {
	Map MapExample{};
	EXPECT_EQ(nullptr, MapExample.at(-100));
}
TEST(IndexTest, NotEmptyMapKeyControl) {
	Map MapExample{};
	for (int i = 0; i < 9; i++) {
		MapExample.insert(keys + i);
	}
	for (int i = 0; i < 9; i++) {
		EXPECT_EQ(*(keys + i), *(MapExample.at(i))->key);
	}
}
TEST(IndexTest, NotEmptyMapValControl) {
	Map MapExample{};
	for (int i = 0; i < 9; i++) {
		MapExample.insert(keys + i) = i;
	}
	for (int i = 0; i < 9; i++) {
		EXPECT_EQ(i, MapExample.at(i)->value);
	}
}

//Pair* find(const char* key);
TEST(MapFind, FindNotExisting) {
	Map MapExample{};
	EXPECT_EQ(nullptr, MapExample.find("Examplekey"));
}
TEST(MapFind, InsertOneElementAndFindKey) {
	Map MapExample{};
	MapExample.insert(keys);
	EXPECT_EQ(*keys, *(MapExample.find(keys)->key));
}
TEST(MapFind, InsertManyElementsAndFind) {
	Map MapExample{};
	for (int i = 0; i < 9; i++) {
		MapExample.insert(keys + i);
	}
	for (int i = 0; i < 9; i++) {
		EXPECT_EQ(*(keys + i), *(MapExample.find(keys + i)->key));
	}

}

//void erase(const char* key);
TEST(MapErase, EraseOneElementWithoutVal) {
	Map MapExample{};
	MapExample.insert("ExampleKey");
	MapExample.erase("ExampleKey");
	EXPECT_EQ(0, MapExample.size());
}
TEST(MapErase, EraseOneElementWithVal) {
	Map MapExample{};
	MapExample.insert("ExampleKey") = 5;
	MapExample.erase("ExampleKey");
	EXPECT_EQ(0, MapExample.size());
}
TEST(MapErase, EraseManyElements) {
	Map MapExample{};
	for (int i = 0; i < 9; i++) {
		MapExample.insert(keys + i) = i;
	}
	for (int k = 0; k < 9; k++) {
		MapExample.erase(keys + k);
	}
	EXPECT_EQ(0, MapExample.size());
}

//int& operator[](const char* key) ;
TEST(MapIndexOperator, TakeRandElem) {
	Map MapExample{};
	MapExample["ExmapleKey"] = 5;
	EXPECT_EQ(5, MapExample.find("ExmapleKey")->value);
}
TEST(MapIndexOperator, TakeOneElem) {
	Map MapExample{};
	MapExample.insert("ExmapleKey") = 5;
	EXPECT_EQ(5, MapExample["ExmapleKey"]);
}
TEST(MapIndexOperator, TakeManyElem) {
	Map MapExample{};
	for (int i = 0; i < 9; i++) {
		MapExample.insert(keys + i) = i;
	}
	for (int i = 0; i < 9; i++) {
		EXPECT_EQ(i, MapExample[keys + i]);
	}
}

//const int& operator[](const char* key) const;
TEST(MapIndexOperatorConst, TakeOneElem) {
	Map MapExample{};
	MapExample.insert("ExmapleKey") = 5;
	EXPECT_EQ(5, MapExample["ExmapleKey"]);
}
TEST(MapIndexOperatorConst, TakeNotExistingElem) {
	const Map MapExample{};
	EXPECT_ANY_THROW(MapExample["RandomKey"]);
}