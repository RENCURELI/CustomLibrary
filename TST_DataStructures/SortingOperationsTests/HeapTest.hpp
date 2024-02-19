#pragma once

#include <HeapOperations.hpp>

#include <algorithm>
#include <vector>
#include <deque>
#include <string>

#pragma region MakeHeapTests
// ================================================
// ===========   MAKE HEAP TESTS   ================
// ================================================

TEST(MakeHeapTest, DefaultPredicate)
{
	std::vector<int> testVec = { 12, 0, 9, 5, 4, 10 };
	MakeHeap(testVec.begin(), testVec.end());

	EXPECT_TRUE(std::is_heap(testVec.begin(), testVec.end()) == true);

	testVec = { 2 };
	MakeHeap(testVec.begin(), testVec.end());

	EXPECT_TRUE(std::is_heap(testVec.begin(), testVec.end()) == true);
}

#pragma endregion MakeHeapTests

#pragma region PushHeapTests
// ================================================
// ===========   PUSH HEAP TESTS   ================
// ================================================

TEST(PushHeapTest, DefaultPredicate)
{
	std::vector<int> testVec = { 12, 0, 9, 5, 4, 10 };
	std::make_heap(testVec.begin(), testVec.end());

	EXPECT_TRUE(std::is_heap(testVec.begin(), testVec.end()) == true);

	testVec.push_back(11);
	PushHeap(testVec.begin(), testVec.end());

	EXPECT_TRUE(std::is_heap(testVec.begin(), testVec.end()) == true);
	EXPECT_EQ(testVec[2], 11);
}

#pragma endregion PushHeapTests