#pragma once

#include <algorithm>
#include <string>

#include "../DataStructures/include/DeQue.hpp"
#include "../DataStructures/include/List.hpp"
#include "../DataStructures/include/Vector.hpp"

// Must come last due to dependencies on other classes
#include "../DataStructures/include/Stack.hpp"


#pragma region StackTests
// ================================================
// ==============   STACK TESTS   =================
// ================================================

TEST(StackTest, Constructor)
{
	// Container = Vector
	Stack<int> vecStack;
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
	Stack<int> vecStack;
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
	Stack<int> vecStack;
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

#pragma endregion StackTests