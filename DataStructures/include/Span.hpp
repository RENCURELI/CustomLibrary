#pragma once

#include <cassert>
#include <initializer_list>
#include <iterator>
#include <type_traits>

#pragma region Iterator
template<class T>
struct SpanIterator
{
	using iterator_concept = std::contiguous_iterator_tag;
	using value_type = std::remove_cv_t<T>;
	using difference_type = std::ptrdiff_t;
	using pointer = T*;
	using reference = T&;

	[[nodiscard]] constexpr reference operator*() const noexcept
	{
		return *m_Ptr;
	}

	[[nodiscard]] constexpr pointer operator->() const noexcept
	{
		return m_Ptr;
	}

	constexpr SpanIterator& operator++() noexcept
	{
		++m_Ptr;
		return *this;
	}

	constexpr SpanIterator operator++(int) noexcept
	{
		SpanIterator it{ *this };
		++(*this);
		return it;
	}

	constexpr SpanIterator& operator--() noexcept
	{
		--m_Ptr;
		return *this;
	}

	constexpr SpanIterator operator--(int) noexcept
	{
		SpanIterator it{ *this };
		--(*this);
		return it;
	}

	constexpr SpanIterator& operator+=(const difference_type offset) noexcept
	{
		m_Ptr += offset;
		return m_Ptr;
	}

	[[nodiscard]] constexpr SpanIterator operator+(const difference_type offset) const noexcept
	{
		SpanIterator it{ *this };
		it += offset;
		return it;
	}

	constexpr SpanIterator& operator-=(const difference_type offset) noexcept
	{
		m_Ptr -= offset;
		return m_Ptr;
	}

	[[nodiscard]] constexpr SpanIterator operator-(const difference_type offset) const noexcept
	{
		SpanIterator it{ *this };
		it -= offset;
		return it;
	}

	[[nodiscard]] constexpr reference operator[](const difference_type offset) const noexcept
	{
		return *(*this + offset);
	}

	[[nodiscard]] constexpr bool operator==(const SpanIterator& other) const noexcept
	{
		return m_Ptr == other.m_Ptr;
	}

	[[nodiscard]] constexpr std::strong_ordering operator<=>(const SpanIterator& other) const noexcept
	{
		return m_Ptr <=> other.m_Ptr;
	}

	pointer m_Ptr = nullptr;
};

#pragma endregion Iterator

template<class OtherT, class T>
concept _Span_array_convertible = requires(T elementType, OtherT otherType)
{
	std::is_convertible_v<OtherT(*)[], T(*)[]>;
};

template<class T, std::size_t Extent>
class Span
{
public:
	using element_type = T;
	using value_type = std::remove_cv_t<T>;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;
	using iterator = SpanIterator<T>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	//using const_iterator -> requires c++ 23 ( std::const_iterator<iterator> )

	static constexpr size_type extent = Extent;

	constexpr Span(const Span&) noexcept = default;
	constexpr Span& operator=(const Span&) noexcept = default;

	constexpr Span() noexcept requires (Extent == 0) : m_Data{ nullptr } {}
	// Might require CXX 26
// 	constexpr explicit Span(std::initializer_list<value_type> initList) requires std::is_const_v<element_type> : m_Data{initList.begin()}
// 	{
// 		static_assert(Extent == initList.size(), "[ERROR] Size mismatch in span's constructor Extent != initList.size()");
// 	}
	
	template<std::_Span_compatible_iterator<element_type> It>
	constexpr explicit Span(It first, size_type count) : m_Data{ std::to_address(first) }
	{
		(void)count;
		//static_assert(Extent == count, "[ERROR] Size mismatch in span constructor (iterator, len)");
		assert(Extent == count);
	}

	template <size_t _Size>
	constexpr Span(std::type_identity_t<element_type>(&arr)[_Size]) noexcept : m_Data{arr} {}

	template<_Span_array_convertible<element_type> U, std::size_t N> // U's type will be inferred and set as first argument of concept
	constexpr Span(std::array<U, N>& arr) noexcept : m_Data{ arr.data() } {}

	template<_Span_array_convertible<element_type> U, std::size_t N> // U's type will be inferred and set as first argument of concept
	constexpr Span(const std::array<U, N>& arr) noexcept : m_Data{ arr.data() } {}

private:
	pointer m_Data;
};

template<class T>
class Span<T, std::dynamic_extent>
{
public:
	using element_type = T;
	using value_type = std::remove_cv_t<T>;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;
	using iterator = SpanIterator<T>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	//using const_iterator -> requires c++ 23 ( std::const_iterator<iterator> )

	static constexpr size_type extent = std::dynamic_extent;

private:
	pointer m_Data;
	size_type m_Size;
};