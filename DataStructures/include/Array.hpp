#pragma once
#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <iterator>

#pragma region ConstIterator
template<typename Array>
class ArrayConstIterator
{
public:
	using iterator_concept = std::contiguous_iterator_tag;
	using value_type = typename Array::value_type;
	using pointer = Array::const_pointer;
	using reference = const value_type&;
	using difference_type = std::ptrdiff_t;

	using PtrType = typename Array::pointer;

	ArrayConstIterator(PtrType ptr) : m_Ptr(ptr) {}

	// preincrement
	ArrayConstIterator& operator++()
	{
		this->m_Ptr++;
		return *this;
	}

	// postincrement
	ArrayConstIterator operator++(int)
	{
		ArrayConstIterator it(*this);
		++(*this);
		return it;
	}

	// preincrement
	ArrayConstIterator& operator--()
	{
		this->m_Ptr--;
		return *this;
	}

	// postincrement
	ArrayConstIterator operator--(int)
	{
		ArrayConstIterator it(*this);
		--(*this);
		return it;
	}

	ArrayConstIterator& operator+=(const difference_type offset)
	{
		this->m_Ptr += offset;
		return *this;
	}

	ArrayConstIterator operator+(const difference_type offset)
	{
		ArrayConstIterator tmp = this->m_Ptr;
		tmp += offset;
		return tmp;
	}

	ArrayConstIterator& operator-=(const difference_type offset)
	{
		this->m_Ptr -= offset;
		return *this;
	}

	ArrayConstIterator operator-(const difference_type offset)
	{
		ArrayConstIterator tmp = this->m_Ptr;
		tmp -= offset;
		return tmp;
	}

	friend difference_type operator-(const ArrayConstIterator& lhs, const ArrayConstIterator& rhs)
	{
		return lhs.m_Ptr - rhs.m_Ptr;
	}

	const reference operator*() const { return *m_Ptr; }
	reference operator[](int index) { return *(m_Ptr + index); }
	const pointer operator->() const { return this->m_Ptr; }
	bool operator==(const ArrayConstIterator& other) const { return m_Ptr == other.m_Ptr; }
	bool operator!=(const ArrayConstIterator& other) const { return !(*this == other); }
	bool operator<(const ArrayConstIterator& right) const { return m_Ptr < right.m_Ptr; }
	bool operator>(const ArrayConstIterator& right) const { return right < *this; }
	bool operator<=(const ArrayConstIterator& right) const { return !(right < *this); }
	bool operator>=(const ArrayConstIterator& right) const { return !(*this < right); }

	PtrType m_Ptr;
};

#pragma endregion ConstIterator

#pragma region Iterator
template<typename Array>
class ArrayIterator : public ArrayConstIterator<Array>
{
public:
	using value_type = typename Array::value_type;
	using pointer = Array::pointer;
	using reference = value_type&;
	using difference_type = std::ptrdiff_t;
	using BaseIt = ArrayConstIterator<Array>;
public:
	// preincrement
	ArrayIterator& operator++()
	{
		BaseIt::operator++();
		return *this;
	}

	// postincrement
	ArrayIterator operator++(int)
	{
		ArrayIterator it(*this);
		++(*this);
		return it;
	}

	// preincrement
	ArrayIterator& operator--()
	{
		BaseIt::operator--();
		return *this;
	}

	// postincrement
	ArrayIterator operator--(int)
	{
		ArrayIterator it(*this);
		--(*this);
		return it;
	}

	ArrayIterator& operator+=(const difference_type offset)
	{
		BaseIt::operator+=(offset);
		return *this;
	}

	ArrayIterator operator+(const difference_type offset) const
	{
		ArrayIterator tmp = *this;
		tmp += offset;
		return tmp;
	}

	ArrayIterator& operator-=(const difference_type offset)
	{
		BaseIt::operator-=(offset);
		return *this;
	}

	ArrayIterator operator-(const difference_type offset) const
	{
		ArrayIterator tmp = *this;
		tmp -= offset;
		return tmp;
	}

	friend difference_type operator-(const ArrayIterator& lhs, const ArrayIterator& rhs)
	{
		return lhs.m_Ptr - rhs.m_Ptr;
	}

	reference operator*() const { return const_cast<reference>(BaseIt::operator*()); }
	reference operator[](int index) { return *(this->m_Ptr + index); }
	pointer operator->() const { return this->m_Ptr; }
	bool operator==(const ArrayIterator& other) const { return this->m_Ptr == other.m_Ptr; }
	bool operator!=(const ArrayIterator& other) const { return !(*this == other); }
	bool operator<(const ArrayIterator& right) const { return this->m_Ptr < right.m_Ptr; }
	bool operator>(const ArrayIterator& right) const { return right < *this; }
	bool operator<=(const ArrayIterator& right) const { return !(right < *this); }
	bool operator>=(const ArrayIterator& right) const { return !(*this < right); }
};
#pragma endregion Iterator

#pragma warning(disable : 4200) // We disable this warning as we assign the value of N on construction -> https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-levels-2-and-4-c4200?f1url=%3FappId%3DDev16IDEF1%26l%3DEN-US%26k%3Dk(C4200)%26rd%3Dtrue&view=msvc-170
template<typename T, const size_t N>
struct Array
{
 	using value_type = T;
 	using pointer = T*;
 	using const_pointer = const T*;
 	using iterator = ArrayIterator<Array<T, N>>;
 	using const_iterator = ArrayConstIterator<Array<T, N>>;
 	using reverse_iterator = std::reverse_iterator<iterator>;
 	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
	// size_type would be the unsigned version of the allocator_traits::difference_type ( I currently don't have an allocator or allocator_traits )
	//using size_type = std::make_unsigned<const_iterator::difference_type>;

	T values[N];

	T& operator[](size_t index)
	{
		if (index >= N)
			throw std::out_of_range("[ERROR] Index out of bounds");

		return values[index];
	}

	const T& operator[](size_t index) const
	{
		if (index >= N)
			throw std::out_of_range("[ERROR] Index out of bounds");

		return values[index];
	}

	inline const T& at(const size_t index) const 
	{
		if (index >= N)
			throw std::out_of_range("[ERROR] Index out of bounds");

		return values[index];
	}

	inline T& at(const size_t index)
	{
		if (index >= N)
			throw std::out_of_range("[ERROR] Index out of bounds");

		return values[index];
	}

	inline size_t size() const { return N; }
	inline size_t max_size() const { return N; }
	inline bool empty() const { return N == 0; }
	inline const T& front() const { return values[0]; }
	inline T& front() { return values[0]; }
	inline const T& back() const { return values[N - 1]; }
	inline T& back() { return values[N - 1]; }
	inline T* data() { return values; }
	inline const T* data() const { return values; }
	inline iterator begin() { return iterator(values); }
	inline const_iterator cbegin() const { return const_iterator(values); }
	inline reverse_iterator rbegin() { return reverse_iterator(end()); }
	inline const_reverse_iterator crbegin() const { return const_reverse_iterator(cend()); }
	inline iterator end() { return iterator(values + N); }
	inline const_iterator cend() const { return const_iterator(values + N); }
	inline reverse_iterator rend() { return reverse_iterator(begin()); }
	inline const_reverse_iterator crend() const { return const_reverse_iterator(cbegin()); }

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
		
		for (size_t i = 0; i < size(); i++)
		{
			T temp = other[i];
			other[i] = values[i];
			values[i] = temp;
		}
	}
};