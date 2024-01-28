// For all Sorting Operations -> https://en.cppreference.com/w/cpp/algorithm#Sorting_operations

#pragma once

#include <algorithm>
#include <iterator>

//export module sorting_operations;

//export import <algorithm>
//export import <iterator>

inline constexpr int ISORT_MAX{ 32 }; // Max size for Insertion Sort

template<std::bidirectional_iterator BidIt, class Compare>
constexpr BidIt InsertionSort(const BidIt first, const BidIt last, Compare comp)
{
	if (first != last)
	{
		// Cycle over the collection
		for (BidIt mid = first; ++mid != last;)
		{
			BidIt hole = mid; // We copy mid for the inner loop
			typename BidIt::value_type val = *mid; // Save a copy of the value currently evaluated

			// This ensures we don't move backwards to an iterator < first -> which we can't check in BidIt -> no implementation of <=>
			if (comp(*mid, *first))
			{
				// Move backward -> push values to the right
				std::move_backward(first, mid, ++hole); // ++hole is valid as std::move_backwards moves [first, last)
				*first = std::move(val); // Replace the value of first with the evaluated value
			}
			else
			{
				// Go backwards from the evaluated entry to the beginning, until comp evaluates to false
				for (BidIt prev = hole; comp(val, *--prev); hole = prev) // Hole takes prev -> Move iterator down by one
				{
					*hole = std::move(*prev); // We move / copy the value pointed to by prev into hole
				}

				*hole = std::move(val); // We move the evaluated value to the position pointed to by hole
			}
		}
	}

	return last;
}


// ======================================
// ==============   SORT   ==============
// ======================================

// This is currently the implementation of sort_heap -> form the Heap Operations -> https://en.cppreference.com/w/cpp/algorithm#Heap_operations
// Standard sort uses Introsort -> https://en.wikipedia.org/wiki/Introsort  ( TODO : Update Sort to use Introsort once HeapSort method is implemented )
template<std::random_access_iterator RandomIt, class Compare>
void Sort(RandomIt first, RandomIt last, Compare comp)
{
	// Small enough to use insertion sort
	if (std::distance(first, last) <= ISORT_MAX)
	{
		InsertionSort(first, last, comp);
		return;
	}

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

// The STL implementation is a Timsort -> https://en.wikipedia.org/wiki/Timsort
// For now, it will be an insertion sort
template<std::random_access_iterator RandomIt, class Compare>
void StableSort(RandomIt first, RandomIt last, Compare comp)
{
	RandomIt oldFirst = first;
	for (; first != last; ++first)
	{
		size_t len = std::distance(oldFirst, first);
		size_t j = 1;
		// first - ( j - 1 ) -> allows us to follow the currently evaluated element down the container until it falls into place
		while (j <= len && comp(*(first - (j - 1)), *(first - j)))
		{
			std::swap(*(first - (j-1)), *(first - j));
			++j;
		}
	}
}

template<std::random_access_iterator RandomIt>
void StableSort(RandomIt first, RandomIt last)
{
	StableSort(first, last, std::less<>{});
}

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

// ======================================
// ==========   NTH ELEMENT   ===========
// ======================================

// Uses IntroSelect -> https://en.wikipedia.org/wiki/Introselect
// First implementation will use median of medians -> https://en.wikipedia.org/wiki/Median_of_medians
template<std::random_access_iterator RandomIt, class Compare>
void NthElement(RandomIt first, RandomIt nth, RandomIt last, Compare comp)
{

}

template<std::random_access_iterator RandomIt>
void NthElement(RandomIt first, RandomIt nth, RandomIt last)
{
	NthElement(first, nth, last, std::less<>{});
}