// For all Heap Operations -> https://en.cppreference.com/w/cpp/algorithm#Heap_operations

#pragma once

#include <algorithm>
#include <iterator>

template<std::random_access_iterator RandomIt, class Compare>
constexpr void MakeHeap(RandomIt first, RandomIt last, Compare comp)
{
	std::ptrdiff_t bottom = last - first;
	for (std::ptrdiff_t hole = bottom >> 1; hole > 0;)
	{
		--hole;
		std::_Iter_value_t<RandomIt> val = std::move(*(first + hole));
	}
}

template<std::random_access_iterator RandomIt>
constexpr void MakeHeap(RandomIt first, RandomIt last)
{
	MakeHeap(first, last, std::less<>{});
}