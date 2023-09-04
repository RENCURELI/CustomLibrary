#pragma once

#include <DeQue.hpp>

template<typename T, typename Container = DeQue<T>>
class Stack
{
public:
	Stack()
	{
		m_Container = Container();
	}

	explicit Stack(const Container& cont) : m_Container(cont) {}

	explicit Stack(Container&& cont) : m_Container(std::move(cont)) {}

	// For stack copy and stack move, constructors are implicitly declared

	~Stack() {}

	inline T& top() { return m_Container.back(); }
	inline const T& top() const { return m_Container.back(); }
	inline size_t size() const { return m_Container.size(); }
	inline bool empty() const { return m_Container.empty(); }
	
	void push(const T& value)
	{
		m_Container.push_back(value);
	}

	void pop()
	{
		m_Container.pop_back();
	}

	// operator= is implicitly declared for both copy and move

	const Container& GetContainer() const
	{
		return m_Container;
	}

protected:
	Container m_Container;
};