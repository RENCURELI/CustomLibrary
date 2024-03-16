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
	int myArray[]{1, 2, 3, 4, 5};
	Span<int, 5> testSpan(myArray);

	std::vector<int> vec = { 1, 2, 3, 4, 5 };
	Span<int, 5> vecSpan(vec.begin(), 5);
	//Span<int, 5> vecSpanFailAssert(vec.begin(), 4); -> Will need to either test for assert, or make static_assert work

	std::array<int, 5> tstArray{ 1, 2, 3, 4, 5 };
	Span<int, 5> arraySpan(tstArray);
}

#pragma endregion SpanConstructorTests