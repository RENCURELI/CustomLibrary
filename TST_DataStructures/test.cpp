#include "pch.h"
#include <gtest/gtest.h>

#include <algorithm>
#include <string>

#include "ContainerTests/ArrayTest.hpp"
#include "ContainerTests/FListTest.hpp"
#include "ContainerTests/ListTest.hpp"
#include "ContainerTests/StackTest.hpp"
#include "ContainerTests/VectorTest.hpp"
#include "ContainerTests/DequeTest.hpp"

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}