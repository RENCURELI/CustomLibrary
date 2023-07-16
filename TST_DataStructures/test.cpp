#include "pch.h"
#include <gtest/gtest.h>

#include <algorithm>
#include <string>

#include "ArrayTest.hpp"
#include "FListTest.hpp"
#include "ListTest.hpp"
#include "StackTest.hpp"
#include "VectorTest.hpp"
#include "DequeTest.hpp"

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}