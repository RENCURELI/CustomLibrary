#pragma once

#include <iostream>
#include <initializer_list>
#include <cstddef>
#include <stdexcept>

// Contiguous dynamic array
template<typename T>
class Vector
{
public:

	// Default constructor creating a 4 item vector
	Vector() 
	{
		m_Buffer = new T[4];
		m_Capacity = 4;
	}

	Vector(std::initializer_list<T> l)
	{
		m_Capacity = l.size() * 2;
		m_Buffer = new T[m_Capacity]; // Reserve some extra memory for future allocations
		
		for (const auto& it : l)
		{
			push_back(it);
		}
	}

	Vector(Vector& other)
	{

	}

	Vector(int count, T data)
	{

	}


	~Vector()
	{
		delete[] buffer;
	}

	// emplace back
	// push_back
	void push_back(const T& value)
	{
		if (m_Size == m_Capacity)
			resize();
		m_Buffer[m_Size] = value;
		m_Size++;
	}
	
	// pop back
	// insert

	/*constexpr std::iterator insert(int pos, T data)
	{
		buffer[pos] = data;
	}*/

	inline T* front() const { return this->m_Buffer; }
	inline T* back() const { return this + sizeof(T) * m_Size; }
	inline int getSize() const { return m_Size; }
	inline int getCapacity() const { return m_Capacity; }

	void PrintVector()
	{
		for (int i = 0; i < m_Size; i++)
		{
			std::cout << " -> " << m_Buffer[i];
		}
	}

	Vector& operator=(const vector& other)
	{

	}

	Vector& operator=(std::initializer_list<T> l)
	{

	}

private:
	int m_Capacity; // The capacity of the vector
	int m_Size; // The number of elements stored in vector

	T* m_Buffer; // Pointer to the currently allocated array

	// resize
	void resize()
	{
		m_Capacity *= 2;
		T* newBuffer = new T[m_Capacity];
		for (int i = 0; i < m_Size; i++)
		{
			newBuffer[i] = m_Buffer[i];
		}
		m_Buffer = newBuffer;
	}
};