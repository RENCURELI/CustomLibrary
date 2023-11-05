// For all Sorting Operations -> https://en.cppreference.com/w/cpp/algorithm#Sorting_operations

#pragma once

#include <algorithm>
#include <iterator>

// ======================================
// ==============   SORT   ==============
// ======================================

// This is currently the implementation of sort_heap -> form the Heap Operations -> https://en.cppreference.com/w/cpp/algorithm#Heap_operations
// Standard sort uses Introsort -> https://en.wikipedia.org/wiki/Introsort  ( TODO : Update Sort to use Introsort once HeapSort method is implemented )
template<std::random_access_iterator RandomIt, class Compare>
void Sort(RandomIt first, RandomIt last, Compare comp)
{
	std::make_heap(first, last, comp);

	for (; first != last; --last)
	{
		std::pop_heap(first, last, comp);
	}
}

template<std::random_access_iterator RandomIt>
void Sort(RandomIt first, RandomIt last)
{
	Sort(first, last, std::less<>{});
}

// ======================================
// ==========   STABLE SORT   ===========
// ======================================


// ======================================
// ========   IS SORTED UNTIL   =========
// ======================================

template<std::forward_iterator ForwardIt, class Compare>
constexpr ForwardIt IsSortedUntil(ForwardIt first, ForwardIt last, Compare comp)
{
	if (first != last)
	{
		ForwardIt next = first;

		// We increment and check we haven't yet reached the end of the collection
		while (++next != last)
		{
			// EXEAMPLE using std::less -> if next < first, values are not sorted in non-descending order
			if (comp(*next, *first))
			{
				return next;
			}
			first = next;
		}
	}
	return last;
}

template<std::forward_iterator ForwardIt>
constexpr ForwardIt IsSortedUntil(ForwardIt first, ForwardIt last)
{
	return IsSortedUntil(first, last, std::less<>{});
}

// ======================================
// ===========   IS SORTED   ============
// ======================================

template<std::forward_iterator ForwardIt, class Compare>
constexpr bool IsSorted(ForwardIt first, ForwardIt last, Compare comp)
{
	return IsSortedUntil(first, last, comp) == last;
}

template<std::forward_iterator ForwardIt>
constexpr bool IsSorted(ForwardIt first, ForwardIt last)
{
	return IsSorted(first, last, std::less<>{});
}