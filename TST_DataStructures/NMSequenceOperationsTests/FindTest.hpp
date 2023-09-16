#pragma once

#include <NonModifyingSequenceOperations.hpp>

#include <algorithm>
#include <vector>
#include <list>

#pragma region FindTests
// ================================================
// ==============   FIND TESTS   ==================
// ================================================

TEST(FindTest, NonContiguous)
{
	std::list<float> testList = { 0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f };

	EXPECT_TRUE(std::find(testList.begin(), testList.end(), 0.3f) != testList.end());
	EXPECT_TRUE(Find(testList.begin(), testList.end(), 0.3f) != testList.end());

	EXPECT_FALSE(std::find(testList.begin(), testList.end(), 1.0f) != testList.end());
	EXPECT_FALSE(Find(testList.begin(), testList.end(), 1.0) != testList.end());
}

TEST(FindTest, Contiguous)
{
	std::vector<float> testVec= { 0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f };

	EXPECT_TRUE(std::find(testVec.begin(), testVec.end(), 0.3f) != testVec.end());
	EXPECT_TRUE(Find(testVec.begin(), testVec.end(), 0.3f) != testVec.end());

	EXPECT_FALSE(std::find(testVec.begin(), testVec.end(), 1.0f) != testVec.end());
	EXPECT_FALSE(Find(testVec.begin(), testVec.end(), 1.0) != testVec.end());
}

TEST(FindTest, FindIf)
{
	std::vector<int> testVec = { 0, 1, 2, 3, 4, 5 };

	auto is_even = [](int i)
	{
		return i % 2 == 0;
	};

	EXPECT_TRUE(std::find_if(testVec.begin(), testVec.end(), is_even) != testVec.end());
	EXPECT_TRUE(FindIf(testVec.begin(), testVec.end(), is_even) != testVec.end());

	int val = 0;
	auto less_than = [&val](int i)
	{
		return i < val;
	};

	EXPECT_FALSE(std::find_if(testVec.begin(), testVec.end(), less_than) != testVec.end());
	EXPECT_FALSE(FindIf(testVec.begin(), testVec.end(), less_than) != testVec.end());
}

TEST(FindTest, FindIfNot)
{
	std::vector<int> testVec = { 0, 1, 2, 3, 4, 5 };

	auto is_even = [](int i)
	{
		return i % 2 == 0;
	};

	EXPECT_TRUE(std::find_if_not(testVec.begin(), testVec.end(), is_even) != testVec.end());
	EXPECT_TRUE(FindIfNot(testVec.begin(), testVec.end(), is_even) != testVec.end());

	int val = 6;
	auto less_than = [&val](int i)
	{
		return i < val;
	};

	EXPECT_FALSE(std::find_if_not(testVec.begin(), testVec.end(), less_than) != testVec.end());
	EXPECT_FALSE(FindIfNot(testVec.begin(), testVec.end(), less_than) != testVec.end());
}

#pragma endregion FindTests