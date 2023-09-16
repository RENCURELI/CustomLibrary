#pragma once

#include<Queue.hpp>

#include <List.hpp>
#include <Vector.hpp>

#pragma region QueueTests
// ================================================
// ==============   QUEUE TESTS   =================
// ================================================

TEST(QueueTest, VectorConstructor)
{
	// Default Vector
	Queue<int, Vector<int>> vecQueue;
	EXPECT_EQ(vecQueue.size(), 0);
	EXPECT_EQ(vecQueue.empty(), true);

	for (int i = 0; i < 100; ++i)
	{
		vecQueue.push(i);
	}

	EXPECT_EQ(vecQueue.size(), 100);
	EXPECT_EQ(vecQueue.empty(), false);

	// Copy ( implicit )
	Queue<int, Vector<int>> copyConstruct = vecQueue;
	EXPECT_EQ(copyConstruct.size(), 100);
	EXPECT_EQ(copyConstruct.empty(), false);

	// Move ( implicit )
	Queue<int, Vector<int>> moveConstruct = std::move(vecQueue);
	EXPECT_EQ(moveConstruct.size(), 100);
	EXPECT_EQ(moveConstruct.empty(), false);

	// Copy ( explicit )
	Vector<int> testVec = { 1, 2, 3, 4, 5 };
	Queue<int, Vector<int>> copyExplicit = Queue<int, Vector<int>>(testVec);
	EXPECT_EQ(copyExplicit.size(), 5);
	EXPECT_EQ(copyExplicit.empty(), false);

	// Move ( explicit )
	Queue<int, Vector<int>> moveExplicit = Queue<int, Vector<int>>(std::move(testVec));
	EXPECT_EQ(moveExplicit.size(), 5);
	EXPECT_EQ(moveExplicit.empty(), false);
}

TEST(QueueTest, ListConstructor)
{
	// Default List
	Queue<int, List<int>> listQueue;
	EXPECT_EQ(listQueue.size(), 0);
	EXPECT_EQ(listQueue.empty(), true);

	for (int i = 0; i < 100; ++i)
	{
		listQueue.push(i);
	}

	EXPECT_EQ(listQueue.size(), 100);
	EXPECT_EQ(listQueue.empty(), false);

	// Copy ( implicit )
	Queue<int, List<int>> copyConstruct = listQueue;
	EXPECT_EQ(copyConstruct.size(), 100);
	EXPECT_EQ(copyConstruct.empty(), false);

	// Move ( implicit )
	Queue<int, List<int>> moveConstruct = std::move(listQueue);
	EXPECT_EQ(moveConstruct.size(), 100);
	EXPECT_EQ(moveConstruct.empty(), false);

	// Copy ( explicit )
	List<int> testList = { 1, 2, 3, 4, 5 };
	Queue<int, List<int>> copyExplicit = Queue<int, List<int>>(testList);
	EXPECT_EQ(copyExplicit.size(), 5);
	EXPECT_EQ(copyExplicit.empty(), false);

	// Move ( explicit )
	Queue<int, List<int>> moveExplicit = Queue<int, List<int>>(std::move(testList));
	EXPECT_EQ(moveExplicit.size(), 5);
	EXPECT_EQ(moveExplicit.empty(), false);
}

TEST(QueueTest, DequeConstructor)
{
	// Default DeQue
	Queue<int, DeQue<int>> dequeQueue;
	EXPECT_EQ(dequeQueue.size(), 0);
	EXPECT_EQ(dequeQueue.empty(), true);

	for (int i = 0; i < 100; ++i)
	{
		dequeQueue.push(i);
	}

	EXPECT_EQ(dequeQueue.size(), 100);
	EXPECT_EQ(dequeQueue.empty(), false);

	// Copy ( implicit )
	Queue<int, DeQue<int>> copyConstruct = dequeQueue;
	EXPECT_EQ(copyConstruct.size(), 100);
	EXPECT_EQ(copyConstruct.empty(), false);

	// Move ( implicit )
	Queue<int, DeQue<int>> moveConstruct = std::move(dequeQueue);
	EXPECT_EQ(moveConstruct.size(), 100);
	EXPECT_EQ(moveConstruct.empty(), false);

	// Copy ( explicit )
	DeQue<int> testDeque = { 1, 2, 3, 4, 5 };
	Queue<int, DeQue<int>> copyExplicit = Queue<int, DeQue<int>>(testDeque);
	EXPECT_EQ(copyExplicit.size(), 5);
	EXPECT_EQ(copyExplicit.empty(), false);

	// Move ( explicit )
	Queue<int, DeQue<int>> moveExplicit = Queue<int, DeQue<int>>(std::move(testDeque));
	EXPECT_EQ(moveExplicit.size(), 5);
	EXPECT_EQ(moveExplicit.empty(), false);
}

TEST(QueueTest, PushPop)
{
	// Container = Vector
	Queue<int, Vector<int>> vecQueue;
	vecQueue.push(3);
	EXPECT_EQ(vecQueue.size(), 1);
	EXPECT_EQ(vecQueue.empty(), false);
	EXPECT_EQ(vecQueue.front(), 3);

	// Container = List
	Queue<int, List<int>> listQueue;
	listQueue.push(2);
	EXPECT_EQ(listQueue.size(), 1);
	EXPECT_EQ(listQueue.empty(), false);
	EXPECT_EQ(listQueue.front(), 2);

	// Container = DeQue
	Queue<int, DeQue<int>> dequeQueue;
	dequeQueue.push(2);
	EXPECT_EQ(dequeQueue.size(), 1);
	EXPECT_EQ(dequeQueue.empty(), false);
	EXPECT_EQ(dequeQueue.front(), 2);
}

TEST(QueueTest, Accessors)
{
	// Container = Vector
	Queue<int, Vector<int>> vecQueue;
	EXPECT_THROW(vecQueue.front(), std::runtime_error);
	EXPECT_EQ(vecQueue.empty(), true);

	// Container = List
	Queue<int, List<int>> listQueue;
	EXPECT_THROW(listQueue.front(), std::runtime_error);
	EXPECT_EQ(listQueue.empty(), true);

	// Container = DeQue
	Queue<int, DeQue<int>> dequeQueue;
	EXPECT_THROW(dequeQueue.front(), std::runtime_error);
	EXPECT_EQ(dequeQueue.empty(), true);
}

TEST(QueueTest, Assignment)
{
	// Container = Vector
	Queue<int, Vector<int>> test;
	for (int i = 0; i < 100; ++i)
	{
		test.push(i);
	}

	EXPECT_EQ(test.size(), 100);

	Queue<int, Vector<int>> otherTest;
	EXPECT_TRUE(otherTest.empty() == true);

	otherTest = test;
	EXPECT_EQ(otherTest.size(), 100);

	// Container = DeQue
	Queue<int, DeQue<int>> dequeTest;
	for (int i = 0; i < 100; ++i)
	{
		dequeTest.push(i);
	}
	Queue<int, DeQue<int>> otherDequeTest;
	EXPECT_TRUE(otherDequeTest.empty() == true);

	otherDequeTest = dequeTest;
	EXPECT_EQ(otherDequeTest.size(), 100);

	// Container = List
	Queue<int, List<int>> listTest;
	for (int i = 0; i < 100; ++i)
	{
		listTest.push(i);
	}
	Queue<int, List<int>> otherListTest;
	EXPECT_TRUE(otherListTest.empty() == true);

	otherListTest = listTest;
	EXPECT_EQ(otherListTest.size(), 100);
}

TEST(QueueTest, Comparison)
{
	Vector<int> testVec = { 1, 2, 3, 4, 5 };
	Queue<int, Vector<int>> firstQueue = Queue<int, Vector<int>>(testVec);
	Queue<int, Vector<int>> equalQueue = Queue<int, Vector<int>>(testVec);

	EXPECT_TRUE(firstQueue == equalQueue);

	Vector<int> otherVec = { 1, 2, -3, 4, 5 };
	Queue<int, Vector<int>> diffQueue = Queue<int, Vector<int>>(otherVec);
	EXPECT_FALSE(firstQueue == diffQueue);

	EXPECT_EQ(firstQueue <=> equalQueue, std::strong_ordering::equal);
	EXPECT_EQ(firstQueue <=> diffQueue, std::strong_ordering::greater);
}

#pragma endregion QueueTests