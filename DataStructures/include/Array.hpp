#pragma once
#include <iostream>
#include <cstddef>
#include <compare>
#include <stdexcept>
#include <iterator>

#pragma region ConstIterator
template<typename T, size_t Size>
class ArrayConstIterator
{
public:
	using iterator_concept = std::contiguous_iterator_tag;
	using value_type = T;
	using pointer = const value_type*;
	using reference = const value_type&;
	using difference_type = std::ptrdiff_t;

	using PtrType = pointer;

	ArrayConstIterator(PtrType ptr) : m_Ptr(ptr) {}

	explicit ArrayConstIterator(PtrType ptr, size_t offset) : m_Ptr(ptr + offset) {}

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
template<typename T, size_t Size>
class ArrayIterator : public ArrayConstIterator<T, Size>
{
public:
	using value_type = T;
	using pointer = value_type*;
	using reference = value_type&;
	using difference_type = std::ptrdiff_t;
	using BaseIt = ArrayConstIterator<T, Size>;

	using PtrType = typename pointer;

public:
	ArrayIterator(PtrType ptr) : BaseIt(ptr) {}

	explicit ArrayIterator(PtrType ptr, size_t offset) : BaseIt(ptr + offset) {}

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
 	using iterator = ArrayIterator<T, N>;
 	using const_iterator = ArrayConstIterator<T, N>;
 	using reverse_iterator = std::reverse_iterator<iterator>;
 	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	T values[N];

	constexpr T& operator[](size_t index)
	{
		if (index >= N)
		{
			throw std::out_of_range("[ERROR] Index out of bounds");
		}

		return values[index];
	}

	constexpr const T& operator[](size_t index) const
	{
		if (index >= N)
		{
			throw std::out_of_range("[ERROR] Index out of bounds");
		}

		return values[index];
	}

	inline constexpr const T& at(const size_t index) const 
	{
		if (index >= N)
		{
			throw std::out_of_range("[ERROR] Index out of bounds");
		}

		return values[index];
	}

	inline constexpr T& at(const size_t index)
	{
		if (index >= N)
		{
			throw std::out_of_range("[ERROR] Index out of bounds");
		}

		return values[index];
	}

	inline constexpr size_t size() const noexcept { return N; }
	inline constexpr size_t max_size() const noexcept { return N; }
	[[nodiscard]] inline constexpr bool empty() const noexcept { return N == 0; }
	inline constexpr const T& front() const { return values[0]; }
	inline constexpr T& front() { return values[0]; }
	inline constexpr const T& back() const { return values[N - 1]; }
	inline constexpr T& back() { return values[N - 1]; }
	inline constexpr T* data() noexcept { return values; }
	inline constexpr const T* data() const noexcept { return values; }
	inline constexpr iterator begin() noexcept { return iterator(values); }
	inline constexpr const_iterator cbegin() const noexcept { return const_iterator(values); }
	inline constexpr reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
	inline constexpr const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }
	inline constexpr iterator end() noexcept { return iterator(values, size()); }
	inline constexpr const_iterator cend() const noexcept { return const_iterator(values, size()); }
	inline constexpr reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
	inline constexpr const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

	constexpr void fill(const T& val)
	{
		for (int i = 0; i < N; i++)
		{
			values[i] = val;
		}
	}

	constexpr void swap(Array& other) noexcept(std::is_nothrow_swappable_v<T>)
	{
		for (size_t i = 0; i < size(); i++)
		{
			T temp = other[i];
			other[i] = values[i];
			values[i] = temp;
		}
	}
};

template<class T, std::size_t N>
bool operator==(const Array<T, N>& lhs, const Array<T, N>& rhs)
{
	return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
}

template <class T, std::size_t N>
constexpr auto operator<=>(const Array<T, N>& lhs, const Array<T, N>& rhs)
{
	return std::lexicographical_compare_three_way(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
}