#pragma once
#include "Vector.hpp"
#include <iterator>
#include <memory>

#pragma region ConstIterator
template <typename DeQue>
class DeQueConstIterator
{
public:
	using iterator_concept = std::random_access_iterator_tag;
	using value_type = typename DeQue::value_type;
	using pointer = typename DeQue::pointer;
	using const_pointer = typename DeQue::const_pointer;
	using reference = typename DeQue::reference;
	using const_reference = typename DeQue::const_reference;
	using difference_type = std::ptrdiff_t;

	DeQueConstIterator(pointer ptr) : m_Ptr(ptr) {}

// 	preincrement
// 		DeQueConstIterator& operator++()
// 		{
// 			this->m_Ptr++;
// 			return *this;
// 		}
// 	
// 		// postincrement
// 		DeQueConstIterator operator++(int)
// 		{
// 			DeQueConstIterator it(*this);
// 			++(*this);
// 			return it;
// 		}
// 	
// 		// preincrement
// 		DeQueConstIterator& operator--()
// 		{
// 			this->m_Ptr--;
// 			return *this;
// 		}
// 	
// 		// postincrement
// 		DeQueConstIterator operator--(int)
// 		{
// 			DeQueConstIterator it(*this);
// 			--(*this);
// 			return it;
// 		}
// 	
// 		DeQueConstIterator& operator+=(const difference_type offset)
// 		{
// 			this->m_Ptr += offset;
// 			return *this;
// 		}
// 	
// 		DeQueConstIterator operator+(const difference_type offset)
// 		{
// 			DeQueConstIterator tmp = this->m_Ptr;
// 			tmp += offset;
// 			return tmp;
// 		}
// 	
// 		DeQueConstIterator& operator-=(const difference_type offset)
// 		{
// 			this->m_Ptr -= offset;
// 			return *this;
// 		}
// 	
// 		DeQueConstIterator operator-(const difference_type offset)
// 		{
// 			DeQueConstIterator tmp = this->m_Ptr;
// 			tmp -= offset;
// 			return tmp;
// 		}
// 	
// 		friend difference_type operator-(const DeQueConstIterator& lhs, const DeQueConstIterator& rhs)
// 		{
// 			return lhs.m_Ptr - rhs.m_Ptr;
// 		}
// 	
// 		const reference operator*() const { return *m_Ptr; }
// 		reference operator[](int index) { return *(m_Ptr + index); }
// 		const pointer operator->() const { return this->m_Ptr; }
// 		bool operator==(const DeQueConstIterator& other) const { return m_Ptr == other.m_Ptr; }
// 		bool operator!=(const DeQueConstIterator& other) const { return !(*this == other); }
// 		bool operator<(const DeQueConstIterator& right) const { return m_Ptr < right.m_Ptr; }
// 		bool operator>(const DeQueConstIterator& right) const { return right < *this; }
// 		bool operator<=(const DeQueConstIterator& right) const { return !(right < *this); }
// 		bool operator>=(const DeQueConstIterator& right) const { return !(*this < right); }

	pointer m_Ptr;
};
#pragma endregion ConstIterator

#pragma region Iterator

#pragma endregion Iterator

#pragma region ConstReverseIterator

#pragma endregion ConstReverseIterator

#pragma region ReverseIterator

#pragma endregion ReverseIterator


template<typename T>
class DeQue
{
public:
	using value_type = T;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;
	// block for iterators

public:
	DeQue()
	{
		// We first allocate the block
		m_Map = new Vector<T>[8];
		m_MapSize = 8;
	}

	void push_front(const T& value)
	{
		// We grow the map if the current offset is at the start of a block and we have no available blocks left to start filling
		// NOTE : We cannot have tail and head in the same block if tail is in front of head within the block 
		// EXAMPLE : in m_Map[0] we cannot have tail at index 1 and head at index 3 -> if such a scenario would happen, we reallocate more blocks
		if (m_Offset % m_BlockSize == 0 && m_MapSize <= (m_Size + m_BlockSize) / m_BlockSize)
		{
			// GrowMap will come here
		}

		// We get the last possible index if current offset is 0
		size_t newOffset = m_Offset != 0 ? m_Offset : m_MapSize * m_BlockSize;
		const size_t block = get_block(--newOffset); // We push in front of current head

		// We allocate the block if not already done
// 		if (&m_Map[block] == nullptr)
// 		{
// 			&m_Map[block] = new Vector<T>[m_BlockSize];
// 		}

		// We can't insert by regular means, so we set the data directly. The Deque is responsible for indexing and lookup
		memcpy_s(m_Map[block].data() + (newOffset % m_BlockSize), sizeof(T), &value, sizeof(T));
		m_Offset = newOffset;
		++m_Size;
	}


private:
	size_t get_block(size_t offset) const
	{
		// The binary and will return the index 010 & 111 -> 010 -> 2 -> the position is in block m_Map[2]
		return (offset / m_BlockSize) & (m_MapSize - 1);
	}

private:
	size_t m_Size = 0; // The number of elements stored in the deque
	size_t m_MapSize = 0; // The amount of blocks contained in the map
	size_t m_Offset = 0; // Offset between head and first entry m_Map[0].[0]
	size_t m_BlockSize = 8;
	Vector<T>* m_Map; // Ring buffer of pointers to each memory block of the deque ( fixed size arrays )
	T* m_Head = nullptr;
	T* m_Tail = nullptr;
};