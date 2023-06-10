#pragma once

#include <algorithm>
#include <string>

#include "../DataStructures/include/FList.hpp"

#pragma region FListTests
// ================================================
// ==============   FLIST TESTS   =================
// ================================================

TEST(FListTest, Constructor)
{
	FList<int> emptyList;
	EXPECT_EQ(emptyList.size(), 0);
	EXPECT_EQ(emptyList.empty(), true);

	FList<int> initList = { 1, 2, 3 };
	EXPECT_EQ(initList.size(), 3);
	EXPECT_EQ(initList.empty(), false);

	FList<int> copyConstruct = initList;
	EXPECT_EQ(copyConstruct.size(), 3);
	EXPECT_EQ(copyConstruct.empty(), false);
}

TEST(FListTest, Front)
{
	FList<int> testFrontList = { 1, 2, 3 };

	// Data is filled from the front and thus "inverted"
	EXPECT_EQ(testFrontList.front(), 3);
}

// Here we test Empty, push_back, push_front and size
TEST(FListTest, PushAndSize)
{
	FList<int> testList;
	EXPECT_EQ(testList.size(), 0);
	EXPECT_EQ(testList.empty(), true);

	testList = { 1, 2, 3 };
	EXPECT_EQ(testList.size(), 3);
	EXPECT_EQ(testList.empty(), false);

	testList.push_front(0);

	EXPECT_EQ(testList.front(), 0);
	EXPECT_EQ(testList.size(), 4);
}

// Here we test insert and remove methods
TEST(FListTest, InsertAndremove)
{
	// insert block
	FList<int> testList = { 1, 2, 3 };

	testList.insert(0, 0);
	EXPECT_EQ(testList.front(), 0);

	// We still need to implement the find algorithm for this case
	testList.insert(4, testList.size());
	//EXPECT_EQ(testList.back(), 4);

	// We still need to implement the find algorithm for this case
	//testList.insert(-5, 2);

	// We test error handling
	EXPECT_THROW(testList.insert(-1, -1), std::exception);
	EXPECT_THROW(testList.insert(12, 12), std::exception);

	// remove block
	testList.remove(0);
	EXPECT_EQ(testList.front(), 3);

	// We still need to implement the find algorithm for this case
	testList.remove(testList.size() - 1);
	//EXPECT_EQ(testList.back(), 3);

	// We still need to implement the find algorithm for this case
	//testList.remove(2);

	// We test error handling
	EXPECT_THROW(testList.remove(-1), std::exception);
	EXPECT_THROW(testList.remove(12), std::exception);
}

TEST(FListTest, PopAndClear)
{
	FList<int> testList = { 1, 2, 3, 4, 5 };

	testList.pop_front();
	EXPECT_EQ(testList.front(), 4);

	testList.clear();
	EXPECT_EQ(testList.size(), 0);
	EXPECT_EQ(testList.empty(), true);
}

#pragma endregion FListTests