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

TEST(StackTest, VectorConstructor)
{
	// Default Vector
	Stack<int, Vector<int>> vecStack;
	EXPECT_EQ(vecStack.size(), 0);
	EXPECT_EQ(vecStack.empty(), true);

	for (int i = 0; i < 100; ++i)
	{
		vecStack.push(i);
	}

	EXPECT_EQ(vecStack.size(), 100);
	EXPECT_EQ(vecStack.empty(), false);

	// Copy ( implicit )
	Stack<int, Vector<int>> copyConstruct = vecStack;
	EXPECT_EQ(copyConstruct.size(), 100);
	EXPECT_EQ(copyConstruct.empty(), false);

	// Move ( implicit )
	Stack<int, Vector<int>> moveConstruct = std::move(vecStack);
	EXPECT_EQ(moveConstruct.size(), 100);
	EXPECT_EQ(moveConstruct.empty(), false);

	// Copy ( explicit )
	Vector<int> testVec = { 1, 2, 3, 4, 5 };
	Stack<int, Vector<int>> copyExplicit = Stack<int, Vector<int>>(testVec);
	EXPECT_EQ(copyExplicit.size(), 5);
	EXPECT_EQ(copyExplicit.empty(), false);

	// Move ( explicit )
	Stack<int, Vector<int>> moveExplicit = Stack<int, Vector<int>>(std::move(testVec));
	EXPECT_EQ(moveExplicit.size(), 5);
	EXPECT_EQ(moveExplicit.empty(), false);
}

TEST(StackTest, ListConstructor)
{
	// Default List
	Stack<int, List<int>> listStack;
	EXPECT_EQ(listStack.size(), 0);
	EXPECT_EQ(listStack.empty(), true);

	for (int i = 0; i < 100; ++i)
	{
		listStack.push(i);
	}

	EXPECT_EQ(listStack.size(), 100);
	EXPECT_EQ(listStack.empty(), false);

	// Copy ( implicit )
	Stack<int, List<int>> copyConstruct = listStack;
	EXPECT_EQ(copyConstruct.size(), 100);
	EXPECT_EQ(copyConstruct.empty(), false);

	// Move ( implicit )
	Stack<int, List<int>> moveConstruct = std::move(listStack);
	EXPECT_EQ(moveConstruct.size(), 100);
	EXPECT_EQ(moveConstruct.empty(), false);

	// Copy ( explicit )
	List<int> testList = { 1, 2, 3, 4, 5 };
	Stack<int, List<int>> copyExplicit = Stack<int, List<int>>(testList);
	EXPECT_EQ(copyExplicit.size(), 5);
	EXPECT_EQ(copyExplicit.empty(), false);

	// Move ( explicit )
	Stack<int, List<int>> moveExplicit = Stack<int, List<int>>(std::move(testList));
	EXPECT_EQ(moveExplicit.size(), 5);
	EXPECT_EQ(moveExplicit.empty(), false);
}

TEST(StackTest, DequeConstructor)
{
	// Default DeQue
	Stack<int, DeQue<int>> dequeStack;
	EXPECT_EQ(dequeStack.size(), 0);
	EXPECT_EQ(dequeStack.empty(), true);

	for (int i = 0; i < 100; ++i)
	{
		dequeStack.push(i);
	}

	EXPECT_EQ(dequeStack.size(), 100);
	EXPECT_EQ(dequeStack.empty(), false);

	// Copy ( implicit )
	Stack<int, DeQue<int>> copyConstruct = dequeStack;
	EXPECT_EQ(copyConstruct.size(), 100);
	EXPECT_EQ(copyConstruct.empty(), false);

	// Move ( implicit )
	Stack<int, DeQue<int>> moveConstruct = std::move(dequeStack);
	EXPECT_EQ(moveConstruct.size(), 100);
	EXPECT_EQ(moveConstruct.empty(), false);

	// Copy ( explicit )
	DeQue<int> testDeque = { 1, 2, 3, 4, 5 };
	Stack<int, DeQue<int>> copyExplicit = Stack<int, DeQue<int>>(testDeque);
	EXPECT_EQ(copyExplicit.size(), 5);
	EXPECT_EQ(copyExplicit.empty(), false);

	// Move ( explicit )
	Stack<int, DeQue<int>> moveExplicit = Stack<int, DeQue<int>>(std::move(testDeque));
	EXPECT_EQ(moveExplicit.size(), 5);
	EXPECT_EQ(moveExplicit.empty(), false);
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

TEST(StackTest, Comparison)
{
	Vector<int> testVec = { 1, 2, 3, 4, 5 };
	Stack<int, Vector<int>> firstStack = Stack<int, Vector<int>>(testVec);
	Stack<int, Vector<int>> equalStack = Stack<int, Vector<int>>(testVec);

	EXPECT_TRUE(firstStack == equalStack);

	Vector<int> otherVec = { 1, 2, -3, 4, 5 };
	Stack<int, Vector<int>> diffStack = Stack<int, Vector<int>>(otherVec);
	EXPECT_FALSE(firstStack == diffStack);

	EXPECT_EQ(firstStack <=> equalStack, std::strong_ordering::equal);
	EXPECT_EQ(firstStack <=> diffStack, std::strong_ordering::greater);
}

#pragma endregion StackTests