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
TEST(FListTest, InsertAndRemove)
{
	// insert block
	FList<int> testList = { 1, 2, 3 };

	testList.push_front(0);
	EXPECT_EQ(testList.front(), 0);

	testList.insert_after(testList.cend(), 4);
	EXPECT_TRUE(std::find(testList.begin(), testList.end(), 4) != testList.end());

	// remove block
	testList.pop_front();
	EXPECT_EQ(testList.front(), 3);

	auto testIt = testList.begin();
	std::advance(testIt, testList.size() - 2); // - 2 to erase the last element of the list as we erase the element AFTER the iterator
	testList.erase_after(testIt);
	EXPECT_TRUE(std::find(testList.begin(), testList.end(), 4) == testList.end());
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