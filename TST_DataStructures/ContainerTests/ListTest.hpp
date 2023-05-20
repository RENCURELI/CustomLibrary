#pragma once

#include <algorithm>
#include <string>

#include "../DataStructures/include/List.hpp"

#pragma region ListTests
// ================================================
// ==============   LIST TESTS   =================
// ================================================

TEST(ListTest, Constructor)
{
	List<int> emptyList;
	EXPECT_EQ(emptyList.size(), 0);
	EXPECT_EQ(emptyList.empty(), true);

	List<int> initList = { 1, 2, 3 };
	EXPECT_EQ(initList.size(), 3);
	EXPECT_EQ(initList.empty(), false);

	List<int> copyConstruct = initList;
	EXPECT_EQ(copyConstruct.size(), 3);
	EXPECT_EQ(copyConstruct.empty(), false);
}

TEST(ListTest, FrontBack)
{
	List<int> testList = { 1, 10, 5, -5 };

	EXPECT_EQ(testList.front(), 1);
	EXPECT_EQ(testList.back(), -5);
}

// Here we test Empty, push_back, push_front and size
TEST(ListTest, PushAndSize)
{
	List<int> testList;
	EXPECT_EQ(testList.size(), 0);
	EXPECT_EQ(testList.empty(), true);

	testList = { 1, 2, 3 };
	EXPECT_EQ(testList.size(), 3);
	EXPECT_EQ(testList.empty(), false);

	testList.push_front(0);

	EXPECT_EQ(testList.front(), 0);
	EXPECT_EQ(testList.size(), 4);

	testList.push_back(4);

	EXPECT_EQ(testList.back(), 4);
	EXPECT_EQ(testList.size(), 5);
}

// Here we test insert and remove methods
TEST(ListTest, InsertAndremove)
{
	// insert block
	List<int> testList = { 1, 2, 3 };

	testList.insert(testList.begin(), 0);
	EXPECT_EQ(testList.front(), 0);

	testList.insert(testList.end(), 4);
	EXPECT_EQ(testList.back(), 4);

	// We still need to implement the find algorithm for this case
	auto it = testList.begin();
	std::advance(it, 3);
	testList.insert(it, -5);

	// remove block
	testList.erase(testList.begin());
	EXPECT_EQ(testList.front(), 1);

	testList.erase(--testList.end());
	EXPECT_EQ(testList.back(), 3);

	// We still need to implement the find algorithm for this case
	it = testList.begin();
	std::advance(it, 2);
	testList.erase(it);
}

TEST(ListTest, PopAndClear)
{
	List<int> testList = { 1, 2, 3, 4, 5 };

	testList.pop_back();
	EXPECT_EQ(testList.back(), 4);

	testList.pop_front();
	EXPECT_EQ(testList.front(), 2);

	testList.clear();
	EXPECT_EQ(testList.size(), 0);
	EXPECT_EQ(testList.empty(), true);
}

#pragma endregion ListTests
