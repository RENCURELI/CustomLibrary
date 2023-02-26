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

	inline T at(const int index) const 
	{
		if (index >= N || index < 0)
			throw std::runtime_error("[ERROR] Index out of bounds");

		return values[index];
	}

	inline std::size_t size() const { return N; }
	inline bool empty() const { return N == 0; }
	inline T* front() const { return values[0]; }
	inline T* back() const { return values[N - 1]; }

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
		
		for (int i = 0; i < size(); i++)
		{
			T temp = other[i];
			other[i] = values[i];
			values[i] = temp;
		}
	}
};