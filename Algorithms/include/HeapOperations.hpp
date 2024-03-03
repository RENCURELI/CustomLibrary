// For all Heap Operations -> https://en.cppreference.com/w/cpp/algorithm#Heap_operations

// References
//https://github.com/llvm/llvm-project/blob/main/libcxx/include/__algorithm/make_heap.h
//https://github.com/llvm/llvm-project/blob/main/libcxx/include/__algorithm/sift_down.h

#pragma once

#include <algorithm>
#include <iterator>

template<std::random_access_iterator RandomIt, class Compare>
constexpr void SiftUp(RandomIt first, RandomIt last, Compare comp, typename std::_Iter_diff_t<RandomIt> len)
{
	using value_type = std::_Iter_value_t<RandomIt>;
	// 1 element or less, nothing to do
	if (len > 1)
	{
		len = (len - 2) >> 1; // -2 because len is based on iterator Last, which is one step behind element to insert
		RandomIt ptr = first + len; // get temp parent of newly inserted value ( fake it as being part of the heap )

		// Should newly inserted value replace its parent?
		if (comp(*ptr, *(--last)))
		{
			value_type temp(std::move(*last));
			do
			{
				// Do while with break to avoid duplicating the next 2 lines
				*last = std::move(*ptr);
				last = ptr;
				if (len == 0)
				{
					break;
				}

				len = (len - 1) >> 1;
				ptr = first + len;
			} while (comp(*ptr, temp));
			*last = std::move(temp);
		}
	}
}

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
[[nodiscard]] RandomIt FloydSiftDown(RandomIt first, Compare comp, typename std::_Iter_diff_t<RandomIt> len)
{
	using difference_type = typename std::_Iter_diff_t<RandomIt>;

	RandomIt hole = first;
	RandomIt childIt = first;
	difference_type child = 0;

	// We will loop until we return a value -> Hole moved down to becoming a leaf node
	while (true)
	{
		childIt += child + 1; // Get left child of current index
		child = 2 * child + 1;

		if ((child + 1) < len && comp(*childIt, *(childIt + 1)))
		{
			++childIt;
			++child;
		}

		*hole = std::move(*childIt); // Put the value of Child It in the current address of Hole
		hole = childIt; // Move hole down

		if (child > (len >> 1) - 1)
		{
			return hole;
		}
	}
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


template<std::random_access_iterator RandomIt, class Compare>
constexpr void PushHeap(RandomIt first, RandomIt last, Compare comp)
{
	typename std::_Iter_diff_t<RandomIt> len = last - first;
	SiftUp(first, last, comp, len);
}

template<std::random_access_iterator RandomIt>
constexpr void PushHeap(RandomIt first, RandomIt last)
{
	PushHeap(first, last, std::less<>{});
}

template<std::random_access_iterator RandomIt, class Compare>
constexpr void PopHeap(RandomIt first, RandomIt last, Compare comp)
{
	typename std::_Iter_diff_t<RandomIt> len = last - first;
	using value_type = typename std::_Iter_value_t<RandomIt>;
	// A length of 1 or less is basically no operation
	if (len > 1)
	{
		value_type top(std::move(*first));
		RandomIt hole = FloydSiftDown(first, comp, len);
		--last; // subtract 1 from last as last is "outside" of the range we work on

		if (hole == last)
		{
			*hole = std::move(top); // heap property is maintained through the sift down process
		}
		// In case, after floyd sift down, hole is not right most leaf
		else
		{
			*hole = std::move(*last); // Put value from last where hole points to
			++hole; // increment hole to be at index of last
			*last = std::move(top); // move top to where last points to ( last was not moved )
			SiftUp(first, hole, comp, hole - first); // Sift up in the range (first, hole] -> hole is excluded to ensure we maintain heap property
		}
	}
}

template<std::random_access_iterator RandomIt>
constexpr void PopHeap(RandomIt first, RandomIt last)
{
	PopHeap(first, last, std::less<>{});
}