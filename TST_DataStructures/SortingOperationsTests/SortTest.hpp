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

#pragma region IsSortedUntilTests
// ================================================
// =========   IS SORTED UNTIL TESTS   ============
// ================================================

TEST(IsSortedUntilTest, DefaultPredicate)
{
	std::vector<int> firstVec = { 0, 1, 2, 3, 4, 1, 2 }; // Sorted until 4
	std::vector<int> secondVec = { 0, -1, -2, -3, -4 }; // Not sorted using std::less
	std::vector<int> thirdVec = { 0, 1, 2, 3, 4, 5 }; // Sorted until end()

	auto it = IsSortedUntil(firstVec.begin(), firstVec.end());
	EXPECT_EQ(*it, 1);

	it = std::is_sorted_until(firstVec.begin(), firstVec.end());
	EXPECT_EQ(*it, 1);

	it = IsSortedUntil(secondVec.begin(), secondVec.end());
	EXPECT_TRUE(it == std::next(secondVec.begin()));

	it = std::is_sorted_until(secondVec.begin(), secondVec.end());
	EXPECT_TRUE(it == std::next(secondVec.begin()));

	it = IsSortedUntil(thirdVec.begin(), thirdVec.end());
	EXPECT_TRUE(it == thirdVec.end());

	it = std::is_sorted_until(thirdVec.begin(), thirdVec.end());
	EXPECT_TRUE(it == thirdVec.end());
}

TEST(IsSortedUntilTest, CustomPredicatePredicate)
{
	std::vector<int> firstVec = { 4, 3, 2, 1, 0, 1, 5 }; // Sorted until 0
	std::vector<int> secondVec = { 0, 1, 2, 3, 4 }; // Not sorted using std::greater
	std::vector<int> thirdVec = { 5, 4, 3, 2, 1, 0 }; // Sorted until end()

	auto it = IsSortedUntil(firstVec.begin(), firstVec.end(), std::greater<>{});
	EXPECT_EQ(*it, 1);

	it = std::is_sorted_until(firstVec.begin(), firstVec.end(), std::greater<>{});
	EXPECT_EQ(*it, 1);

	it = IsSortedUntil(secondVec.begin(), secondVec.end(), std::greater<>{});
	EXPECT_TRUE(it == std::next(secondVec.begin()));

	it = std::is_sorted_until(secondVec.begin(), secondVec.end(), std::greater<>{});
	EXPECT_TRUE(it == std::next(secondVec.begin()));

	it = IsSortedUntil(thirdVec.begin(), thirdVec.end(), std::greater<>{});
	EXPECT_TRUE(it == thirdVec.end());

	it = std::is_sorted_until(thirdVec.begin(), thirdVec.end(), std::greater<>{});
	EXPECT_TRUE(it == thirdVec.end());
}

#pragma endregion IsSortedUntilTests

#pragma region IsSortedTests
// ================================================
// ============   IS SORTED TESTS   ===============
// ================================================

TEST(IsSortedTest, DefaultPredicate)
{
	std::vector<int> firstVec = { 0, 1, 2, 3, 4, 1, 2 }; // Sorted until 4
	std::vector<int> secondVec = { 0, -1, -2, -3, -4 }; // Not sorted using std::less
	std::vector<int> thirdVec = { 0, 1, 2, 3, 4, 5 }; // Sorted until end()

	EXPECT_FALSE(IsSorted(firstVec.begin(), firstVec.end()) == true);
	EXPECT_FALSE(std::is_sorted(firstVec.begin(), firstVec.end()) == true);

	EXPECT_FALSE(IsSorted(secondVec.begin(), secondVec.end()) == true);
	EXPECT_FALSE(std::is_sorted(secondVec.begin(), secondVec.end()) == true);

	EXPECT_TRUE(IsSorted(thirdVec.begin(), thirdVec.end()) == true);
	EXPECT_TRUE(std::is_sorted(thirdVec.begin(), thirdVec.end()) == true);
}

TEST(IsSortedTest, CustomPredicate)
{
	std::vector<int> firstVec = { 4, 3, 2, 1, 0, 1, 5 }; // Sorted until 0
	std::vector<int> secondVec = { 0, 1, 2, 3, 4 }; // Not sorted using std::greater
	std::vector<int> thirdVec = { 5, 4, 3, 2, 1, 0 }; // Sorted until end()

	EXPECT_FALSE(IsSorted(firstVec.begin(), firstVec.end(), std::greater<>{}) == true);
	EXPECT_FALSE(std::is_sorted(firstVec.begin(), firstVec.end(), std::greater<>{}) == true);

	EXPECT_FALSE(IsSorted(secondVec.begin(), secondVec.end(), std::greater<>{}) == true);
	EXPECT_FALSE(std::is_sorted(secondVec.begin(), secondVec.end(), std::greater<>{}) == true);

	EXPECT_TRUE(IsSorted(thirdVec.begin(), thirdVec.end(), std::greater<>{}) == true);
	EXPECT_TRUE(std::is_sorted(thirdVec.begin(), thirdVec.end(), std::greater<>{}) == true);
}

#pragma endregion IsSortedTests