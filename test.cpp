#include "gtest/gtest.h"
#include "../Map_assoc_mas/Map.hpp"

const char* keys[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

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
	for (int i = 0; i < 9; i++)
		MapExample1.insert(keys[i]) = i;
	Map MapExample2(MapExample1);
	for (int i = 0; i < 9; i++)
		EXPECT_EQ(i, MapExample2.find(keys[i])->value);
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
	for (int i = 0; i < 9; i++)
		MapExample1.insert(keys[i]) = i;
	Map MapExample2{};
	MapExample2 = MapExample1;
	for (int i = 0; i < 9; i++) {
		EXPECT_EQ(MapExample1.find(keys[i])->value, MapExample2.find(keys[i])->value);
		EXPECT_STREQ(MapExample1.find(keys[i])->key, MapExample1.find(keys[i])->key);
	}
}

//size_t size() const;
TEST(MapSize, SizeOfEmpty) {
	Map MapExample{};
	EXPECT_EQ(0, MapExample.size());
}
TEST(MapSize, SizeOfNotEmptyMap) {
	Map MapExample{};
	for (int i = 0; i < 9; i++)
		MapExample.insert(keys[i]);
	EXPECT_EQ(9, MapExample.size());
}
TEST(MapSize, SizeAfterErase) {
	Map MapExample{};
	for (int i = 0; i < 9; i++)
		MapExample.insert(keys[i]);
	MapExample.erase(keys[0]);
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
	for (int i = 0; i < 9; i++)
		MapExample.insert(keys[i]);
	EXPECT_EQ(9, MapExample.size());

}
TEST(MapInsert, InsertOneElementWithVal) {
	Map MapExample{};
	int& example1Value = MapExample.insert("ExampleKey") = 5;
	EXPECT_EQ(5, MapExample.find("ExampleKey")->value);
}
TEST(MapInsert, InsertManyElementWithVal) {
	Map MapExample{};
	for (int i = 0; i < 9; i++)
		MapExample.insert(keys[i]) = i;
	for (int i = 0; i < 9; i++)
		EXPECT_EQ(i, MapExample.find(keys[i])->value);
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
	for (int i = 0; i < 9; i++)
		MapExample.insert(keys[i]);
	for (int i = 0; i < 9; i++)
		EXPECT_EQ(*(keys[i]), *(MapExample.at(i))->key);
}
TEST(IndexTest, NotEmptyMapValControl) {
	Map MapExample{};
	for (int i = 0; i < 9; i++)
		MapExample.insert(keys[i]) = i;
	for (int i = 0; i < 9; i++)
		EXPECT_EQ(i, MapExample.at(i)->value);
}

//Pair* find(const char* key);
TEST(MapFind, FindInEmpty) {
	Map MapExample{};
	EXPECT_EQ(nullptr, MapExample.find("Examplekey"));
	EXPECT_EQ(MapExample.find(nullptr), nullptr);
	EXPECT_EQ(MapExample.find(""), nullptr);
}
TEST(MapFind, InsertOneElementAndFindKey) {
	Map MapExample{};
	MapExample.insert(keys[0]);
	EXPECT_EQ(*(keys[0]), *(MapExample.find(keys[0])->key));
}
TEST(MapFind, InsertManyElementsAndFind) {
	Map MapExample{};
	for (int i = 0; i < 9; i++)
		MapExample.insert(keys[i]);
	for (int i = 0; i < 9; i++)
		EXPECT_EQ(*(keys[i]), *(MapExample.find(keys[i])->key));
	EXPECT_EQ(MapExample.find(nullptr), nullptr);
	EXPECT_EQ(MapExample.find("key"), nullptr);
	EXPECT_EQ(MapExample.find(""), nullptr);
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
	for (int i = 0; i < 9; i++)
		MapExample.insert(keys[i]) = i;
	for (int j = 0; j < 9; j++)
		MapExample.erase(keys[j]);
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
	for (int i = 0; i < 9; i++)
		MapExample.insert(keys[i]) = i;
	for (int i = 0; i < 9; i++)
		EXPECT_EQ(i, MapExample[keys[i]]);
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

TEST(MapKeyFailedSituations, NullPtr) {
	Map map{};
	EXPECT_THROW(map.insert(nullptr), std::out_of_range);//проходит
	EXPECT_THROW(map.erase(nullptr), std::out_of_range);
}

TEST(MapKeyFailedSituations, EmptyPtr) {
	Map map{};
	EXPECT_THROW(map.erase(""), std::out_of_range);
	EXPECT_THROW(map.insert(""), std::out_of_range);
}

TEST(MapKeyFailedSituations, LongKey) {
	Map map{};
	const char key255[] =
		"12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345"
		"12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345"
		"12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345"
		"12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345"
		"12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345"
		"12345";
	const char key256[] =
		"12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345"
		"12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345"
		"12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345"
		"12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345"
		"12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345"
		"12345" "1";
	const char key257[] =
		"12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345"
		"12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345"
		"12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345"
		"12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345"
		"12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345"
		"12345" "12";
	const char key258[] =
		"12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345"
		"12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345"
		"12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345"
		"12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345"
		"12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345"
		"12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345" "12345"
		"12345" "123";
	EXPECT_NO_THROW(map.insert(key257)); // проходит
	ASSERT_EQ(map.size(), 1);
	EXPECT_TRUE(map.find(key255));
	EXPECT_STREQ(key255, map.find(key256)->key);
	EXPECT_STREQ(key255, map.find(key257)->key);
	EXPECT_STREQ(key255, map.find(key258)->key);
}
