#pragma once

#include <algorithm>

#include "../DataStructures/include/DeQue.hpp"

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

}

// Test at() and operator []
TEST(DequeTest, Accessors)
{

}