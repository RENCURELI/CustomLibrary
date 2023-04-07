#include "pch.h"
#include <gtest/gtest.h>
#include "../DataStructures/include/Array.hpp"
#include "../DataStructures/include/Vector.hpp"
#include "../DataStructures/include/List.hpp"
#include "../DataStructures/include/FList.hpp"

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
	EXPECT_EQ(defaultConstructor.getSize(), 4);
	EXPECT_EQ(defaultConstructor.getCapacity(), 4);

	Vector<int> initList = { 1, 2, 3, 4 };
	EXPECT_EQ(initList.getSize(), 4);
	EXPECT_EQ(initList.getCapacity(), 4);

	Vector<int> copyConstructor = initList;
	EXPECT_EQ(copyConstructor.getSize(), 4);
	EXPECT_EQ(copyConstructor.getCapacity(), 4);

	Vector<int> customConstructor = Vector<int>(4, 1);
	EXPECT_EQ(customConstructor.getSize(), 4);
	EXPECT_EQ(customConstructor.getCapacity(), 4);
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
	EXPECT_THROW(testVec.at(testVec.getSize()), std::exception);
}

TEST(VectorTest, Resizing)
{
	Vector<int> testVec = { 1, 2, 3, 4, 5 };

	testVec.resize(12);
	EXPECT_EQ(testVec.getSize(), 5);
	EXPECT_EQ(testVec.getCapacity(), 12);

	testVec.resize(10, 10);
	EXPECT_EQ(testVec.back(), 10);
	EXPECT_EQ(testVec.getSize(), 10);
	EXPECT_EQ(testVec.getCapacity(), 12);

	testVec.reserve(25);
	EXPECT_EQ(testVec.getCapacity(), 25);

	testVec.reserve(10);
	EXPECT_EQ(testVec.getCapacity(), 25);

	testVec.resize(5);
	EXPECT_EQ(testVec.back(), 5);
	EXPECT_EQ(testVec.getSize(), 5);
	EXPECT_EQ(testVec.getCapacity(), 25);
}

TEST(VectorTest, Insertion)
{
	Vector<int> testVec = { 1, 2, 3, 4, 5 };

	testVec.push_back(6);
	EXPECT_EQ(testVec.getSize(), 6);
	EXPECT_EQ(testVec.getCapacity(), 10);

	testVec.insert(3, 12);
	EXPECT_EQ(testVec.getSize(), 7);
	EXPECT_EQ(testVec.getCapacity(), 10);
	EXPECT_EQ(testVec[3], 12);
}

TEST(VectorTest, Deletion)
{
	Vector<int> testVec = { 1, 2, 3, 4, 5 };

	testVec.pop_back();
	EXPECT_EQ(testVec.back(), 4);
	EXPECT_EQ(testVec.getSize(), 4);
	EXPECT_EQ(testVec.getCapacity(), 5);

	testVec.erase(0);
	EXPECT_EQ(testVec.front(), 2);
	EXPECT_EQ(testVec.getSize(), 3);
	EXPECT_EQ(testVec.getCapacity(), 5);

	testVec.erase(0, 1);
	EXPECT_EQ(testVec.front(), 4);
	EXPECT_EQ(testVec.getSize(), 1);
	EXPECT_EQ(testVec.getCapacity(), 5);

	testVec.clear();
	EXPECT_EQ(testVec.getSize(), 0);
	EXPECT_EQ(testVec.getCapacity(), 5);
}

#pragma endregion VectorTests

#pragma region ListTests
// ================================================
// ==============   LIST TESTS   =================
// ================================================

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
	EXPECT_EQ(testList.GetSize(), 0);
	EXPECT_EQ(testList.IsEmpty(), true);

	testList = { 1, 2, 3 };
	EXPECT_EQ(testList.GetSize(), 3);
	EXPECT_EQ(testList.IsEmpty(), false);

	testList.push_front(0);

	EXPECT_EQ(testList.front(), 0);
	EXPECT_EQ(testList.GetSize(), 4);

	testList.push_back(4);

	EXPECT_EQ(testList.back(), 4);
	EXPECT_EQ(testList.GetSize(), 5);
}

// Here we test InsertAt and RemoveAt methods
TEST(ListTest, InsertAndRemoveAt)
{
	// InsertAt block
	List<int> testList = { 1, 2, 3 };

	testList.InsertAt(0, 0);
	EXPECT_EQ(testList.front(), 0);

	testList.InsertAt(4, testList.GetSize());
	EXPECT_EQ(testList.back(), 4);

	// We still need to implement the find algorithm for this case
	//testList.InsertAt(-5, 2);

	// We test error handling
	EXPECT_THROW(testList.InsertAt(-1, -1), std::exception);
	EXPECT_THROW(testList.InsertAt(12, 12), std::exception);

	// RemoveAt block
	testList.RemoveAt(0);
	EXPECT_EQ(testList.front(), 1);

	testList.RemoveAt(testList.GetSize() - 1);
	EXPECT_EQ(testList.back(), 3);

	// We still need to implement the find algorithm for this case
	//testList.RemoveAt(2);

	// We test error handling
	EXPECT_THROW(testList.RemoveAt(-1), std::exception);
	EXPECT_THROW(testList.RemoveAt(12), std::exception);
}

TEST(ListTest, PopAndClear)
{
	List<int> testList = { 1, 2, 3, 4, 5 };
	
	testList.pop_back();
	EXPECT_EQ(testList.back(), 4);

	testList.pop_front();
	EXPECT_EQ(testList.front(), 2);

	testList.Clear();
	EXPECT_EQ(testList.GetSize(), 0);
	EXPECT_EQ(testList.IsEmpty(), true);
}

#pragma endregion ListTests

#pragma region FListTests
// ================================================
// ==============   FLIST TESTS   =================
// ================================================

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
	EXPECT_EQ(testList.GetSize(), 0);
	EXPECT_EQ(testList.IsEmpty(), true);

	testList = { 1, 2, 3 };
	EXPECT_EQ(testList.GetSize(), 3);
	EXPECT_EQ(testList.IsEmpty(), false);

	testList.push_front(0);

	EXPECT_EQ(testList.front(), 0);
	EXPECT_EQ(testList.GetSize(), 4);
}

// Here we test InsertAt and RemoveAt methods
TEST(FListTest, InsertAndRemoveAt)
{
	// InsertAt block
	FList<int> testList = { 1, 2, 3 };

	testList.InsertAt(0, 0);
	EXPECT_EQ(testList.front(), 0);

	// We still need to implement the find algorithm for this case
	testList.InsertAt(4, testList.GetSize());
	//EXPECT_EQ(testList.back(), 4);

	// We still need to implement the find algorithm for this case
	//testList.InsertAt(-5, 2);

	// We test error handling
	EXPECT_THROW(testList.InsertAt(-1, -1), std::exception);
	EXPECT_THROW(testList.InsertAt(12, 12), std::exception);

	// RemoveAt block
	testList.RemoveAt(0);
	EXPECT_EQ(testList.front(), 3);

	// We still need to implement the find algorithm for this case
	testList.RemoveAt(testList.GetSize() - 1);
	//EXPECT_EQ(testList.back(), 3);

	// We still need to implement the find algorithm for this case
	//testList.RemoveAt(2);

	// We test error handling
	EXPECT_THROW(testList.RemoveAt(-1), std::exception);
	EXPECT_THROW(testList.RemoveAt(12), std::exception);
}

TEST(FListTest, PopAndClear)
{
	FList<int> testList = { 1, 2, 3, 4, 5 };

	testList.pop_front();
	EXPECT_EQ(testList.front(), 4);

	testList.Clear();
	EXPECT_EQ(testList.GetSize(), 0);
	EXPECT_EQ(testList.IsEmpty(), true);
}

#pragma endregion FListTests


int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}