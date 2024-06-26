#pragma once

#include <algorithm>
#include <string>

#include "Array.hpp"

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

#pragma warning(push) // Suppress warning convert from int to size_t signed to unsigned conversion
#pragma warning(disable : 4245)
	// Test for negative index
	EXPECT_THROW(testArray.at(-1), std::out_of_range);
#pragma warning(pop)

	// Test for negative overflowing index
	EXPECT_THROW(testArray.at(testArray.size()), std::out_of_range);

	EXPECT_TRUE(std::is_sorted(testArray.begin(), testArray.end()) == true);
}

TEST(ArrayTest, ArraySize)
{
#pragma warning(push) // Suppress warning zero-sized array in stack object will have no elements
#pragma warning(disable : 4815)
	Array<int, 0> emptyArray;
#pragma warning(pop)

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
	{
		EXPECT_EQ(testArray.at(i), 12);
	}
}

TEST(ArrayTest, Assignment)
{
	Array<int, 5> testArray{ 1, 2, 3, 4, 5 };
	Array<int, 5> otherArray{ 0, 0, 0, 0, 0 };

	EXPECT_FALSE(std::find(testArray.begin(), testArray.end(), 0) != testArray.end());
	EXPECT_TRUE(std::find(testArray.begin(), testArray.end(), 5) != testArray.end());

	testArray = otherArray;
	EXPECT_TRUE(std::find(testArray.begin(), testArray.end(), 0) != testArray.end());
	EXPECT_FALSE(std::find(testArray.begin(), testArray.end(), 5) != testArray.end());
}

TEST(ArrayTest, Comparison)
{
	Array<int, 5> firstArray{1, 2, 3, 4, 5};
	Array<int, 5> equalArray{1, 2, 3, 4, 5};

	EXPECT_TRUE(firstArray == equalArray);

	Array<int, 5> diffArray{1, 2, -3, 4, 5};
	EXPECT_FALSE(firstArray == diffArray);

	EXPECT_EQ(firstArray <=> equalArray, std::strong_ordering::equal);
	EXPECT_EQ(firstArray <=> diffArray, std::strong_ordering::greater);
}

#pragma endregion ArrayTests