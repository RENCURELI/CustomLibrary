#include "pch.h"
#include <gtest/gtest.h>

#include <algorithm>
#include <string>

#include "ContainerTests/ArrayTest.hpp"
#include "ContainerTests/FListTest.hpp"
#include "ContainerTests/ListTest.hpp"
#include "ContainerTests/StackTest.hpp"
#include "ContainerTests/PriorityQueueTest.hpp"
#include "ContainerTests/QueueTest.hpp"
#include "ContainerTests/VectorTest.hpp"
#include "ContainerTests/DequeTest.hpp"

#include "NMSequenceOperationsTests/FindTest.hpp"

#include "SortingOperationsTests/SortTest.hpp"
#include "SortingOperationsTests/HeapTest.hpp"

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}