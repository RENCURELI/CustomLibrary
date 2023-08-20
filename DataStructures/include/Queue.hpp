#pragma once

template<typename T, typename Container = DeQue<T>>
class Queue
{
public:
	Queue()
	{
		m_Container = Container();
	}

	explicit Queue(const Container& cont) : m_Container(cont) {}

	Queue(const Queue& other)
	{
		m_Container = other.GetContainer();
	}

	~Queue() {}

	Queue& operator=(const Queue& other)
	{
		m_Container = other.GetContainer();
		return *this;
	}

	inline T& front() { return m_Container.front(); }
	inline const T& front() const { return m_Container.front(); }
	inline T& back() { return m_Container.back(); }
	inline const T& back() const { return m_Container.back(); }
	inline bool empty() const { return m_Container.empty(); }
	inline size_t size() const { return m_Container.size(); }

	void push(const T& value)
	{
		m_Container.push_back(value);
	}

	void pop()
	{
		m_Container.pop_front();
	}

	const Container& GetContainer() const
	{
		return m_Container;
	}

protected:
	Container m_Container;
};