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
		m_Capacity = (unsigned int)l.size();
		m_Buffer = new T[m_Capacity]; // Reserve some extra memory for future allocations
		
		for (const auto& it : l)
		{
			push_back(it);
		}
	}

	Vector(const Vector& other)
	{

	}

	Vector(const int count, T data)
	{
		m_Capacity = count; // We reserve for the amount of data to store
		m_Buffer = new T[count];

		// We insert the specified data in vector
		for (int i = 0; i < count; i++)
		{
			push_back(data);
		}
	}


	~Vector()
	{
		delete[] m_Buffer;
	}

	// emplace back
	// push_back
	void push_back(const T& value)
	{
		if (m_Size == m_Capacity)
			resize(m_Capacity * 2);
		m_Buffer[m_Size] = value;
		m_Size++;
	}
	
	// pop back
	// insert

	/*constexpr std::iterator insert(int pos, T data)
	{
		buffer[pos] = data;
	}*/

	void assign(int count, T val)
	{
		clear();
		int i = 0;
		do
		{
			m_Buffer[i] = val;
			++i;
		} while (i < count);
		m_Size = count;
	}

	constexpr void clear() noexcept
	{
		std::destroy(m_Buffer, m_Buffer + m_Size);
		m_Size = 0;
	}

	void erase(int pos)
	{
		if (pos > m_Size || pos < 0)
			throw std::runtime_error("[ERROR] Index out of bounds");

		m_Buffer[pos].~T();
	}

	void erase(int first, int last)
	{
		int i = first;
		do
		{
			m_Buffer[i].~T();
			++i;
		} while (i < last);
	}

	inline T* front() const { return this->m_Buffer; }
	inline T* back() const { return this + sizeof(T) * m_Size; }
	inline int getSize() const { return m_Size; }
	inline int getCapacity() const { return m_Capacity; }

	void PrintVector()
	{
		for (unsigned int i = 0; i < m_Size; i++)
		{
			std::cout << " -> " << m_Buffer[i];
		}
	}

	Vector& operator=(const Vector& other)
	{

	}

	Vector& operator=(std::initializer_list<T> l)
	{

	}

	// resize and move data from old position to new
	void resize(unsigned int size)
	{
		if (size > m_Capacity)
		{
			reserve(size * 2);
		}
		else if (size < m_Size)
		{
			// We return as we won't replace previous data
			erase(size - 1, m_Size);
			return;
		}
		
		unsigned int i = 0;

		do
		{
			push_back(T());
			++i;
		} while (i < size);
	}

	void resize(unsigned int size, const T& value)
	{
		if (size > m_Capacity)
		{
			reserve(size * 2);
		}
		else if (size < m_Size)
		{
			// We return as we won't replace previous data
			erase(size - 1, m_Size);
			return;
		}

		unsigned int i = 0;

		do
		{
			push_back(T);
			++i;
		} while (i < size);
	}

	// If size is greater than the current capacity, new storage is allocated, otherwise the function does nothing. -> cppreference
	void reserve(unsigned int size)
	{
		if (size <= m_Capacity)
			return;
		else
		{
			m_Capacity = size;
			T* newBuffer = new T[m_Capacity];

			// We handle the case where we resize to a lower size than current size by discarding overflowing elements
			if (m_Capacity < m_Size)
				m_Size = m_Capacity;

			for (unsigned int i = 0; i < m_Size; i++)
			{
				newBuffer[i] = m_Buffer[i];
			}
			delete[] m_Buffer;
			m_Buffer = newBuffer;
		}
	}

	// Reduces capacity to size
	void shrinkToFit()
	{
		
	}

private:
	unsigned int m_Capacity; // The capacity of the vector
	unsigned int m_Size; // The number of elements stored in vector

	T* m_Buffer; // Pointer to the currently allocated array
};