#pragma once

#include <algorithm>
#include <initializer_list>
#include <string>

#include "FList.hpp"

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

	FList<int> moveConstruct = std::move(copyConstruct);
	EXPECT_EQ(copyConstruct.size(), 0);
	EXPECT_EQ(moveConstruct.size(), 3);
	EXPECT_EQ(copyConstruct.empty(), true);
	EXPECT_EQ(moveConstruct.empty(), false);

	// Iterator Constructor
	FList<int> itConstruct = FList<int>(moveConstruct.begin(), moveConstruct.end());
	EXPECT_EQ(itConstruct.size(), 3);
	EXPECT_EQ(itConstruct.empty(), false);
	EXPECT_EQ(itConstruct.front(), 3);

	// Count default Constructor
	FList<int> countDefConstruct = FList<int>(5);
	EXPECT_EQ(countDefConstruct.size(), 5);
	EXPECT_EQ(countDefConstruct.empty(), false);
	EXPECT_EQ(countDefConstruct.front(), 0);

	// Count Val Constructor
	FList<int> countValConstruct = FList<int>(5, -14);
	EXPECT_EQ(countValConstruct.size(), 5);
	EXPECT_EQ(countValConstruct.empty(), false);
	EXPECT_EQ(countValConstruct.front(), -14);
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
	// =====================================================================
	//                        INSERT OPERATIONS
	// =====================================================================
	FList<int> testList = { 1, 2, 3 };

	testList.push_front(0);
	EXPECT_EQ(testList.front(), 0);

	testList.insert_after(testList.cend(), 4);
	EXPECT_TRUE(std::find(testList.begin(), testList.end(), 4) != testList.end());

	// =====================================================================
	// insert_after( const_iterator pos, size_type count, const T& data )
	// =====================================================================

	auto testIt = testList.begin();
	auto otherIt = testList.begin();
	testIt = std::next(testIt);
	testIt = testList.insert_after(testIt, 5, 12);
	std::advance(otherIt, 6);
	EXPECT_EQ(std::count(testList.begin(), testList.end(), 12), 5);
	EXPECT_TRUE(testIt == otherIt);

	// =====================================================================
	// insert_after(const_iterator pos, iterator first, iterator last)
	// =====================================================================

	testList.clear();
	testList = { 0, 1, 2, 3, 4, 5 };
	FList<int> otherList = { 6, 7, 8, 9, 10 };
	testIt = testList.begin();
	testIt = std::next(testIt);

	testIt = testList.insert_after(testIt, otherList.begin(), otherList.end());
	otherIt = testList.begin();
	std::advance(otherIt, 6);
	EXPECT_TRUE(testIt == otherIt);
	EXPECT_EQ(testList.size(), 11);

// 	otherList.clear();
// 	otherList = { 14, 12, 21 };
// 	testList.clear();
// 	testList.insert_after(testList.cbegin(), otherList.begin(), otherList.end());

	// =====================================================================
	// insert_after(const_iterator pos, std::initializer_list<T> ilist)
	// =====================================================================

	testList.clear();
	testList = { 0, 1, 2, 3, 4, 5 };
	std::initializer_list<int> initList = { 100, 101, 102, 103 };
	testIt = testList.begin();

	testIt = testList.insert_after(testIt, initList);
	EXPECT_EQ(testList.size(), 10);
	EXPECT_TRUE(std::find(testList.begin(), testList.end(), 101) != testList.end());
	
	otherIt = testList.begin();
	std::advance(otherIt, 4);
	EXPECT_TRUE(testIt == otherIt);

	testList.clear();

	// =====================================================================
	//                        REMOVE OPERATIONS
	// =====================================================================

	testList = { 4, 1, 2, 3, 0 };
	testList.pop_front();
	EXPECT_EQ(testList.front(), 3);

	testIt = testList.begin();
	std::advance(testIt, testList.size() - 2); // - 2 to erase the last element of the list as we erase the element AFTER the iterator
	testList.erase_after(testIt);
	EXPECT_TRUE(std::find(testList.begin(), testList.end(), 4) == testList.end());

	testList.clear();
	testList = { 0, 1, 2, 3, 4, 5 };
	testIt = testList.begin();
	std::advance(testIt, 3);
	otherIt = testList.erase_after(testList.cbegin(), testIt);
	EXPECT_TRUE(testIt == otherIt);
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

TEST(FListTest, Assingment)
{
	// Copy Assign
	FList<int> testList;
	EXPECT_TRUE(testList.empty());

	FList<int> otherList = { 1, 2, 3, 4, 5 };
	EXPECT_FALSE(otherList.empty());

	testList = otherList;
	EXPECT_FALSE(testList.empty());
	EXPECT_FALSE(otherList.empty());
	EXPECT_TRUE(std::find(testList.begin(), testList.end(), 3) != testList.end());

	// InitList Assign
	std::initializer_list<int> initList {0, -1, -2, -3, -4};
	testList = initList;
	EXPECT_FALSE(std::find(testList.begin(), testList.end(), 3) != testList.end());
	EXPECT_TRUE(std::find(testList.begin(), testList.end(), -3) != testList.end());

	// Move Assign
	FList<int> movableList = { 10, 11, 12, 13, 14, 15 };
	EXPECT_FALSE(movableList.empty());

	testList = std::move(movableList);
	EXPECT_TRUE(movableList.empty());
	EXPECT_FALSE(std::find(testList.begin(), testList.end(), -3) != testList.end());
	EXPECT_TRUE(std::find(testList.begin(), testList.end(), 10) != testList.end());
}

#pragma endregion FListTests