#pragma once

#include <iostream>
#include <initializer_list>
#include <cstddef>
#include <stdexcept>
#include <format>

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
		m_Size = m_Capacity;
	}

	Vector(std::initializer_list<T> l)
	{
		m_Capacity = (unsigned int)l.size();
		m_Size = 0; // Size will grow as we add elements
		m_Buffer = new T[m_Capacity];
		
		for (const auto& it : l)
		{
			push_back(it);
		}
	}

	Vector(const Vector& other)
	{
		m_Capacity = other.getCapacity();
		//m_Size = 0; // Size will grow as we add elements
		m_Size = m_Capacity;
		m_Buffer = new T[m_Capacity];

		for (int i = 0; i < other.m_Size; i++)
		{
			m_Buffer[i] = other.at(i);
			//push_back(other.at(i));
		}
	}

	Vector(const int count, T data)
	{
		m_Capacity = count; // We reserve for the amount of data to store
		//m_Size = 0; // Size will grow as we add elements
		m_Size = m_Capacity;
		m_Buffer = new T[count];

		// We insert the specified data in vector
		for (int i = 0; i < count; i++)
		{
			//push_back(data);
			m_Buffer[i] = data;
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
	
	void pop_back()
	{
		delete back();
		m_Size--;
	}

	// In the STL, this should return an iterator, not sure why I would need to
	void insert(int pos, const T& data)
	{
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
			int i = m_Size;
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

	T& at(int index)
	{
		return m_Buffer[index];
	}

	const T& at(int index) const
	{
		return m_Buffer[index];
	}

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

	void erase(unsigned int first, unsigned int last)
	{
		// Error handling
		if (first < 0 || last > m_Size)
		{
			std::string errorMessage = std::string();
			errorMessage.append("[ERROR] Index out of bound, first = " + std::to_string(first));
			errorMessage.append(" last = " + std::to_string(last));
			errorMessage.append(" first must be greater than 0 and last smaller than size, size = " + std::to_string(m_Size));
			throw std::runtime_error(errorMessage);
		}

		if (first > last)
			throw std::runtime_error("[ERROR] First is greater than Last -> infinite loop");

		unsigned int i = first;
		do
		{
			m_Buffer[i].~T();
			++i;
		} while (i < last);
	}

	inline const T& front() const { return this->m_Buffer; }
	inline T& front() { return this->m_Buffer; }
	inline const T& back() const { return this + sizeof(T) * m_Size; }
	inline T& back() { return this + sizeof(T) * m_Size; }
	inline int getSize() const { return m_Size; }
	inline int getCapacity() const { return m_Capacity; }

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

		// We copy the data over from other to this
		for (int i = 0; i < other.m_Size; i++)
		{
			push_back(other.at(i));
		}
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
	}

	T& operator[](int pos)
	{
		return m_Buffer[pos];
	}

	const T& operator[] (int pos) const
	{
		return m_Buffer[pos];
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