#pragma once

#include <algorithm>
#include <string>

#include <Stack.hpp>

#include <List.hpp>
#include <Vector.hpp>

#pragma region StackTests
// ================================================
// ==============   STACK TESTS   =================
// ================================================

TEST(StackTest, Constructor)
{
	// Container = Vector
	Stack<int, Vector<int>> vecStack;
	EXPECT_EQ(vecStack.size(), 0);
	EXPECT_EQ(vecStack.empty(), true);

	// Container = List
	Stack<int, List<int>> listStack;
	EXPECT_EQ(listStack.size(), 0);
	EXPECT_EQ(listStack.empty(), true);

	// Container = DeQue
	Stack<int, DeQue<int>> dequeStack;
	EXPECT_EQ(dequeStack.size(), 0);
	EXPECT_EQ(dequeStack.empty(), true);
}

TEST(StackTest, PushPop)
{
	// Container = Vector
	Stack<int, Vector<int>> vecStack;
	vecStack.push(3);
	EXPECT_EQ(vecStack.size(), 1);
	EXPECT_EQ(vecStack.empty(), false);
	EXPECT_EQ(vecStack.top(), 3);

	// Container = List
	Stack<int, List<int>> listStack;
	listStack.push(2);
	EXPECT_EQ(listStack.size(), 1);
	EXPECT_EQ(listStack.empty(), false);
	EXPECT_EQ(listStack.top(), 2);

	// Container = DeQue
	Stack<int, DeQue<int>> dequeStack;
	dequeStack.push(2);
	EXPECT_EQ(dequeStack.size(), 1);
	EXPECT_EQ(dequeStack.empty(), false);
	EXPECT_EQ(dequeStack.top(), 2);
}

TEST(StackTest, Accessors)
{
	// Container = Vector
	Stack<int, Vector<int>> vecStack;
	EXPECT_THROW(vecStack.top(), std::runtime_error);
	EXPECT_EQ(vecStack.empty(), true);

	// Container = List
	Stack<int, List<int>> listStack;
	EXPECT_THROW(listStack.top(), std::runtime_error);
	EXPECT_EQ(listStack.empty(), true);

	// Container = DeQue
	Stack<int, DeQue<int>> dequeStack;
	EXPECT_THROW(dequeStack.top(), std::runtime_error);
	EXPECT_EQ(dequeStack.empty(), true);
}

TEST(StackTest, Assignment)
{
	// Container = Vector
	Stack<int, Vector<int>> test;
	for (int i = 0; i < 100; ++i)
	{
		test.push(i);
	}

	EXPECT_EQ(test.size(), 100);

	Stack<int, Vector<int>> otherTest;
	EXPECT_TRUE(otherTest.empty() == true);

	otherTest = test;
	EXPECT_EQ(otherTest.size(), 100);

	// Container = DeQue
	Stack<int, DeQue<int>> dequeTest;
	for (int i = 0; i < 100; ++i)
	{
		dequeTest.push(i);
	}
	Stack<int, DeQue<int>> otherDequeTest;
	EXPECT_TRUE(otherDequeTest.empty() == true);

	otherDequeTest = dequeTest;
	EXPECT_EQ(otherDequeTest.size(), 100);

	// Container = List
	Stack<int, List<int>> listTest;
	for (int i = 0; i < 100; ++i)
	{
		listTest.push(i);
	}
	Stack<int, List<int>> otherListTest;
	EXPECT_TRUE(otherListTest.empty() == true);

	otherListTest = listTest;
	EXPECT_EQ(otherListTest.size(), 100);
}

#pragma endregion StackTests