#pragma once

#include <Span.hpp>

#include <array>
#include <span>
#include <vector>

#pragma region SpanConstructorTests
// ================================================
// ===========   CONSTRUCTOR TESTS   ==============
// ================================================

TEST(SpanTest, Constructor)
{
	int myArray[]{10, 20, 30, 40, 50};
	Span<int, 5> testSpan(myArray);
	EXPECT_EQ(testSpan.data(), std::to_address(myArray));

	std::vector<int> vec = { 1, 2, 3, 4, 5 };
	Span<int, 5> vecSpan(vec.begin(), 5);
	EXPECT_EQ(vecSpan.data(), vec.data());
	//Span<int, 5> vecSpanFailAssert(vec.begin(), 4); -> Will need to either test for assert, or make static_assert work

	std::array<int, 5> tstArray{ 1, 2, 3, 4, 5 };
	Span<int, 5> arraySpan(tstArray);
	EXPECT_EQ(arraySpan.data(), tstArray.data());

	// Copy constructor
	Span<int, 5> spanConstructed(arraySpan);
	EXPECT_EQ(spanConstructed.data(), arraySpan.data());

	// Copy assign
	spanConstructed = testSpan; // Should be shallow copy
	EXPECT_EQ(spanConstructed.data(), testSpan.data());
}

TEST(SpanTest, Iterators)
{
	std::array<int, 7> tstArray{ 10, 15, 12, 54, 36, -15, 99 };
	Span<int, 7> testSpan(tstArray);

	auto spanIt = std::find(testSpan.begin(), testSpan.end(), -15);
	auto arrayIt = std::find(tstArray.begin(), tstArray.end(), -15);
	EXPECT_EQ(std::to_address(spanIt), std::to_address(arrayIt));
}

TEST(SpanTest, Accessors)
{
	std::array<int, 7> tstArray{ 10, 15, 12, 54, 36, -15, 99 };
	Span<int, 7> testSpan(tstArray);

	EXPECT_EQ(testSpan.size(), 7);
	EXPECT_EQ(testSpan.size_bytes(), 28);
	EXPECT_EQ(testSpan.back(), 99);
	EXPECT_EQ(testSpan.front(), 10);
	EXPECT_EQ(testSpan[2], 12);
}

#pragma endregion SpanConstructorTests