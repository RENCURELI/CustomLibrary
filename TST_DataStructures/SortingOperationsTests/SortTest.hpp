#pragma once

#include <SortingOperations.hpp>

#include <algorithm>
#include <vector>
#include <deque>

#pragma region SortTests
// ================================================
// ==============   SORT TESTS   ==================
// ================================================

TEST(SortTest, DefaultPredicate)
{
	std::vector<int> testVec = { 12, 0, 9, 5, 4, 10 };
	std::vector<int> otherVec = { 12, 0, 9, 5, 4, 10 };

	EXPECT_EQ(testVec.front(), 12);
	EXPECT_EQ(testVec.back(), 10);

	EXPECT_EQ(otherVec.front(), 12);
	EXPECT_EQ(otherVec.back(), 10);

	Sort(testVec.begin(), testVec.end());

	EXPECT_EQ(testVec.front(), 0);
	EXPECT_EQ(testVec.back(), 12);

	std::sort(otherVec.begin(), otherVec.end());

	EXPECT_EQ(otherVec.front(), 0);
	EXPECT_EQ(otherVec.back(), 12);
}

TEST(SortTest, CustomPredicate)
{
	std::vector<int> testVec = { 12, 0, 9, 5, 4, 10 };
	std::vector<int> otherVec = { 12, 0, 9, 5, 4, 10 };

	EXPECT_EQ(testVec.front(), 12);
	EXPECT_EQ(testVec.back(), 10);

	EXPECT_EQ(otherVec.front(), 12);
	EXPECT_EQ(otherVec.back(), 10);

	Sort(testVec.begin(), testVec.end(), std::greater<>{});

	EXPECT_EQ(testVec.front(), 12);
	EXPECT_EQ(testVec.back(), 0);

	std::sort(otherVec.begin(), otherVec.end(), std::greater<>{});

	EXPECT_EQ(otherVec.front(), 12);
	EXPECT_EQ(otherVec.back(), 0);
}

#pragma endregion SortTests