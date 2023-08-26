#pragma once

#include <PriorityQueue.hpp>

// Vector is the default container
#include <DeQue.hpp>

#pragma region PriorityQueueTests
// ================================================
// ===========   PRIORITY QUEUE TESTS   ===========
// ================================================

TEST(PriorityQueueTest, VectorConstructors)
{
	// Container = Vector
	PriorityQueue<int, Vector<int>> defaultConstructor;
	EXPECT_EQ(defaultConstructor.size(), 0);
	EXPECT_EQ(defaultConstructor.empty(), true);

	Vector<int> vecToCopy = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	EXPECT_FALSE(std::is_heap(vecToCopy.cbegin(), vecToCopy.cend()));
	PriorityQueue<int> copyConstructor = PriorityQueue<int>(std::less<int>(), vecToCopy);
	EXPECT_EQ(copyConstructor.size(), 10);
	EXPECT_EQ(copyConstructor.empty(), false);
	EXPECT_TRUE(std::is_heap(copyConstructor.GetContainer().cbegin(), copyConstructor.GetContainer().cend()));

	// Iterator constructor
	PriorityQueue<int> itConstructor = PriorityQueue<int>(vecToCopy.begin(), vecToCopy.end());
	EXPECT_EQ(itConstructor.size(), 10);
	EXPECT_EQ(itConstructor.empty(), false);
	EXPECT_TRUE(std::is_heap(itConstructor.GetContainer().cbegin(), itConstructor.GetContainer().cend()));

	// Iterator To Different Container Type
	PriorityQueue<int, DeQue<int>> itConstructorDiffCont = PriorityQueue<int, DeQue<int>>(vecToCopy.begin(), vecToCopy.end(), std::less<int>(), DeQue<int>());
	EXPECT_EQ(itConstructorDiffCont.size(), 10);
	EXPECT_EQ(itConstructorDiffCont.empty(), false);
	EXPECT_TRUE(std::is_heap(itConstructorDiffCont.GetContainer().cbegin(), itConstructorDiffCont.GetContainer().cend()));
}

TEST(PriorityQueueTest, DequeConstructors)
{
	// Container = DeQue
	PriorityQueue<int, DeQue<int>> defaultConstructor;
	EXPECT_EQ(defaultConstructor.size(), 0);
	EXPECT_EQ(defaultConstructor.empty(), true);

	DeQue<int> dequeToCopy = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	EXPECT_FALSE(std::is_heap(dequeToCopy.cbegin(), dequeToCopy.cend()));
	PriorityQueue<int, DeQue<int>> copyConstructor = PriorityQueue<int, DeQue<int>>(std::less<int>(), dequeToCopy);
	EXPECT_EQ(copyConstructor.size(), 10);
	EXPECT_EQ(copyConstructor.empty(), false);
	EXPECT_TRUE(std::is_heap(copyConstructor.GetContainer().cbegin(), copyConstructor.GetContainer().cend()));

	// Iterator constructor
	PriorityQueue<int, DeQue<int>> itConstructor = PriorityQueue<int, DeQue<int>>(dequeToCopy.begin(), dequeToCopy.end());
	EXPECT_EQ(itConstructor.size(), 10);
	EXPECT_EQ(itConstructor.empty(), false);
	EXPECT_TRUE(std::is_heap(itConstructor.GetContainer().cbegin(), itConstructor.GetContainer().cend()));

	// Iterator To Different Container Type
	PriorityQueue<int> itConstructorDiffCont = PriorityQueue<int>(dequeToCopy.begin(), dequeToCopy.end(), std::less<int>(), Vector<int>());
	EXPECT_EQ(itConstructorDiffCont.size(), 10);
	EXPECT_EQ(itConstructorDiffCont.empty(), false);
	EXPECT_TRUE(std::is_heap(itConstructorDiffCont.GetContainer().cbegin(), itConstructorDiffCont.GetContainer().cend()));
}

TEST(PriorityQueueTest, PushPop)
{

}

TEST(PriorityQueueTest, Accessors)
{

}

TEST(PriorityQueueTest, Assignment)
{

}

#pragma endregion PriorityQueueTests