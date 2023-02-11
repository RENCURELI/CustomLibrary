#pragma once
#include <iostream>
#include <initializer_list>
#include <stdexcept>

// Contiguous static array similar to C style arrays
template<typename T, int N>
class Array
{
public:
	Array() {}
	Array(std::initializer_list<T> l)
	{
		// Must handle case where too much data is passed
		for (const auto& it : l)
		{
			// Add to array
		}
	}

	~Array() {}

	/*Required Functions
	- at()
	- front()
	- back()
	- empty()
	- size()
	- fill()
	- clear() -> maybe
	*/


private:
};