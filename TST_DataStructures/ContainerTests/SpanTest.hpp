#pragma once

#include <Span.hpp>

#include <array>
#include <span>

#pragma region SpanConstructorTests
// ================================================
// ===========   CONSTRUCTOR TESTS   ==============
// ================================================

TEST(SpanTest, Constructor)
{
	int myArray[]{1, 2, 3, 4, 5};
	Span<int, 5> testSpan(myArray);
	//std::span<int> testSpan(myArray);
}

#pragma endregion SpanConstructorTests