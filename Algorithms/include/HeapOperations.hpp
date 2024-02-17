// For all Heap Operations -> https://en.cppreference.com/w/cpp/algorithm#Heap_operations

// References
//https://github.com/llvm/llvm-project/blob/main/libcxx/include/__algorithm/make_heap.h
//https://github.com/llvm/llvm-project/blob/main/libcxx/include/__algorithm/sift_down.h

#pragma once

#include <algorithm>
#include <iterator>

template<std::random_access_iterator RandomIt, class Compare>
constexpr void SiftDown(RandomIt first, Compare comp, typename std::_Iter_diff_t<RandomIt> len, RandomIt start)
{
	using value_type = std::_Iter_value_t<RandomIt>;

	std::ptrdiff_t child = start - first; // last parent before leaf nodes
	// Early return if we only have one element or if first possible parent is lower than value
	// ( this second part sounds weird, will require test cases to determine if it can be removed )
	if (len < 2 || (len >> 1) - 1 < child)
	{
		return;
	}

	child = 2 * child + 1; // We get the possible left child
	RandomIt childIt = first + child; // we get the iterator to the child element

	if ((child + 1) < len && comp(*childIt, *(childIt + 1)))
	{
		// Right child exists and is greater than left child
		++childIt;
		++child;
	}

	if (comp(*childIt, *start))
	{
		// We are already in heap order
		return;
	}

	value_type top(std::move(*start)); // We construct a temp to store the value of "start"
	do
	{
		// Not in heap order, swap parent with largest child
		*start = std::move(*childIt);
		start = childIt;

		if ((len >> 1) - 1 < child)
		{
			break;
		}

		// Recompute child from updated parent
		child = 2 * child + 1;
		childIt = first + child;

		// We compare left and right child again
		if ((child + 1) < len && comp(*childIt, *(childIt + 1)))
		{
			++childIt;
			++child;
		}

	// Check heap ordering
	} while (!comp(*childIt, top));
	*start = std::move(top); // Move the temp value back into the "start" iterator ( which has moved to the proper position
}

template<std::random_access_iterator RandomIt, class Compare>
constexpr void MakeHeap(RandomIt first, RandomIt last, Compare comp)
{
	std::ptrdiff_t bottom = last - first;
	// Start from "lowest" parent and go "up" towards first parent
	for (std::ptrdiff_t hole = bottom >> 1; hole > 0;) // Divide by two ( shift for better assembly )
	{
		--hole;
		SiftDown(first, comp, bottom, first + hole);
	}
}

template<std::random_access_iterator RandomIt>
constexpr void MakeHeap(RandomIt first, RandomIt last)
{
	MakeHeap(first, last, std::less<>{});
}