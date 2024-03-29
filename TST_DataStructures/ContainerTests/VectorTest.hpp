#pragma once

#include <algorithm>
#include <string>

#include "Vector.hpp"

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

	Vector<int> moveConstructor = Vector<int>(std::move(Vector<int>({ 1, 2, 3 })));
	EXPECT_EQ(moveConstructor.size(), 3);
	EXPECT_EQ(moveConstructor.capacity(), 3);
	EXPECT_EQ(moveConstructor.front(), 1);
	EXPECT_EQ(moveConstructor.back(), 3);

	Vector<int> iteratorConstructor = Vector<int>(moveConstructor.begin(), moveConstructor.end());
	EXPECT_EQ(moveConstructor.size(), 3);
	EXPECT_EQ(moveConstructor.capacity(), 3);
	EXPECT_EQ(moveConstructor.front(), 1);
	EXPECT_EQ(moveConstructor.back(), 3);
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

	std::sort(testVec.begin(), testVec.end());
	EXPECT_TRUE(std::is_sorted(testVec.begin(), testVec.end()) == true);

	auto it = std::find(testVec.begin(), testVec.end(), 2);
	EXPECT_TRUE(it == testVec.begin() + 1);
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

	testVec.shrink_to_fit();
	EXPECT_EQ(testVec.back(), 5);
	EXPECT_EQ(testVec.size(), 5);
	EXPECT_EQ(testVec.capacity(), 5);
}

TEST(VectorTest, PushBack)
{
	Vector<int> testVec = { 1, 2, 3, 4, 5 };

	testVec.push_back(6);
	EXPECT_EQ(testVec.size(), 6);
	EXPECT_TRUE(std::find(testVec.begin(), testVec.end(), 6) != testVec.end());
	EXPECT_EQ(testVec.capacity(), 10);

	// Push_back move
	testVec.push_back(std::move(15));
	EXPECT_EQ(testVec.size(), 7);
	EXPECT_TRUE(std::find(testVec.begin(), testVec.end(), 15) != testVec.end());
	EXPECT_EQ(testVec.capacity(), 10);
}

TEST(VectorTest, Insertion)
{
	Vector<int> testVec = { 1, 2, 3, 4, 5 };

	auto it = testVec.cbegin();
	testVec.insert(std::next(it, 3), 12);
	EXPECT_EQ(testVec.size(), 6);
	EXPECT_EQ(testVec.capacity(), 10);
	EXPECT_EQ(testVec[3], 12);
	EXPECT_THROW(testVec.insert(testVec.end() + testVec.capacity(), 51), std::out_of_range);

	it = testVec.cbegin();
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
	EXPECT_EQ(testVec.size(), 14);
	EXPECT_EQ(testVec.capacity(), 14);

	Vector<int> secondVec = { 10, 20, 30, 40, 50 };
	returnedIt = testVec.insert(testVec.begin() + 5, secondVec.begin() + 1, secondVec.end() - 1);
	EXPECT_TRUE(returnedIt == (testVec.begin() + 5));
	EXPECT_EQ(*(testVec.begin() + 5), 20);
	EXPECT_EQ(*(testVec.begin() + 7), 40);
	EXPECT_EQ(*(testVec.begin() + 8), 1);
	EXPECT_EQ(testVec.size(), 17);
	EXPECT_EQ(testVec.capacity(), 34);

	returnedIt = testVec.insert(testVec.begin(), secondVec.begin(), secondVec.begin());
	EXPECT_TRUE(returnedIt == testVec.begin());
	EXPECT_EQ(*testVec.begin(), 100);
	EXPECT_EQ(testVec.size(), 17);
	EXPECT_EQ(testVec.capacity(), 34);

	returnedIt = testVec.insert(testVec.begin(), { 0, 1, 2, 3 });
	EXPECT_TRUE(returnedIt == testVec.begin());
	EXPECT_EQ(*testVec.begin(), 0);
	EXPECT_EQ(testVec.size(), 21);
	EXPECT_EQ(testVec.capacity(), 34);
}

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
	{
		testVec.pop_back();
	}
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

	testVec.clear();
	newVec.clear();

	// If this test ever fails, it crashes ( but I'd rather crash here than in another test )
	for (int i = 0; i < 1000; ++i)
	{
		newVec.push_back(i);
	}
	testVec = newVec;

	testVec = std::move(Vector<int>(10, 1));
	EXPECT_EQ(testVec.size(), 10);
	EXPECT_EQ(testVec.capacity(), 10);
	EXPECT_EQ(testVec.front(), 1);
	EXPECT_EQ(testVec.back(), 1);
}

TEST(VectorTest, Comparison)
{
	Vector<int> firstVector{1, 2, 3, 4, 5};
	Vector<int> equalVector{1, 2, 3, 4, 5};

	EXPECT_TRUE(firstVector == equalVector);

	Vector<int> diffVector{1, 2, -3, 4, 5};
	EXPECT_FALSE(firstVector == diffVector);

	EXPECT_EQ(firstVector <=> equalVector, std::strong_ordering::equal);
	EXPECT_EQ(firstVector <=> diffVector, std::strong_ordering::greater);
}

#pragma endregion VectorTests
