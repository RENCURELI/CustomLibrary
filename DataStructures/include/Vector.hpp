#pragma once

#include <iostream>
#include <initializer_list>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <memory>
#include <iterator>
#include <limits>

#pragma region ConstIterator
template<typename Vector>
class VectorConstIterator
{
public:
	using iterator_concept = std::contiguous_iterator_tag;
	using value_type = typename Vector::value_type;
	using pointer = Vector::const_pointer;
	using reference = const value_type&;
	using difference_type = std::ptrdiff_t;

	using PtrType = typename Vector::pointer;

	VectorConstIterator(PtrType ptr) : m_Ptr(ptr) {}

	// preincrement
	VectorConstIterator& operator++()
	{
		this->m_Ptr++;
		return *this;
	}

	// postincrement
	VectorConstIterator operator++(int)
	{
		VectorConstIterator it(*this);
		++(*this);
		return it;
	}

	// preincrement
	VectorConstIterator& operator--()
	{
		this->m_Ptr--;
		return *this;
	}

	// postincrement
	VectorConstIterator operator--(int)
	{
		VectorConstIterator it(*this);
		--(*this);
		return it;
	}

	VectorConstIterator& operator+=(const difference_type offset)
	{
		this->m_Ptr += offset;
		return *this;
	}

	VectorConstIterator operator+(const difference_type offset)
	{
		VectorConstIterator tmp = this->m_Ptr;
		tmp += offset;
		return tmp;
	}

	VectorConstIterator& operator-=(const difference_type offset)
	{
		this->m_Ptr -= offset;
		return *this;
	}

	VectorConstIterator operator-(const difference_type offset)
	{
		VectorConstIterator tmp = this->m_Ptr;
		tmp -= offset;
		return tmp;
	}

	friend difference_type operator-(const VectorConstIterator& lhs, const VectorConstIterator& rhs)
	{
		return lhs.m_Ptr - rhs.m_Ptr;
	}

	const reference operator*() const { return *m_Ptr; }
	reference operator[](int index) { return *(m_Ptr + index); }
	const pointer operator->() const { return this->m_Ptr; }
	bool operator==(const VectorConstIterator& other) const { return m_Ptr == other.m_Ptr; }
	bool operator!=(const VectorConstIterator& other) const { return !(*this == other); }
	bool operator<(const VectorConstIterator& right) const { return m_Ptr < right.m_Ptr; }
	bool operator>(const VectorConstIterator& right) const { return right < *this; }
	bool operator<=(const VectorConstIterator& right) const { return !(right < *this); }
	bool operator>=(const VectorConstIterator& right) const { return !(*this < right); }

	PtrType m_Ptr;
};

#pragma endregion ConstIterator

#pragma region Iterator
template<typename Vector>
class VectorIterator : public VectorConstIterator<Vector>
{
public:
	using value_type = typename Vector::value_type;
	using pointer = Vector::pointer;
	using reference = value_type&;
	using difference_type = std::ptrdiff_t;
	using BaseIt = VectorConstIterator<Vector>;
public:
	// preincrement
	VectorIterator& operator++()
	{
		BaseIt::operator++();
		return *this;
	}

	// postincrement
	VectorIterator operator++(int)
	{
		VectorIterator it(*this);
		++(*this);
		return it;
	}

	// preincrement
	VectorIterator& operator--()
	{
		BaseIt::operator--();
		return *this;
	}

	// postincrement
	VectorIterator operator--(int)
	{
		VectorIterator it(*this);
		--(*this);
		return it;
	}

	VectorIterator& operator+=(const difference_type offset)
	{
		BaseIt::operator+=(offset);
		return *this;
	}

	VectorIterator operator+(const difference_type offset) const
	{
		VectorIterator tmp = *this;
		tmp += offset;
		return tmp;
	}

	VectorIterator& operator-=(const difference_type offset)
	{
		BaseIt::operator-=(offset);
		return *this;
	}

	VectorIterator operator-(const difference_type offset) const
	{
		VectorIterator tmp = *this;
		tmp -= offset;
		return tmp;
	}

	friend difference_type operator-(const VectorIterator& lhs, const VectorIterator& rhs)
	{
		return lhs.m_Ptr - rhs.m_Ptr;
	}

	reference operator*() const { return const_cast<reference>(BaseIt::operator*()); }
	reference operator[](int index) { return *(this->m_Ptr + index); }
	pointer operator->() const { return this->m_Ptr; }
	bool operator==(const VectorIterator& other) const { return this->m_Ptr == other.m_Ptr; }
	bool operator!=(const VectorIterator& other) const { return !(*this == other); }
	bool operator<(const VectorIterator& right) const { return this->m_Ptr < right.m_Ptr; }
	bool operator>(const VectorIterator& right) const { return right < *this; }
	bool operator<=(const VectorIterator& right) const { return !(right < *this); }
	bool operator>=(const VectorIterator& right) const { return !(*this < right); }
};
#pragma endregion Iterator

// Contiguous dynamic array
template<typename T>
class Vector
{
public:
	using value_type = T;
	using pointer = T*;
	using const_pointer = const T*;
	using iterator = VectorIterator<Vector<T>>;
	using const_iterator = VectorConstIterator<Vector<T>>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
	// size_type would be the unsigned version of the allocator_traits::difference_type ( I currently don't have an allocator or allocator_traits )
	//using size_type = std::make_unsigned<const_iterator::difference_type>; // doesn't seem to work yet
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
		m_Capacity = l.size();
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
		if ((m_Capacity & 0) != 0)
			m_Capacity++;

		m_Size = m_Capacity;
		m_Buffer = new T[m_Capacity];

		memset(m_Buffer, 0, sizeof(T) * m_Capacity);
		memcpy_s(m_Buffer, sizeof(T) * m_Size, other.m_Buffer, sizeof(T) * other.m_Size);
	}

	Vector(size_t count, T data)
	{
		if (count <= 0)
			throw std::runtime_error("[ERROR] Trying to create array of invalid size -> must be greater than 0");

		m_Capacity = count; // We reserve for the amount of data to store
		m_Size = m_Capacity;
		m_Buffer = new T[count];

		for (size_t i = 0; i < count; i++)
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
			reserve(m_Capacity * 2);
		m_Buffer[m_Size] = value;
		m_Size++;
	}
	
	void pop_back()
	{
		if (m_Size == 0)
			return;

		back().~T();
		m_Size--;
	}

	iterator insert(const_iterator pos, const T& data)
	{
		if (pos > cend())
			throw std::out_of_range("[ERROR] Index out of bounds, you will leave some indices unset -> this might cause issues");

		// End points to the block of memory just after the last value
		if (pos == cend())
		{
			push_back(data);
		}
		else
		{
			// We resize if needed
			if (m_Size + 1 > m_Capacity)
				reserve(m_Capacity * 2);

			// We move the data after pos
			const_iterator it = cend();
			do
			{
				*it.m_Ptr = *(it - 1).m_Ptr;
				--it;
			} while (it > pos);

			// We insert the new data
			*pos.m_Ptr = data;
			m_Size++;
		}
		return makeIterator(pos.m_Ptr);
	}

	// would replace size_t with the hypothetical size_type
	iterator insert(const_iterator pos, size_t count, const T& value)
	{
		if (pos > cend())
			throw std::out_of_range("[ERROR] Index out of bounds, you will leave some indices unset -> this might cause issues");

		if (count == 0)
			return makeIterator(pos.m_Ptr);

		if (pos == cend())
		{
			iterator returnIt = end();

			for (int i = 0; i < count; i++)
				push_back(value);

			return returnIt;
		}
		else
		{
			size_t posOffset = pos - begin();
			size_t newSize = m_Size + count;
			if (newSize > m_Capacity)
			{
				reserve(newSize);

				// After reserve, "pos" is invalidated
				pos = begin() + posOffset;
			}

			// We move all data from after the last "to be inserted" position
			const_iterator it = cend();
			do
			{
				*(it + (count - 1)).m_Ptr = *(it - 1).m_Ptr;
				--it;
			} while (it > pos);

			iterator temp = makeIterator(pos.m_Ptr);
			iterator upperBound = makeIterator((temp + count).m_Ptr);
			for (; temp != upperBound; ++temp)
			{
				*temp.m_Ptr = value;
			}

			m_Size = newSize;

			return makeIterator(pos.m_Ptr);
		}
	}

	// inserts [first last)
	iterator insert(const_iterator pos, iterator first, iterator last)
	{
		if (pos > cend())
			throw std::out_of_range("[ERROR] Index out of bounds, you will leave some indices unset -> this might cause issues");

		if (first == last)
			return makeIterator(pos.m_Ptr);

		iterator returnedIt = makeIterator(pos.m_Ptr);
		if (pos == cend())
		{
			for (; first != last; ++first)
				push_back(*first);
		}
		else
		{
			size_t posOffset = pos - begin();
			size_t count = last - first;
			size_t newSize = m_Size + count;
			if (newSize > m_Capacity)
			{
				reserve(newSize * 2);

				// After reserve, "pos" is invalidated
				pos = begin() + posOffset;
			}

			// We move all data from after the last "to be inserted" position
			const_iterator it = cend();
			do
			{
				*(it + (count - 1)).m_Ptr = *(it - 1).m_Ptr;
				--it;
			} while (it > pos);

			iterator temp = makeIterator(pos.m_Ptr);
			for (; first != last; ++first)
			{
				*temp.m_Ptr = *first.m_Ptr;
				++temp;
			}

			m_Size = newSize;

			return makeIterator(pos.m_Ptr);
		}

		return returnedIt;
	}

	iterator insert(const_iterator pos, std::initializer_list<T> ilist)
	{
		if (pos > cend())
			throw std::out_of_range("[ERROR] Index out of bounds, you will leave some indices unset -> this might cause issues");

		if (ilist.size() == 0)
			return makeIterator(pos.m_Ptr);

		iterator returnedIt = makeIterator(pos.m_Ptr);
		if (pos == cend())
		{
			returnedIt = end();

			for (const auto& it : ilist)
				push_back(it);
		}
		else
		{
			size_t posOffset = pos - begin();
			size_t count = ilist.size();
			size_t newSize = m_Size + count;
			if (newSize > m_Capacity)
			{
				reserve(newSize * 2);

				// After reserve, "pos" is invalidated
				pos = begin() + posOffset;
			}

			// We move all data from after the last "to be inserted" position
			const_iterator it = cend();
			do
			{
				*(it + (count - 1)).m_Ptr = *(it - 1).m_Ptr;
				--it;
			} while (it > pos);

			iterator temp = makeIterator(pos.m_Ptr);
			for (const auto& it : ilist)
			{
				*temp.m_Ptr = it;
				++temp;
			}

			m_Size = newSize;

			return makeIterator(pos.m_Ptr);
		}

		return returnedIt;
	}

	T& at(const size_t index)
	{
		if (m_Size <= 0)
			throw std::runtime_error("[ERROR] Trying to access empty container");
		else if (index >= m_Size)
			throw std::out_of_range("[ERROR] Index out of bounds");
		return m_Buffer[index];
	}

	const T& at(const size_t index) const
	{
		if (m_Size <= 0)
			throw std::runtime_error("[ERROR] Trying to access empty container");
		else if (index > m_Size)
			throw std::out_of_range("[ERROR] Index out of bounds");
		return m_Buffer[index];
	}

	void assign(size_t count, T val)
	{
		clear();
		size_t i = 0;
		do
		{
			push_back(val);
			++i;
		} while (i < count);
	}

	constexpr void clear() noexcept
	{
		std::destroy(m_Buffer, m_Buffer + m_Size);
		m_Size = 0;
	}

	iterator erase(iterator pos)
	{
		if (pos > end())
			throw std::out_of_range("[ERROR] Index out of bounds");

		const pointer ptr = pos.m_Ptr;

		std::destroy_at(&pos);

		// if the position is the same as size, we don't need to move data
		if (pos <= end() - 1)
		{
			do
			{
				*pos = std::move(*pos + 1);
				++pos;
			} while (pos < end());
		}
		m_Size--;

		return makeIterator(ptr);
	}

	iterator erase(iterator first, iterator last)
	{
		// Error handling
		if (first > last)
			throw std::runtime_error("[ERROR] First is greater than Last -> infinite loop");
		else if (last > end())
		{
			std::string errorMessage = "[ERROR] Index out of bound, first = " + std::to_string(*first)
										+ " last = " + std::to_string(*last)
										+ " first must be greater than 0 and last smaller than size, size = " + std::to_string(m_Size);
			throw std::out_of_range(errorMessage);
		}

		if (first == last)
		{
			return last;
		}

		const pointer ptr = first.m_Ptr;

		std::destroy(&first, &last);

		// if last is the last element of the vector we don't move the data
		if (last <= end() - 1)
		{
			size_t elemsToMove = end() - last;
			for (int i = 0; i < elemsToMove; i++)
			{
				*(first + i) = std::move(*(last + i));
			}
		}

		m_Size -= last - first;
		return makeIterator(ptr);
	}

	inline const T& front() const { return m_Size > 0 ? this->m_Buffer[0] : throw std::runtime_error("[ERROR] Trying to access empty container"); }
	inline T& front() { return m_Size > 0 ? this->m_Buffer[0] : throw std::runtime_error("[ERROR] Trying to access empty container"); }
	inline const T& back() const { return m_Size > 0 ? this->m_Buffer[m_Size - 1] : throw std::runtime_error("[ERROR] Trying to access empty container"); }
	inline T& back() { return m_Size > 0 ? this->m_Buffer[m_Size - 1] : throw std::runtime_error("[ERROR] Trying to access empty container"); }
	inline size_t size() const { return m_Size; }
	inline size_t max_size() const { return std::numeric_limits<size_t>::max(); }
	inline size_t capacity() const { return m_Capacity; }
	inline bool empty() const { return m_Size == 0; }
	inline iterator begin() { return iterator(m_Buffer); }
	inline const_iterator cbegin() const { return const_iterator(m_Buffer); }
	inline reverse_iterator rbegin() { return reverse_iterator(end()); }
	inline const_reverse_iterator crbegin() const { return const_reverse_iterator(cend()); }
	inline iterator end() { return iterator(m_Buffer + m_Size); }
	inline const_iterator cend() const { return const_iterator(m_Buffer + m_Size); }
	inline reverse_iterator rend() { return reverse_iterator(begin()); }
	inline const_reverse_iterator crend() const { return const_reverse_iterator(cbegin()); }

	void PrintVector()
	{
		for (size_t i = 0; i < m_Size; i++)
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

	T& operator[](size_t pos)
	{
		return m_Size > 0 ? m_Buffer[pos] : throw std::runtime_error("[ERROR] Trying to access empty container");
	}

	const T& operator[](size_t pos) const
	{
		return m_Size > 0 ? m_Buffer[pos] : throw std::runtime_error("[ERROR] Trying to access empty container");
	}

	// resize and move data from old position to new
	void resize(size_t count)
	{
		if (count < m_Size)
		{
			// We return as we won't replace previous data
			erase(begin() + count, end());
			return;
		}
		
		reserve(count);
	}

	void resize(size_t count, const T& value)
	{
		if (count < m_Size)
		{
			// We return as we won't replace previous data
			erase(begin() + count, end());
			return;
		}
		
		reserve(count);

		size_t i = m_Size; // we append value after the already present elements
		do
		{
			push_back(value);
			++i;
		} while (i < count);
	}

	// If size is greater than the current capacity, new storage is allocated, otherwise the function does nothing. -> cppreference
	void reserve(size_t count)
	{
		if (count <= m_Capacity)
			return;
		else
		{
			m_Capacity = count;
			T* newBuffer = new T[m_Capacity];

			// We handle the case where we resize to a lower size than current size by discarding overflowing elements
			if (m_Capacity < m_Size)
				m_Size = m_Capacity;

			for (size_t i = 0; i < m_Size; i++)
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
	iterator makeIterator(const pointer ptr)
	{
		return iterator(ptr);
	}

private:
	size_t m_Capacity; // The capacity of the vector
	size_t m_Size; // The number of elements stored in vector

	T* m_Buffer; // pointer to the currently allocated array
};