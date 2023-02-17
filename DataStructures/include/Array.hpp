#pragma once
#include <iostream>
#include <cstddef>
#include <stdexcept>

template<typename T, const std::size_t N>
struct Array
{
	T values[N];

	T& operator[](std::size_t index)
	{
		return values[index];
	}

	/*Required Functions
	- front()
	- back()
	- fill()
	*/

	inline T at(int index) const { return values[index]; }
	inline std::size_t size() const { return N; }
	inline bool empty() const { return N == 0; }
};