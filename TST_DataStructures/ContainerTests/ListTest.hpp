#pragma once

#include <algorithm>
#include <string>

#include "List.hpp"

#pragma region ListTests
// ================================================
// ==============   LIST TESTS   =================
// ================================================

TEST(ListTest, Constructor)
{
	// Default Constructor
	List<int> emptyList;
	EXPECT_EQ(emptyList.size(), 0);
	EXPECT_EQ(emptyList.empty(), true);

	// InitList Constructor
	List<int> initList = { 1, 2, 3 };
	EXPECT_EQ(initList.size(), 3);
	EXPECT_EQ(initList.empty(), false);

	// Copy Constructor
	List<int> copyConstruct = initList;
	EXPECT_EQ(copyConstruct.size(), 3);
	EXPECT_EQ(copyConstruct.empty(), false);

	// Move Constructor
	List<int> moveConstruct = std::move(copyConstruct);
	EXPECT_EQ(moveConstruct.size(), 3);
	EXPECT_EQ(copyConstruct.size(), 0);
	EXPECT_EQ(moveConstruct.empty(), false);
	EXPECT_EQ(copyConstruct.empty(), true);

	// Iterator Constructor
	List<int> itConstruct = List<int>(moveConstruct.begin(), moveConstruct.end());
	EXPECT_EQ(itConstruct.size(), 3);
	EXPECT_EQ(itConstruct.empty(), false);
	EXPECT_EQ(itConstruct.front(), 1);

	// Count default Constructor
	List<int> countDefConstruct = List<int>(5);
	EXPECT_EQ(countDefConstruct.size(), 5);
	EXPECT_EQ(countDefConstruct.empty(), false);
	EXPECT_EQ(countDefConstruct.front(), 0);

	// Count Val Constructor
	List<int> countValConstruct = List<int>(5, -14);
	EXPECT_EQ(countValConstruct.size(), 5);
	EXPECT_EQ(countValConstruct.empty(), false);
	EXPECT_EQ(countValConstruct.front(), -14);
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
TEST(ListTest, InsertAndRemove)
{
	// insert block
	List<int> testList = { 1, 2, 3 };

	testList.insert(testList.begin(), 0);
	EXPECT_EQ(testList.front(), 0);

	testList.insert(testList.end(), 4);
	EXPECT_EQ(testList.back(), 4);

	auto it = testList.begin();
	std::advance(it, 3);
	testList.insert(it, -5);
	EXPECT_FALSE(std::find(testList.begin(), testList.end(), -5) == testList.end());

	// remove block
	testList.erase(testList.begin());
	EXPECT_EQ(testList.front(), 1);

	it = testList.begin();
	std::advance(it, testList.size() - 1);
	testList.erase(it);
	EXPECT_EQ(testList.back(), 3);

	it = testList.begin();
	std::advance(it, 2);
	testList.erase(it);
	EXPECT_TRUE(std::find(testList.begin(), testList.end(), -5) == testList.end());

	testList.clear();
	EXPECT_TRUE(testList.empty() == true);
	EXPECT_EQ(testList.size(), 0);
	EXPECT_THROW(testList.front(), std::runtime_error);

	// =====================================================================
	// iterator insert( const_iterator pos, size_type count, const T& data )
	// =====================================================================

	it = testList.insert(testList.cbegin(), 45, -1);
	EXPECT_TRUE(testList.empty() == false);
	EXPECT_EQ(testList.size(), 45);
	EXPECT_TRUE(it == testList.cbegin());

	it = testList.insert(testList.cbegin(), 5, -2);
	EXPECT_EQ(testList.front(), -2);
	EXPECT_EQ(testList.size(), 50);
	EXPECT_TRUE(it == testList.cbegin());

	it = testList.insert(testList.cend(), 10, 0);
	EXPECT_EQ(testList.back(), 0);
	EXPECT_EQ(testList.size(), 60);
	auto otherIt = testList.begin();
	std::advance(otherIt, 51);
	EXPECT_TRUE(otherIt == it);
	EXPECT_EQ(it.m_Ptr->m_Data, 0);
	it = --it;
	EXPECT_EQ(it.m_Ptr->m_Data, -1);

	it = testList.begin();
	std::advance(it, 25);
	it = testList.insert(it, 15, -15);
	EXPECT_EQ(testList.front(), -2);
	EXPECT_EQ(testList.back(), 0);
	EXPECT_EQ(testList.size(), 75);
	EXPECT_FALSE(std::find(testList.begin(), testList.end(), -15) == testList.end());

	// ==================================================================
	// iterator insert( const_iterator pos, InputIt first, InputIt last )
	// ==================================================================

	List<int> otherList = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

	testList.clear();
	it = otherList.begin();
	std::advance(it, 5);
	it = testList.insert(testList.cbegin(), otherList.begin(), it);
	EXPECT_EQ(testList.size(), 5);
	EXPECT_TRUE(it == testList.begin());
	
	it = otherList.begin();
	std::advance(it, 7);
	otherIt = testList.begin();
	std::advance(otherIt, 2);
	it = testList.insert(otherIt, otherList.begin(), it);
	EXPECT_EQ(testList.size(), 12);
	EXPECT_TRUE(std::find(testList.begin(), testList.end(), 4) != testList.end());
	otherIt = testList.begin();
	std::advance(otherIt, 2);
	EXPECT_TRUE(it == otherIt);

	it = testList.insert(testList.cend(), otherList.begin(), otherList.end());
	EXPECT_EQ(testList.size(), 23);

	// =====================================================================
	// iterator insert( const_iterator pos, std::initializer_list<T> ilist )
	// =====================================================================

	testList.clear();
	it = testList.insert(testList.cbegin(), { 1, 2, 3, 4 });
	EXPECT_EQ(testList.size(), 4);
	EXPECT_TRUE(it == testList.begin());

	it = testList.insert(testList.cend(), { 5, 6, 7, 8 });
	EXPECT_EQ(testList.size(), 8);
	otherIt = testList.begin();
	std::advance(otherIt, 4);
	EXPECT_TRUE(it == otherIt);

	it = testList.insert(otherIt, { 10, 9 });
	EXPECT_EQ(testList.size(), 10);
	otherIt = testList.begin();
	std::advance(otherIt, 4);
	EXPECT_TRUE(it == otherIt);
	EXPECT_TRUE(std::find(testList.begin(), testList.end(), 8) != testList.end());

	// =====================================================================
	// iterator erase(const_iterator pos)
	// =====================================================================
	
	testList.clear();
	testList = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	// iterator setup
	it = testList.begin();
	std::advance(it, 5);
	otherIt = testList.begin();
	std::advance(otherIt, 6);

	it = testList.erase(it);
	EXPECT_TRUE(std::find(testList.begin(), testList.end(), 5) == testList.end());
	EXPECT_EQ(testList.size(), 10);
	EXPECT_TRUE(it == otherIt);

	// =====================================================================
	// iterator erase(const_iterator first, const_iterator last)
	// =====================================================================

	testList.clear();
	testList = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	// iterator setup
	it = testList.begin();
	std::advance(it, 2);
	otherIt = testList.begin();
	std::advance(otherIt, 6);

	it = testList.erase(it, otherIt);
	EXPECT_TRUE(std::find(testList.begin(), testList.end(), 2) == testList.end());
	EXPECT_TRUE(std::find(testList.begin(), testList.end(), 5) == testList.end());
	EXPECT_EQ(testList.size(), 7);
	EXPECT_TRUE(it == otherIt);
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

TEST(ListTest, Assignment)
{
	// Copy Assign
	List<int> testList;
	EXPECT_TRUE(testList.empty());

	List<int> otherList = { 1, 2, 3, 4, 5 };
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
	List<int> movableList = { 10, 11, 12, 13, 14, 15 };
	EXPECT_FALSE(movableList.empty());

	testList = std::move(movableList);
	EXPECT_TRUE(movableList.empty());
	EXPECT_FALSE(std::find(testList.begin(), testList.end(), -3) != testList.end());
	EXPECT_TRUE(std::find(testList.begin(), testList.end(), 10) != testList.end());
}

#pragma endregion ListTests
