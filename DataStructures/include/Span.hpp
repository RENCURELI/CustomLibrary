#pragma once

#include <iterator>
#include <span>

#pragma region Iterator
template<class T>
struct SpanIterator
{
	using iterator_concept = std::contiguous_iterator_tag;
	using value_type = remove_cv_t<T>;
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

template<class T, std::size_t Extent = std::dynamic_extent>
class Span
{
	using value_type = std::remove_cv_t<T>;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;
	using iterator = SpanIterator;
	//using const_iterator -> requires c++ 23 ( std::const_iterator<iterator> )
};