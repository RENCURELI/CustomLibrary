#pragma once

#include<Queue.hpp>

#include <List.hpp>
#include <Vector.hpp>

#pragma region QueueTests
// ================================================
// ==============   QUEUE TESTS   =================
// ================================================

TEST(QueueTest, Constructor)
{
	// Container = Vector
	Queue<int, Vector<int>> vecQueue;
	EXPECT_EQ(vecQueue.size(), 0);
	EXPECT_EQ(vecQueue.empty(), true);

	// Container = List
	Queue<int, List<int>> listQueue;
	EXPECT_EQ(listQueue.size(), 0);
	EXPECT_EQ(listQueue.empty(), true);

	// Container = DeQue
	Queue<int, DeQue<int>> dequeQueue;
	EXPECT_EQ(dequeQueue.size(), 0);
	EXPECT_EQ(dequeQueue.empty(), true);
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

#pragma endregion QueueTests