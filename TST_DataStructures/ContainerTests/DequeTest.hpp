#pragma once

#include <algorithm>
#include <forward_list>
#include <vector>

#include "../DataStructures/include/DeQue.hpp"

// for comparative testing against std::vector
#include "../DataStructures/include/Vector.hpp"

// ================================================
// ==============   DEQUE TESTS   =================
// ================================================

TEST(DequeTest, DequeConstructor)
{
	// Default Constructor
	DeQue<int> defaultConstructor = DeQue<int>();
	EXPECT_EQ(defaultConstructor.size(), 0);

	for (int i = 0; i < 10; ++i)
	{
		defaultConstructor.push_back(154);
	}

	// Copy Constructor
	DeQue<int>copyConstructor = DeQue<int>(defaultConstructor);
	EXPECT_EQ(defaultConstructor.size(), 10);
	auto it = copyConstructor.begin();

	// Iterator based constructor -> copies in range [first, last)
	DeQue<int>iteratorConstructor = DeQue<int>(copyConstructor.begin(), copyConstructor.end());
	auto otherIt = iteratorConstructor.begin();
	EXPECT_TRUE(it == otherIt);

	// Initializer list based constructor
	DeQue<int> initListDeque = { 0, 1, 2, 3 };
	EXPECT_EQ(initListDeque.size(), 4);
	EXPECT_TRUE(std::find(initListDeque.begin(), initListDeque.end(), 3) != initListDeque.end());

	// Count value constructor
	DeQue<int> countValConstructor = DeQue<int>(10, 5);
	EXPECT_EQ(countValConstructor.size(), 10);
	EXPECT_TRUE(std::find(countValConstructor.begin(), countValConstructor.end(), 5) != countValConstructor.end());
	EXPECT_FALSE(std::find(countValConstructor.begin(), countValConstructor.end(), 3) != countValConstructor.end());

	// Count default constructed T constructor
	DeQue<int> countDefaultConstructor = DeQue<int>(10);
	EXPECT_EQ(countDefaultConstructor.size(), 10);
	EXPECT_TRUE(std::find(countDefaultConstructor.begin(), countDefaultConstructor.end(), 0) != countDefaultConstructor.end());
	EXPECT_FALSE(std::find(countDefaultConstructor.begin(), countDefaultConstructor.end(), 3) != countDefaultConstructor.end());
}

// Used to test push_front, push_back, pop_front and pop_back
TEST(DequeTest, PushAndPop)
{
	DeQue<int> testDeque = DeQue<int>();
	EXPECT_TRUE(testDeque.begin() == testDeque.end());

	testDeque.push_back(0);
	EXPECT_EQ(testDeque.size(), 1);
	EXPECT_EQ(*testDeque.begin(), 0);

	testDeque.push_front(-1);
	EXPECT_EQ(testDeque.size(), 2);
	EXPECT_EQ(*testDeque.begin(), -1);

	for (int i = 0; i < 10; ++i)
	{
		testDeque.push_back(i);
	}
	EXPECT_EQ(testDeque.size(), 12);
	EXPECT_FALSE(std::find(testDeque.begin(), testDeque.end(), 3) == testDeque.end());

	auto it = testDeque.begin();
	it = std::next(it);

	// Trigger a resize
	for (int i = 0; i < 100; ++i)
	{
		testDeque.push_front(i);
	}
	EXPECT_EQ(testDeque.size(), 112);
	// The find is used to confirm the resize keeps the data readable
	EXPECT_FALSE(std::find(testDeque.begin(), testDeque.end(), 99) == testDeque.end());
	// If iterator is invalidated during resize, this will blow up ( but there is no real way of checking iterator validity )
	EXPECT_EQ(*it, 0);

	// Now we pop data out of the Deque
	// First, we check the current last element
	it = testDeque.begin();
	std::advance(it, testDeque.size() - 1);
	EXPECT_EQ(*it, 9);

	// Pop back
	testDeque.pop_back();
	// Check the new final element
	it = testDeque.begin();
	std::advance(it, testDeque.size() - 1);
	EXPECT_EQ(*it, 8);

	// Pop Front
	it = testDeque.begin();
	EXPECT_EQ(*it, 99);

	testDeque.pop_front();
	it = testDeque.begin();
	EXPECT_EQ(*it, 98);
}

// Test at(), front(), back() and operator []
TEST(DequeTest, Accessors)
{
	DeQue<int> testDeque = { 0, 1, 2, 3, 4, 5, 6 ,7, 8, 9 };
	EXPECT_EQ(testDeque.front(), 0);
	EXPECT_EQ(testDeque.back(), 9);
	EXPECT_EQ(testDeque.at(2), 2);
	EXPECT_EQ(testDeque[5], 5);
}

TEST(DequeTest, Resizing)
{
	DeQue<int> testDeque = { 0, 1, 2, 3, 4, 5, 6 ,7, 8, 9 };
	EXPECT_EQ(testDeque.size(), 10);

	testDeque.resize(15);
	EXPECT_EQ(testDeque.size(), 15);

	testDeque.resize(5);
	EXPECT_EQ(testDeque.size(), 5);
	EXPECT_TRUE(std::find(testDeque.begin(), testDeque.end(), 10) == testDeque.end());

	testDeque.resize(15, 12);
	EXPECT_EQ(testDeque.size(), 15);
	EXPECT_EQ(std::count(testDeque.begin(), testDeque.end(), 12), 10);
}

TEST(DequeTest, Insertion)
{
	DeQue<int> testDeque = { 0, 1, 2, 3, 4, 5, 6 ,7, 8, 9 };
	auto it = testDeque.cbegin();
	std::advance(it, 3);
	auto returnedIt = testDeque.insert(it, 10);

	EXPECT_FALSE(std::find(testDeque.begin(), testDeque.end(), 10) == testDeque.end());
	EXPECT_EQ(*returnedIt, 10);

	// insert count values
	it = testDeque.cbegin();
	std::advance(it, 3);
	returnedIt = testDeque.insert(it, 10, 150);

	EXPECT_FALSE(std::find(testDeque.begin(), testDeque.end(), 150) == testDeque.end());
	EXPECT_EQ(*returnedIt, 150);
	returnedIt = std::find(testDeque.begin(), testDeque.end(), 10);
	EXPECT_EQ(*(--returnedIt), 150);

	// insert iter first, iter last ( bidirectional )
	std::vector<int> insertableVec = { -1, -2, -3, -4, -5 };
	it = testDeque.cbegin();
	std::advance(it, 10);
	returnedIt = testDeque.insert(it, insertableVec.begin(), insertableVec.end());

	EXPECT_FALSE(std::find(testDeque.begin(), testDeque.end(), -3) == testDeque.end());

	// insert iter first, iter last ( non-bidirectional )
	std::forward_list<int> insertableFList = { -10, -20, -30, -40, -50 };
	it = testDeque.cbegin();
	std::advance(it, 12);
	returnedIt = testDeque.insert(it, insertableFList.begin(), insertableFList.end());

	EXPECT_FALSE(std::find(testDeque.begin(), testDeque.end(), -30) == testDeque.end());

	// insert iter first, iter last ( bidirectional )
	Vector<int> customVec = { 100, 101, 102, 103, 104, 105 };
	it = testDeque.cbegin();
	std::advance(it, 15);
	returnedIt = testDeque.insert(it, customVec.begin(), customVec.end());

	EXPECT_FALSE(std::find(testDeque.begin(), testDeque.end(), 102) == testDeque.end());

	// insert initializer_list
	it = testDeque.cbegin();
	std::advance(it, 22);
	returnedIt = testDeque.insert(it, std::initializer_list<int>{110, 120, 130, 140, 150});

	EXPECT_FALSE(std::find(testDeque.begin(), testDeque.end(), 120) == testDeque.end());
}

TEST(DequeTest, ClearAndErase)
{
	DeQue<int> testDeque = { 0, 1, 2, 3, 4, 5, 6 ,7, 8, 9 };
	EXPECT_EQ(testDeque.size(), 10);

	// CLEAR
	testDeque.clear();
	EXPECT_EQ(testDeque.size(), 0);
	EXPECT_TRUE(std::find(testDeque.begin(), testDeque.end(), 5) == testDeque.end());

	testDeque.insert(testDeque.cbegin(), std::initializer_list<int>{110, 120, 130, 140, 150});
	EXPECT_EQ(testDeque.size(), 5);
	EXPECT_FALSE(std::find(testDeque.begin(), testDeque.end(), 120) == testDeque.end());

	// Erase(pos) - First half
	auto it = testDeque.cbegin();
	std::advance(it, 2);
	auto returnedIt = testDeque.erase(it);
	EXPECT_EQ(testDeque.size(), 4);
	EXPECT_TRUE(std::find(testDeque.begin(), testDeque.end(), 130) == testDeque.end());

	// Erase(pos) - Second half
	it = testDeque.cbegin();

	// Just to add some buffer
	testDeque.push_back(160);
	testDeque.push_back(170);

	std::advance(it, 4);
	returnedIt = testDeque.erase(it);
	EXPECT_EQ(testDeque.size(), 5);
	EXPECT_TRUE(std::find(testDeque.begin(), testDeque.end(), 160) == testDeque.end());

	testDeque.clear();

	// Erase(iter first, iter last) - First half
	testDeque.insert(testDeque.cbegin(), std::initializer_list<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19});
	EXPECT_EQ(testDeque.size(), 20);
	EXPECT_TRUE(std::find(testDeque.begin(), testDeque.end(), 16) != testDeque.end());

	// Empty range and empty range pointing to end should work and not erase anything
	returnedIt = testDeque.erase(testDeque.cbegin(), testDeque.cbegin());
	EXPECT_EQ(testDeque.size(), 20);
	EXPECT_TRUE(std::find(testDeque.begin(), testDeque.end(), 0) != testDeque.end());
	EXPECT_TRUE(returnedIt == testDeque.begin());

	returnedIt = testDeque.erase(testDeque.cend(), testDeque.cend());
	EXPECT_EQ(testDeque.size(), 20);
	EXPECT_TRUE(std::find(testDeque.begin(), testDeque.end(), 19) != testDeque.end());
	EXPECT_TRUE(returnedIt == testDeque.end());

	testDeque.erase(testDeque.cbegin(), testDeque.cbegin() + 5);
	EXPECT_EQ(testDeque.size(), 15);
	EXPECT_FALSE(std::find(testDeque.begin(), testDeque.end(), 3) != testDeque.end());
	EXPECT_EQ(*testDeque.begin(), 5);

	// Erase(iter first, iter last) - Second half
	it = testDeque.cbegin();
	std::advance(it, 8);
	returnedIt = testDeque.erase(it, testDeque.cend());
	EXPECT_EQ(testDeque.size(), 8);
	EXPECT_FALSE(std::find(testDeque.begin(), testDeque.end(), 19) != testDeque.end());
	EXPECT_TRUE(returnedIt == testDeque.end());
}

TEST(DequeTest, Assignment)
{
	DeQue<int> thisDeque = { 0, 1, 2, 3, 4, 5 };
	DeQue<int> otherDeque = { -1, -2, -3, -4, -5 };

	thisDeque = otherDeque;
	EXPECT_EQ(thisDeque.size(), 5);
	EXPECT_FALSE(std::find(thisDeque.begin(), thisDeque.end(), -3) == thisDeque.end());
	EXPECT_TRUE(std::find(thisDeque.begin(), thisDeque.end(), 3) == thisDeque.end());
	
	// Other deque should still be fine
	EXPECT_EQ(otherDeque.size(), 5);
	EXPECT_FALSE(std::find(otherDeque.begin(), otherDeque.end(), -3) == otherDeque.end());
	EXPECT_TRUE(std::find(otherDeque.begin(), otherDeque.end(), 3) == otherDeque.end());

	thisDeque = std::initializer_list<int>{ 0, 1, 2, 3 };
	EXPECT_EQ(thisDeque.size(), 4);
	EXPECT_FALSE(std::find(thisDeque.begin(), thisDeque.end(), -3) != thisDeque.end());
	EXPECT_TRUE(std::find(thisDeque.begin(), thisDeque.end(), 3) != thisDeque.end());
}