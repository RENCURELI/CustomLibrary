#pragma once

#include <iostream>
#include <initializer_list>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <memory>

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
		m_Size = 0;
	}

	Vector(std::initializer_list<T> l)
	{
		m_Capacity = (unsigned int)l.size();
		m_Size = 0; // Size will grow as we add elements
		m_Buffer = new T[m_Capacity];
		
		for (const auto& it : l)
		{
			m_Buffer[m_Size] = it;
			++m_Size;
		}
	}

	Vector(const Vector& other)
	{
		m_Capacity = other.size(); // We "shrink to fit" the size

		// Realign capacity to a multiple of 2 for now, would want to realign on proper 4 * 2 ^ n capacity later
		if (m_Capacity % 2 != 0)
			m_Capacity++;

		m_Size = m_Capacity;
		m_Buffer = new T[m_Capacity];

		memset(m_Buffer, 0, sizeof(T) * m_Capacity);
		memcpy_s(m_Buffer, sizeof(T) * m_Size, other.m_Buffer, sizeof(T) * other.m_Size);
	}

	Vector(const int count, T data)
	{
		if ( count <= 0 )
			throw std::runtime_error("[ERROR] Trying to create array of invalid size -> must be greater than 0");

		m_Capacity = count; // We reserve for the amount of data to store
		m_Size = m_Capacity;
		m_Buffer = new T[count];

		for (int i = 0; i < count; i++)
		{
			m_Buffer[i] = data;
		}
	}

	~Vector()
	{
		delete[] m_Buffer;
	}

	void push_back(const T& value)
	{
		if (m_Size == m_Capacity)
			resize(m_Capacity * 2);
		m_Buffer[m_Size] = value;
		m_Size++;
	}
	
	void pop_back()
	{
		back().~T();
		m_Size--;
	}

	// In the STL, this should return an iterator, not sure why I would need to
	void insert(unsigned int pos, const T& data)
	{
		if (pos > m_Size + 1)
			throw std::runtime_error("[ERROR] Index out of bounds, you will leave some indices unset -> this might cause issues");

		if (pos == m_Size)
		{
			push_back(data);
		}
		else
		{
			// We resize if needed
			if (m_Size + 1 > m_Capacity)
				resize(m_Capacity * 2);

			// We move the data after pos
			unsigned int i = m_Size;
			do
			{
				m_Buffer[i + 1] = m_Buffer[i];
				--i;
			} while (i > pos);

			// We insert the new data
			m_Buffer[pos] = data;
			m_Size++;
		}
	}

	T& at(unsigned int index)
	{
		if (m_Size <= 0)
			throw std::runtime_error("[ERROR] Trying to access empty container");
		else if (index >= m_Size)
			throw std::out_of_range("[ERROR] Index out of bounds");
		return m_Buffer[index];
	}

	const T& at(unsigned int index) const
	{
		if (m_Size <= 0)
			throw std::runtime_error("[ERROR] Trying to access empty container");
		else if (index > m_Size)
			throw std::out_of_range("[ERROR] Index out of bounds");
		return m_Buffer[index];
	}

	void assign(unsigned int count, T val)
	{
		clear();
		unsigned int i = 0;
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

	void erase(unsigned int pos)
	{
		if (pos >= m_Size)
			throw std::out_of_range("[ERROR] Index out of bounds");

		std::destroy_at(&m_Buffer[pos]);

		// if the position is the same as size, we don't need to move data
		if (pos != m_Size)
		{
			do
			{
				m_Buffer[pos] = m_Buffer[pos + 1];
				++pos;
			} while (pos < m_Size);
		}
		m_Size--;
	}

	void erase(unsigned int first, unsigned int last)
	{
		// Error handling
		if (first > last)
			throw std::runtime_error("[ERROR] First is greater than Last -> infinite loop");
		else if (last > m_Size)
		{
			std::string errorMessage = "[ERROR] Index out of bound, first = " + std::to_string(first)
										+ " last = " + std::to_string(last)
										+ " first must be greater than 0 and last smaller than size, size = " + std::to_string(m_Size);
			throw std::out_of_range(errorMessage);
		}

		if (first == last)
		{
			return; // STL would return iterator for last, here, just return
		}

		// We don't destroy last ( same as STL )
		std::destroy(m_Buffer + first, m_Buffer + last - 1);

		// if last is the last element of the vector we don't move the data
		if (last != m_Size - 1)
		{
			int elemsToMove = m_Size - last;
			for (int i = 0; i < elemsToMove; i++)
			{
				m_Buffer[first + i] = m_Buffer[last + i];
			}
		}

		m_Size -= last - first;
	}

	inline const T& front() const { return m_Size > 0 ? this->m_Buffer[0] : throw std::runtime_error("[ERROR] Trying to access empty container"); }
	inline T& front() { return m_Size > 0 ? this->m_Buffer[0] : throw std::runtime_error("[ERROR] Trying to access empty container"); }
	inline const T& back() const { return m_Size > 0 ? this->m_Buffer[m_Size - 1] : throw std::runtime_error("[ERROR] Trying to access empty container"); }
	inline T& back() { return m_Size > 0 ? this->m_Buffer[m_Size - 1] : throw std::runtime_error("[ERROR] Trying to access empty container"); }
	inline int size() const { return m_Size; }
	inline int capacity() const { return m_Capacity; }
	inline bool empty() const { return m_Size == 0; }

	void PrintVector()
	{
		for (unsigned int i = 0; i < m_Size; i++)
		{
			std::cout << " -> " << m_Buffer[i];
		}
	}

	// Copy assign
	Vector& operator=(const Vector& other)
	{
		if (this == &other)
			return *this;

		memset(m_Buffer, 0, sizeof(T) * m_Capacity);
		memcpy_s(m_Buffer, sizeof(T) * m_Size, other.m_Buffer, sizeof(T) * other.m_Size);

		return *this;
	}

	Vector& operator=(std::initializer_list<T> l)
	{
		// We first clear the vector
		clear();

		// We then assign the new values from the iterator list
		for (const auto& it : l)
		{
			push_back(it);
		}

		return *this;
	}

	T& operator[](int pos)
	{
		return m_Size > 0 ? m_Buffer[pos] : throw std::runtime_error("[ERROR] Trying to access empty container");
	}

	const T& operator[] (int pos) const
	{
		return m_Size > 0 ? m_Buffer[pos] : throw std::runtime_error("[ERROR] Trying to access empty container");
	}

	// resize and move data from old position to new
	void resize(unsigned int size)
	{
		if (size < m_Size)
		{
			// We return as we won't replace previous data
			erase(size, m_Size);
			return;
		}
		
		reserve(size);
	}

	void resize(unsigned int size, const T& value)
	{
		if (size < m_Size)
		{
			// We return as we won't replace previous data
			erase(size, m_Size);
			return;
		}
		
		reserve(size);

		unsigned int i = m_Size; // we append value after the already present elements
		do
		{
			push_back(value);
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
		T* newBuffer = new T[m_Size];
		memcpy_s(newBuffer, sizeof(T) * m_Size, m_Buffer, sizeof(T) * m_Size);

		delete[] m_Buffer;
		m_Buffer = newBuffer;
		m_Capacity = m_Size;
	}

private:
	unsigned int m_Capacity; // The capacity of the vector
	unsigned int m_Size; // The number of elements stored in vector

	T* m_Buffer; // Pointer to the currently allocated array
};