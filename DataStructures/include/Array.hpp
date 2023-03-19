#pragma once
#include <iostream>
#include <cstddef>
#include <stdexcept>

template<typename T, const unsigned int N>
struct Array
{
	T values[N];

	T& operator[](unsigned int index)
	{
		return values[index];
	}

	inline T at(const int index) const 
	{
		if (index >= N || index < 0)
			throw std::runtime_error("[ERROR] Index out of bounds");

		return values[index];
	}

	inline unsigned int size() const { return N; }
	inline bool empty() const { return N == 0; }
	inline const T& front() const { return values[0]; }
	inline T& front() { return values[0]; }
	inline const T& back() const { return values[N - 1]; }
	inline T& back() { return values[N - 1]; }

	constexpr void fill(const T& val)
	{
		for (int i = 0; i < N; i++)
		{
			values[i] = val;
		}
	}

	constexpr void swap(Array& other)
	{
		if (other.size() != size())
			throw std::runtime_error("[ERROR] Trying to swap data through arrays of different sizes, this would cause out of bounds errors");
		
		for (unsigned int i = 0; i < size(); i++)
		{
			T temp = other[i];
			other[i] = values[i];
			values[i] = temp;
		}
	}
};