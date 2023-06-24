#pragma once
#include <iterator>

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

	DeQueConstIterator(pointer ptr) : m_Ptr(ptr);

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
		m_Buffer = new int[4];
	}

private:
	size_t m_Size = 0;
	int* m_Buffer; // Ring buffer of pointers to each memory block of the deque ( fixed size arrays )
};