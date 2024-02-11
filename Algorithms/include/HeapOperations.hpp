// For all Heap Operations -> https://en.cppreference.com/w/cpp/algorithm#Heap_operations

// References
//https://github.com/llvm/llvm-project/blob/main/libcxx/include/__algorithm/make_heap.h
//https://github.com/llvm/llvm-project/blob/main/libcxx/include/__algorithm/sift_down.h

#pragma once

#include <algorithm>
#include <iterator>

template<std::random_access_iterator RandomIt, class Compare>
constexpr void MakeHeap(RandomIt first, RandomIt last, Compare comp)
{
	std::ptrdiff_t bottom = last - first;
	// Start from "lowest" parent and go "up" towards first parent
	for (std::ptrdiff_t hole = bottom >> 1; hole > 0;) // Divide by two ( shift for better assembly )
	{
		--hole;
		std::_Iter_value_t<RandomIt> val = std::move(*(first + hole));
		//SiftDown();
	}
}

template<std::random_access_iterator RandomIt>
constexpr void MakeHeap(RandomIt first, RandomIt last)
{
	MakeHeap(first, last, std::less<>{});
}