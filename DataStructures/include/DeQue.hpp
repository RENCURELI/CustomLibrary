#pragma once
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
	using map_type = T**;
	// block for iterators

public:
	DeQue()
	{
		// We first allocate the map
		m_Map = new pointer[MIN_MAP_SIZE];
		m_MapSize = 8;

		// We set all blocks to nullptr ( prevents undefined behaviour ), we will allocate as we push data inside
		memset(m_Map, 0, sizeof(pointer) * m_MapSize);
	}

	~DeQue()
	{
		if (m_Map != nullptr)
		{
			for (size_t block = m_MapSize; block > 0;)
			{
				if (m_Map[--block] != nullptr)
				{
					std::destroy(&m_Map[block], &m_Map[block] + BLOCK_SIZE);
				}
			}
			std::destroy(m_Map, m_Map + m_MapSize);
		}

		m_MapSize = 0;
		m_Map = nullptr;
	}

	void push_front(const T& value)
	{
		// We grow the map if the current offset is at the start of a block and we have no available blocks left to start filling
		// NOTE : We cannot have tail and head in the same block if tail is in front of head within the block 
		// EXAMPLE : in m_Map[0] we cannot have tail at index 1 and head at index 3 -> if such a scenario would happen, we reallocate more blocks
		if (m_Offset % BLOCK_SIZE == 0 && m_MapSize <= (m_Size + BLOCK_SIZE) / BLOCK_SIZE)
		{
			grow_map(1);
		}

		// We get the last possible index if current offset is 0
		size_t newOffset = m_Offset != 0 ? m_Offset : m_MapSize * BLOCK_SIZE;
		const size_t block = get_block(--newOffset); // We push in front of current head

		// We allocate the block if not already done
		if (m_Map[block] == nullptr)
		{
			m_Map[block] = new T[BLOCK_SIZE];
		}

		// We can't insert by regular means, so we set the data directly. The Deque is responsible for indexing and lookup
		//memcpy_s(&m_Map[block] + (newOffset % BLOCK_SIZE), sizeof(T), &value, sizeof(T));
		m_Map[block][newOffset % BLOCK_SIZE] = value;
		m_Offset = newOffset;
		++m_Size;
	}

	void push_back(const T& value)
	{
		if ((m_Offset + m_Size) % BLOCK_SIZE == 0 && m_MapSize <= (m_Size + BLOCK_SIZE) / BLOCK_SIZE)
		{
			grow_map(1);
		}

		// We get the first available position at end of Deque ( we don't keep active track of head and tail, so we calculate it )
		size_t newOffset = m_Offset + m_Size;
		const size_t block = get_block(newOffset);

		// We allocate the block if not already done
		if (m_Map[block] == nullptr)
		{
			m_Map[block] = new T[BLOCK_SIZE];
		}

		m_Map[block][newOffset % BLOCK_SIZE] = value;

		// We don't update offset because we aren't moving the "head"
		++m_Size;
	}

	size_t size() const { return m_Size; }

private:
	size_t get_block(size_t offset) const
	{
		// The binary and will return the index 010 & 111 -> 010 -> 2 -> the position is in block m_Map[2]
		return (offset / BLOCK_SIZE) & (m_MapSize - 1);
	}

	// Grow the map by AT LEAST count, map size should always be a power of 2
	void grow_map(size_t count)
	{
		// This block is to find the first power of 2 larger than the current map size
		size_t newSize = m_MapSize > 0 ? m_MapSize : 1; // Assumption is made that MapSize is always a power of 2
		while (newSize - m_MapSize < count || newSize < MIN_MAP_SIZE)
		{
			// Disregarding a few safety nets from the STL here ( namely checking max possible size )
			newSize *= 2;
		}
		count = newSize - m_MapSize;


		size_t blockOffset = m_Offset / BLOCK_SIZE; // Here we get in which block the offset is
		map_type newMap = new pointer[newSize]; // We allocate the memory for the new map
		map_type ptr = newMap + blockOffset; // We point to the equivalent of the block offset in the new map ( pointer from where we copy over data )

		memset(newMap, 0, sizeof(pointer) * newSize);

		// We copy the data from the offset block to the end of the old map at position ptr
		ptr = std::uninitialized_copy(m_Map + blockOffset, m_Map + m_MapSize, ptr); // ptr is modified to now point after inserted data
		ptr = std::uninitialized_copy(m_Map, m_Map + blockOffset, ptr); // Copy from start of old to bock offset, behind ptr
		// NOTE : STL checks if the block offset is smaller or bigger than the increment size, but it should never be possible, so I don't check

		// We free memory at old location
		if (m_Map != nullptr)
		{
			std::destroy(m_Map, m_Map + m_MapSize);
		}

		m_Map = newMap; // We point to the new valid memory location
		m_MapSize = newSize; // We update the map size
	}

private:
	size_t m_Size = 0; // The number of elements stored in the deque
	size_t m_MapSize = 0; // The amount of blocks contained in the map
	size_t m_Offset = 0; // Offset between head and first entry m_Map[0].[0]
	static const size_t BLOCK_SIZE = 8;
	const size_t MIN_MAP_SIZE = 8;
	map_type m_Map; // Ring buffer of pointers to each memory block of the deque ( fixed size arrays )
};