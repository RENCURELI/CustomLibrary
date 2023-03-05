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

	EXPECT_EQ(firstArray.back(), 10);
	EXPECT_EQ(firstArray.front(), 6);
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

	for (int i = 0; i < testArray.size(); i++)
		EXPECT_EQ(testArray.at(i), 12);
}

#pragma endregion ArrayTests


#pragma region VectorTests
// ================================================
// ==============   VECTOR TESTS   =================
// ================================================


#pragma endregion VectorTests

#pragma region ListTests
// ================================================
// ==============   LIST TESTS   =================
// ================================================


#pragma endregion ListTests

#pragma region FListTests
// ================================================
// ==============   FLIST TESTS   =================
// ================================================


#pragma endregion FListTests


int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}