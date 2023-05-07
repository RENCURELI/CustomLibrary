#include "pch.h"
#include <gtest/gtest.h>
#include <string>
#include "../DataStructures/include/Array.hpp"
#include "../DataStructures/include/Vector.hpp"
#include "../DataStructures/include/List.hpp"
#include "../DataStructures/include/FList.hpp"
#include "../DataStructures/include/Stack.hpp"

#pragma region ArrayTests
// ================================================
// ==============   ARRAY TESTS   =================
// ================================================
TEST(ArrayTest, ArraySwap)
{
	Array<int, 5> firstArray{ 1, 2, 3, 4, 5 };
	Array<int, 5> secondArray{ 6, 7, 8, 9, 10 };

	firstArray.swap(secondArray);

	// We test the first, last and median values
	EXPECT_EQ(firstArray.back(), 10);
	EXPECT_EQ(firstArray.front(), 6);
	EXPECT_EQ(firstArray.at(2), 8);
}

TEST(ArrayTest, ArrayAt)
{
	Array<int, 5> testArray{ 1, 2, 3, 4, 5 };

	EXPECT_EQ(testArray.at(0), testArray.front());
	EXPECT_EQ(testArray.at(testArray.size() - 1), testArray.back());

	// Test for negative index
	EXPECT_THROW(testArray.at(-1), std::exception);

	// Test for negative overflowing index
	EXPECT_THROW(testArray.at(testArray.size()), std::exception);
}

TEST(ArrayTest, ArraySize)
{
	Array<int, 0> emptyArray;

	EXPECT_EQ(emptyArray.empty(), true);
	EXPECT_EQ(emptyArray.size(), 0);

	Array<int, 5> nonEmptyArray;

	EXPECT_EQ(nonEmptyArray.empty(), false);
	EXPECT_EQ(nonEmptyArray.size(), 5);
}

TEST(ArrayTest, ArrayFill)
{
	Array<int, 3> testArray;
	testArray.fill(12);

	for (unsigned int i = 0; i < testArray.size(); i++)
		EXPECT_EQ(testArray.at(i), 12);
}

#pragma endregion ArrayTests

#pragma region VectorTests
// ================================================
// ==============   VECTOR TESTS   =================
// ================================================

TEST(VectorTest, VectorConstructor)
{
	Vector<int> defaultConstructor = Vector<int>();
	EXPECT_EQ(defaultConstructor.size(), 0);
	EXPECT_EQ(defaultConstructor.capacity(), 4);

	Vector<int> initList = { 1, 2, 3, 4 };
	EXPECT_EQ(initList.size(), 4);
	EXPECT_EQ(initList.capacity(), 4);
	EXPECT_EQ(initList.front(), 1);
	EXPECT_EQ(initList.back(), 4);

	Vector<int> copyConstructor = initList;
	EXPECT_EQ(copyConstructor.size(), 4);
	EXPECT_EQ(copyConstructor.capacity(), 4);
	EXPECT_EQ(copyConstructor.front(), 1);
	EXPECT_EQ(copyConstructor.back(), 4);
	EXPECT_EQ(initList.size(), 4);

	Vector<int> customConstructor = Vector<int>(4, 1);
	EXPECT_EQ(customConstructor.size(), 4);
	EXPECT_EQ(customConstructor.capacity(), 4);
	EXPECT_EQ(customConstructor.front(), 1);
	EXPECT_EQ(customConstructor.back(), 1);
}

// These tests are for at, first, last, and [] operator
TEST(VectorTest, VectorAccessors)
{
	Vector<int> testVec = { 1, 2, 3, 4, 5 };
	EXPECT_EQ(testVec.front(), 1);
	EXPECT_EQ(testVec.back(), 5);
	EXPECT_EQ(testVec.at(2), 3);
	EXPECT_EQ(testVec[3], 4);

	// Error testing
	EXPECT_THROW(testVec.at(testVec.size()), std::out_of_range);
}

TEST(VectorTest, VectorIterators)
{
	Vector<int> testVec = { 1, 2, 3, 4, 5 };
	EXPECT_EQ(*testVec.begin(), 1);
	EXPECT_FALSE(std::find(testVec.begin(), testVec.end(), 3) == testVec.end());
	EXPECT_TRUE(testVec.end() == testVec.rbegin().base());
	EXPECT_EQ(*testVec.rbegin(), 5);

	testVec.clear();
	EXPECT_TRUE(testVec.begin() == testVec.end());

	testVec = { 1, 2, 3, 4, 5 };
	EXPECT_FALSE(testVec.begin() == testVec.end());
	EXPECT_EQ(testVec.end() - testVec.begin(), testVec.size());

	testVec.pop_back();
	EXPECT_EQ(*testVec.rbegin(), 4);
}

TEST(VectorTest, Resizing)
{
	Vector<int> testVec = { 1, 2, 3, 4, 5 };

	testVec.resize(12);
	EXPECT_EQ(testVec.size(), 5);
	EXPECT_EQ(testVec.capacity(), 12);

	testVec.resize(10, 10);
	EXPECT_EQ(testVec.back(), 10);
	EXPECT_EQ(testVec.size(), 10);
	EXPECT_EQ(testVec.capacity(), 12);

	testVec.reserve(25);
	EXPECT_EQ(testVec.capacity(), 25);

	testVec.reserve(10);
	EXPECT_EQ(testVec.capacity(), 25);

	testVec.resize(5);
	EXPECT_EQ(testVec.back(), 5);
	EXPECT_EQ(testVec.size(), 5);
	EXPECT_EQ(testVec.capacity(), 25);

	testVec.shrinkToFit();
	EXPECT_EQ(testVec.back(), 5);
	EXPECT_EQ(testVec.size(), 5);
	EXPECT_EQ(testVec.capacity(), 5);
}

TEST(VectorTest, Insertion)
{
	Vector<int> testVec = { 1, 2, 3, 4, 5 };

	testVec.push_back(6);
	EXPECT_EQ(testVec.size(), 6);
	EXPECT_EQ(testVec.capacity(), 10);

	auto it = testVec.cbegin();
	testVec.insert(std::next(it, 3), 12);
	EXPECT_EQ(testVec.size(), 7);
	EXPECT_EQ(testVec.capacity(), 10);
	EXPECT_EQ(testVec[3], 12);
	EXPECT_THROW(testVec.insert(testVec.end() + testVec.capacity(), 51), std::out_of_range);

	testVec.insert(it + 6, 14);
	EXPECT_EQ(testVec[6], 14);
	
	auto returnedIt = testVec.insert(testVec.end(), -12);
	EXPECT_TRUE(returnedIt == (testVec.end() - 1));
	EXPECT_EQ(*testVec.rbegin(), -12);

	returnedIt = testVec.insert(testVec.begin() + 4, 0);
	EXPECT_TRUE(returnedIt == testVec.begin() + 4);
	EXPECT_EQ(*(testVec.begin() + 4), 0);

	returnedIt = testVec.insert(testVec.begin(), 5, 100);
	EXPECT_TRUE(returnedIt == testVec.begin());
	EXPECT_EQ(*testVec.begin(), 100);
	EXPECT_EQ(*(testVec.begin() + 4), 100);
	EXPECT_EQ(*(testVec.begin() + 5), 1);
	EXPECT_EQ(testVec.size(), 15);
	EXPECT_EQ(testVec.capacity(), 15);

	Vector<int> secondVec = { 10, 20, 30, 40, 50 };
	returnedIt = testVec.insert(testVec.begin() + 5, secondVec.begin() + 1, secondVec.end() - 1);
	EXPECT_TRUE(returnedIt == (testVec.begin() + 5));
	EXPECT_EQ(*(testVec.begin() + 5), 20);
	EXPECT_EQ(*(testVec.begin() + 7), 40);
	EXPECT_EQ(*(testVec.begin() + 8), 1);
	EXPECT_EQ(testVec.size(), 18);
	EXPECT_EQ(testVec.capacity(), 36);

	returnedIt = testVec.insert(testVec.begin(), secondVec.begin(), secondVec.begin());
	EXPECT_TRUE(returnedIt == testVec.begin());
	EXPECT_EQ(*testVec.begin(), 100);
	EXPECT_EQ(testVec.size(), 18);
	EXPECT_EQ(testVec.capacity(), 36);

	returnedIt = testVec.insert(testVec.begin(), { 0, 1, 2, 3 });
	EXPECT_TRUE(returnedIt == testVec.begin());
	EXPECT_EQ(*testVec.begin(), 0);
	EXPECT_EQ(testVec.size(), 22);
	EXPECT_EQ(testVec.capacity(), 36);
}

// For more complex types such as std::string -> Will have to update for this
/*TEST(VectorTest, InsertComplex)
{
	Vector<std::string> stringVec;
	stringVec.push_back("Hello");
	stringVec.push_back("World");
	EXPECT_EQ(stringVec.front(), "Hello");
	EXPECT_EQ(stringVec.back(), "World");
	EXPECT_EQ(stringVec.size(), 2);
	EXPECT_EQ(stringVec.capacity(), 4);

	for (int i = 0; i < 5; i++)
	{
		stringVec.push_back("Reallocating");
	}
	EXPECT_EQ(stringVec.back(), "Reallocating");
	EXPECT_EQ(stringVec.size(), 7);
	EXPECT_EQ(stringVec.capacity(), 8);

	stringVec.insert(2, "Inserting...");
}*/

TEST(VectorTest, Deletion)
{
	Vector<int> testVec = { 1, 2, 3, 4, 5 };

	// Error Testing
	EXPECT_THROW(testVec.erase(testVec.begin() + 3, testVec.begin()), std::exception);
	EXPECT_THROW(testVec.erase(testVec.begin(), testVec.end() + 5), std::out_of_range);
	EXPECT_THROW(testVec.erase(testVec.end() + 1), std::out_of_range);
	EXPECT_EQ(testVec.back(), 5);

	// Functionality
	testVec.pop_back();
	EXPECT_EQ(testVec.back(), 4);
	EXPECT_EQ(testVec.size(), 4);
	EXPECT_EQ(testVec.capacity(), 5);

	auto returnedIt = testVec.erase(testVec.begin());
	EXPECT_TRUE(returnedIt == testVec.begin());
	EXPECT_EQ(testVec.front(), 2);
	EXPECT_EQ(testVec.size(), 3);
	EXPECT_EQ(testVec.capacity(), 5);

	returnedIt = testVec.erase(testVec.begin(), testVec.begin() + 1);
	EXPECT_TRUE(returnedIt == testVec.begin());
	EXPECT_EQ(testVec.front(), 3);
	EXPECT_EQ(testVec.size(), 2);
	EXPECT_EQ(testVec.capacity(), 5);

	testVec.clear();
	EXPECT_EQ(testVec.size(), 0);
	EXPECT_EQ(testVec.capacity(), 5);
	EXPECT_THROW(testVec.front(), std::exception);
	EXPECT_THROW(testVec.back(), std::exception);
	EXPECT_THROW(testVec[0], std::exception);

	for (int i = 0; i < 100; i++)
		testVec.pop_back();
	EXPECT_EQ(testVec.size(), 0);

	testVec = { 1, 2, 3, 4, 5 };
	returnedIt = testVec.erase(testVec.begin() + 2);
	EXPECT_EQ(*returnedIt, 4);

	returnedIt = testVec.erase(testVec.begin() + 1, testVec.end());
	EXPECT_TRUE(returnedIt == testVec.end());
}

TEST(VectorTest, AssignMethods)
{
	Vector<int> testVec = { 1, 2, 3, 4, 5 };
	testVec.assign(5, 10);
	EXPECT_EQ(testVec.size(), 5);
	EXPECT_EQ(testVec.capacity(), 5);
	EXPECT_EQ(testVec.front(), 10);
	EXPECT_EQ(testVec.back(), 10);

	testVec = { 2, 2, 2, 2, 2 };
	EXPECT_EQ(testVec.size(), 5);
	EXPECT_EQ(testVec.capacity(), 5);
	EXPECT_EQ(testVec.front(), 2);
	EXPECT_EQ(testVec.back(), 2);

	Vector<int> newVec = Vector(5, 5);
	testVec = newVec;
	EXPECT_EQ(testVec.size(), 5);
	EXPECT_EQ(testVec.capacity(), 5);
	EXPECT_EQ(testVec.front(), 5);
	EXPECT_EQ(testVec.back(), 5);

	testVec.assign(2, 15);
	EXPECT_EQ(testVec.size(), 2);
	EXPECT_EQ(testVec.capacity(), 5);
	EXPECT_EQ(testVec.front(), 15);
	EXPECT_EQ(testVec.back(), 15);

	testVec = { 10, 10, 10, 10, 10, 10, 10 };
	EXPECT_EQ(testVec.size(), 7);
	EXPECT_EQ(testVec.capacity(), 10);
	EXPECT_EQ(testVec.front(), 10);
	EXPECT_EQ(testVec.back(), 10);
}

#pragma endregion VectorTests

#pragma region ListTests
// ================================================
// ==============   LIST TESTS   =================
// ================================================

TEST(ListTest, Constructor)
{
	List<int> emptyList;
	EXPECT_EQ(emptyList.size(), 0);
	EXPECT_EQ(emptyList.empty(), true);

	List<int> initList = { 1, 2, 3 };
	EXPECT_EQ(initList.size(), 3);
	EXPECT_EQ(initList.empty(), false);

	List<int> copyConstruct = initList;
	EXPECT_EQ(copyConstruct.size(), 3);
	EXPECT_EQ(copyConstruct.empty(), false);
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
TEST(ListTest, InsertAndremove)
{
	// insert block
	List<int> testList = { 1, 2, 3 };

	testList.insert(0, 0);
	EXPECT_EQ(testList.front(), 0);

	testList.insert(4, testList.size());
	EXPECT_EQ(testList.back(), 4);

	// We still need to implement the find algorithm for this case
	//testList.insert(-5, 2);

	// We test error handling
	EXPECT_THROW(testList.insert(-1, -1), std::exception);
	EXPECT_THROW(testList.insert(12, 12), std::exception);

	// remove block
	testList.remove(0);
	EXPECT_EQ(testList.front(), 1);

	testList.remove(testList.size() - 1);
	EXPECT_EQ(testList.back(), 3);

	// We still need to implement the find algorithm for this case
	//testList.remove(2);

	// We test error handling
	EXPECT_THROW(testList.remove(-1), std::exception);
	EXPECT_THROW(testList.remove(12), std::exception);
}

TEST(ListTest, PopAndClear)
{
	List<int> testList = { 1, 2, 3, 4, 5 };
	
	testList.pop_back();
	EXPECT_EQ(testList.back(), 4);

	testList.pop_front();
	EXPECT_EQ(testList.front(), 2);

	testList.Clear();
	EXPECT_EQ(testList.size(), 0);
	EXPECT_EQ(testList.empty(), true);
}

#pragma endregion ListTests

#pragma region FListTests
// ================================================
// ==============   FLIST TESTS   =================
// ================================================

TEST(FListTest, Constructor)
{
	FList<int> emptyList;
	EXPECT_EQ(emptyList.size(), 0);
	EXPECT_EQ(emptyList.empty(), true);

	FList<int> initList = { 1, 2, 3 };
	EXPECT_EQ(initList.size(), 3);
	EXPECT_EQ(initList.empty(), false);

	FList<int> copyConstruct = initList;
	EXPECT_EQ(copyConstruct.size(), 3);
	EXPECT_EQ(copyConstruct.empty(), false);
}

TEST(FListTest, Front)
{
	FList<int> testFrontList = { 1, 2, 3 };

	// Data is filled from the front and thus "inverted"
	EXPECT_EQ(testFrontList.front(), 3);
}

// Here we test Empty, push_back, push_front and size
TEST(FListTest, PushAndSize)
{
	FList<int> testList;
	EXPECT_EQ(testList.size(), 0);
	EXPECT_EQ(testList.empty(), true);

	testList = { 1, 2, 3 };
	EXPECT_EQ(testList.size(), 3);
	EXPECT_EQ(testList.empty(), false);

	testList.push_front(0);

	EXPECT_EQ(testList.front(), 0);
	EXPECT_EQ(testList.size(), 4);
}

// Here we test insert and remove methods
TEST(FListTest, InsertAndremove)
{
	// insert block
	FList<int> testList = { 1, 2, 3 };

	testList.insert(0, 0);
	EXPECT_EQ(testList.front(), 0);

	// We still need to implement the find algorithm for this case
	testList.insert(4, testList.size());
	//EXPECT_EQ(testList.back(), 4);

	// We still need to implement the find algorithm for this case
	//testList.insert(-5, 2);

	// We test error handling
	EXPECT_THROW(testList.insert(-1, -1), std::exception);
	EXPECT_THROW(testList.insert(12, 12), std::exception);

	// remove block
	testList.remove(0);
	EXPECT_EQ(testList.front(), 3);

	// We still need to implement the find algorithm for this case
	testList.remove(testList.size() - 1);
	//EXPECT_EQ(testList.back(), 3);

	// We still need to implement the find algorithm for this case
	//testList.remove(2);

	// We test error handling
	EXPECT_THROW(testList.remove(-1), std::exception);
	EXPECT_THROW(testList.remove(12), std::exception);
}

TEST(FListTest, PopAndClear)
{
	FList<int> testList = { 1, 2, 3, 4, 5 };

	testList.pop_front();
	EXPECT_EQ(testList.front(), 4);

	testList.Clear();
	EXPECT_EQ(testList.size(), 0);
	EXPECT_EQ(testList.empty(), true);
}

#pragma endregion FListTests

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
}

#pragma endregion StackTests

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}