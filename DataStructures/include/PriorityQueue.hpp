#pragma once

#include <algorithm>
#include <functional>

#include <Vector.hpp>

template<typename T, class Container = Vector<T>, class Compare = std::less<typename Container::value_type>>
class PriorityQueue
{
public:
	using value_type = Container::value_type;
	using pointer = Container::pointer;
	using const_pointer = Container::const_pointer;

	PriorityQueue() = default;

	explicit PriorityQueue(const Compare& compare)
		: m_Compare(compare), m_Container() {}

	explicit PriorityQueue(const Compare& compare, const Container& cont)
		: m_Compare(compare), m_Container(cont)
	{
		std::make_heap(m_Container.begin(), m_Container.end(), m_Compare);
	}

	PriorityQueue(const Compare& compare, Container&& cont)
		: m_Compare(compare), m_Container(std::move(cont))
	{
		std::make_heap(m_Container.begin(), m_Container.end(), m_Compare);
	}

	// For Priority queue copy and Priority queue move, constructors are implicitly declared

	template<std::input_iterator InputIt>
	PriorityQueue(InputIt first, InputIt last, const Compare& compare = Compare()) : m_Compare(compare)
	{
		m_Container.insert(m_Container.cend(), first, last);
		std::make_heap(m_Container.begin(), m_Container.end(), m_Compare);
	}

	template<std::input_iterator InputIt>
	PriorityQueue(InputIt first, InputIt last, const Compare& comp, const Container& cont)
	{
		m_Compare = comp;
		m_Container = cont;
		m_Container.insert(m_Container.cend(), first, last);
		std::make_heap(m_Container.begin(), m_Container.end(), m_Compare);
	}

	~PriorityQueue() {}

	// operator= is implicitly declared

	inline const T& top() const { return m_Container.front(); }
	inline bool empty() const { return m_Container.empty(); }
	inline size_t size() const { return m_Container.size(); }

	void push(const value_type& value)
	{
		m_Container.push_back(value);
		std::push_heap(m_Container.begin(), m_Container.end(), m_Compare);
	}

	void pop()
	{
		// Removes data from the heap ( still in underlying container )
		std::pop_heap(m_Container.begin(), m_Container.end(), m_Compare);
		// Removes the data from the container itself
		m_Container.pop_back();
	}

	const Container& GetContainer() const
	{
		return m_Container;
	}

protected:
	Container m_Container;
	Compare m_Compare;
};

template<class T, class Cont>
bool operator==(const PriorityQueue<T, Cont>& lhs, const PriorityQueue<T, Cont>& rhs)
{
	return lhs.GetContainer() == rhs.GetContainer();
}

template <class T, class Cont>
constexpr auto operator<=>(const PriorityQueue<T, Cont>& lhs, const PriorityQueue<T, Cont>& rhs)
{
	return lhs.GetContainer() <=> rhs.GetContainer();
}