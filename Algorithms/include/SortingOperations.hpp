// For all Sorting Operations -> https://en.cppreference.com/w/cpp/algorithm#Sorting_operations

#pragma once

#include <algorithm>
#include <iterator>

// ======================================
// ==============   SORT   ==============
// ======================================

// Used when running async find on contiguous iterator containers
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