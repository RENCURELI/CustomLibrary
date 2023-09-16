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
	// Container = Vector
	// Psuh
	PriorityQueue<int> vecQueue;
	vecQueue.push(3);
	EXPECT_EQ(vecQueue.size(), 1);
	EXPECT_EQ(vecQueue.empty(), false);
	EXPECT_EQ(vecQueue.top(), 3);

	vecQueue.push(5);
	EXPECT_EQ(vecQueue.size(), 2);
	EXPECT_EQ(vecQueue.empty(), false);
	EXPECT_EQ(vecQueue.top(), 5);

	vecQueue.push(1);
	EXPECT_EQ(vecQueue.size(), 3);
	EXPECT_EQ(vecQueue.empty(), false);
	EXPECT_EQ(vecQueue.top(), 5);

	// Pop
	vecQueue.pop();
	EXPECT_EQ(vecQueue.size(), 2);
	EXPECT_EQ(vecQueue.empty(), false);
	EXPECT_EQ(vecQueue.top(), 3);

	// Container = Deque
	PriorityQueue<int, DeQue<int>> dequeQueue;
	dequeQueue.push(3);
	EXPECT_EQ(dequeQueue.size(), 1);
	EXPECT_EQ(dequeQueue.empty(), false);
	EXPECT_EQ(dequeQueue.top(), 3);

	dequeQueue.push(5);
	EXPECT_EQ(dequeQueue.size(), 2);
	EXPECT_EQ(dequeQueue.empty(), false);
	EXPECT_EQ(dequeQueue.top(), 5);

	dequeQueue.push(1);
	EXPECT_EQ(dequeQueue.size(), 3);
	EXPECT_EQ(dequeQueue.empty(), false);
	EXPECT_EQ(dequeQueue.top(), 5);

	// Pop
	dequeQueue.pop();
	EXPECT_EQ(dequeQueue.size(), 2);
	EXPECT_EQ(dequeQueue.empty(), false);
	EXPECT_EQ(dequeQueue.top(), 3);
}

TEST(PriorityQueueTest, Accessors)
{
	// Container = Vector
	PriorityQueue<int> vecQueue;
	EXPECT_THROW(vecQueue.top(), std::runtime_error);
	EXPECT_EQ(vecQueue.empty(), true);

	// Container = DeQue
	PriorityQueue<int, DeQue<int>> dequeQueue;
	EXPECT_THROW(dequeQueue.top(), std::runtime_error);
	EXPECT_EQ(dequeQueue.empty(), true);
}

TEST(PriorityQueueTest, Assignment)
{
	// Container = Vector
	PriorityQueue<int, Vector<int>> test;
	for (int i = 0; i < 100; ++i)
	{
		test.push(i);
	}

	EXPECT_EQ(test.size(), 100);

	PriorityQueue<int, Vector<int>> otherTest;
	EXPECT_TRUE(otherTest.empty() == true);

	otherTest = test;
	EXPECT_EQ(otherTest.size(), 100);

	// Container = DeQue
	PriorityQueue<int, DeQue<int>> dequeTest;
	for (int i = 0; i < 100; ++i)
	{
		dequeTest.push(i);
	}
	PriorityQueue<int, DeQue<int>> otherDequeTest;
	EXPECT_TRUE(otherDequeTest.empty() == true);

	otherDequeTest = dequeTest;
	EXPECT_EQ(otherDequeTest.size(), 100);
}

TEST(PriorityQueueTest, Comparison)
{
	Vector<int> testVec = { 1, 2, 3, 4, 5 };
	PriorityQueue<int> firstQueue = PriorityQueue<int>(std::less<int>(), testVec);
	PriorityQueue<int> equalQueue = PriorityQueue<int>(std::less<int>(), testVec);

	EXPECT_TRUE(firstQueue == equalQueue);

	Vector<int> otherVec = { 1, 2, -3, 4, 5 };
	PriorityQueue<int> diffQueue = PriorityQueue<int>(std::less<int>(), otherVec);
	EXPECT_FALSE(firstQueue == diffQueue);

	EXPECT_EQ(firstQueue <=> equalQueue, std::strong_ordering::equal);
	EXPECT_EQ(firstQueue <=> diffQueue, std::strong_ordering::greater);
}

#pragma endregion PriorityQueueTests