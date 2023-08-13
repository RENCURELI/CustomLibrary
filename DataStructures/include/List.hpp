#pragma once
#include "ListNode.hpp"
#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <iterator>

#pragma region ConstIterator
template<typename List>
class ListConstIterator
{
public:
	using iterator_concept = std::bidirectional_iterator_tag;
	using value_type = typename List::value_type;
	using pointer = typename List::const_pointer;
	using reference = const value_type&;
	using difference_type = std::ptrdiff_t;

	using PtrType = typename List::pointer;

	ListConstIterator(PtrType ptr) : m_Ptr(ptr) {}

	// preincrement
	ListConstIterator& operator++()
	{
		m_Ptr = m_Ptr->m_Next;
		return *this;
	}

	// postincrement
	ListConstIterator operator++(int)
	{
		ListConstIterator tmp = *this;
		m_Ptr = m_Ptr.m_Next;
		return tmp;
	}

	// preincrement
	ListConstIterator& operator--()
	{
		m_Ptr = m_Ptr->m_Previous;
		return *this;
	}

	// postincrement
	ListConstIterator operator--(int)
	{
		ListConstIterator tmp = *this;
		m_Ptr = m_Ptr.m_Previous;
		return tmp;
	}

	const reference operator*() const { return m_Ptr->m_Data; }
	const pointer operator->() const { return this->m_Ptr; }
	bool operator==(const ListConstIterator& other) const { return m_Ptr == other.m_Ptr; }
	bool operator!=(const ListConstIterator& other) const { return !(*this == other); }

	PtrType m_Ptr;
};

#pragma endregion ConstIterator

#pragma region Iterator
template<typename List>
class ListIterator : public ListConstIterator<List>
{
public:
	using value_type = typename List::value_type;
	using pointer = typename List::pointer;
	using reference = value_type&;
	using difference_type = std::ptrdiff_t;
	using BaseIt = ListConstIterator<List>;
public:
	// preincrement
	ListIterator& operator++()
	{
		BaseIt::operator++();
		return *this;
	}

	// postincrement
	ListIterator operator++(int)
	{
		ListConstIterator tmp = *this;
		BaseIt::operator++();
		return tmp;
	}

	// preincrement
	ListIterator& operator--()
	{
		BaseIt::operator--();
		return *this;
	}

	// postincrement
	ListIterator operator--(int)
	{
		ListConstIterator tmp = *this;
		BaseIt::operator--();
		return tmp;
	}

	reference operator*() const { return const_cast<reference>(BaseIt::operator*()); }
	pointer operator->() const { return this->m_Ptr; }
	bool operator==(const ListIterator& other) const { return this->m_Ptr == other.m_Ptr; }
	bool operator!=(const ListIterator& other) const { return !(*this == other); }

};
#pragma endregion Iterator

template<typename T>
bool operator==(const ListIterator<T>& lhs, const ListConstIterator<T>& rhs) { return lhs.m_Ptr == rhs.m_Ptr; }

template<class T>
class List
{
public:
	using value_type = T;
	using pointer = ListNode_t<T>*;
	using const_pointer = const T*;
	using iterator = ListIterator<List<T>>;
	using const_iterator = ListConstIterator<List<T>>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

public:
	List() {};
	List(std::initializer_list<T> l)
	{
		for (const auto& it : l)
		{
			push_back(it);
		}
	}

	List(const List& other)
	{
		ListNode_t<T>* temp = other.m_Head;
		while (temp != nullptr)
		{
			this->push_back(temp->m_Data);
			temp = temp->m_Next;
		}
	}

	~List()
	{
		clear();
	}

	void push_front(T data)
	{
		ListNode_t<T>* newNode = new ListNode_t<T>(data);

		// We are adding the first node
		if (m_Head == nullptr)
		{
			m_Head = newNode;
			m_Tail = newNode;
		}
		else
		{
			newNode->m_Next = m_Head;
			m_Head->m_Previous = newNode;
			m_Head = newNode;
		}
		m_Size++;
	}

	void push_back(T data)
	{
		ListNode_t<T>* newNode = new ListNode_t<T>(data);

		// We are adding the first node
		if (m_Head == nullptr)
		{
			m_Head = newNode;
			m_Tail = newNode;
		}
		else
		{
			m_Tail->m_Next = newNode;
			newNode->m_Previous = m_Tail;
			m_Tail = newNode;
		}
		m_Size++;
	}

	iterator insert(const_iterator pos, const T& data)
	{
		ListNode_t<T>* newNode = new ListNode_t<T>(data);

		// Empty list case handled by creating first element
		if (m_Head == nullptr)
		{
			m_Head = newNode;
			m_Tail = newNode;
		}
		else
		{
			// We insert at index 0, specific behaviour
			if (pos == cbegin())
			{
				newNode->m_Next = m_Head;
				m_Head->m_Previous = newNode;
				m_Head = newNode;
			}
			else if (pos == cend())
			{
				m_Tail->m_Next = newNode;
				newNode->m_Previous = m_Tail;
				m_Tail = newNode;
			}
			else
			{
				ListNode_t<T>* prevNode = pos.m_Ptr->m_Previous;
				newNode->m_Next = prevNode->m_Next;
				newNode->m_Previous = prevNode;
				prevNode->m_Next = newNode;
			}
		}

		m_Size++;
		return makeIterator(pos.m_Ptr);
	}

	iterator insert(const_iterator pos, size_t count, const T& data)
	{
		iterator returnVal = makeIterator(pos.m_Ptr);

		// No insertion
		if (count == 0)
		{
			return returnVal;
		}
		
		if (m_Head == nullptr)
		{
			for (; count > 0; --count)
			{
				push_back(data);
			}
			return begin();
		}
		else
		{
			ListNode_t<T>* newNode = new ListNode_t<T>(data);
			returnVal = makeIterator(newNode);

			for (int i = 0; i <= count; ++i)
			{
				if (pos == cbegin())
				{
					newNode->m_Next = m_Head;
					m_Head->m_Previous = newNode;
					m_Head = newNode;
				}
				else if (pos == cend())
				{
					m_Tail->m_Next = newNode;
					newNode->m_Previous = m_Tail;
					m_Tail = newNode;
				}
				else
				{
					ListNode_t<T>* prevNode = pos.m_Ptr->m_Previous;
					newNode->m_Next = prevNode->m_Next;
					newNode->m_Previous = prevNode;
					prevNode->m_Next = newNode;
				}

				newNode = new ListNode_t<T>(data);
			}
		}

		m_Size += count;
		return returnVal;
	}

	// inserts [first last)
	iterator insert(const_iterator pos, iterator first, iterator last)
	{
		iterator returnVal = makeIterator(pos.m_Ptr);

		if (first == last)
		{
			return returnVal;
		}

		if (m_Head == nullptr)
		{
			for (; first != last; ++first)
			{
				push_back(first.m_Ptr->m_Data);
			}
			return begin();
		}
		else
		{
			returnVal = first;
			int i = 0;
			for (; first != last; ++first)
			{
				ListNode_t<T>* newNode = new ListNode_t<T>(first.m_Ptr->m_Data);
				if (pos == cbegin() && i == 0)
				{
					newNode->m_Next = m_Head;
					m_Head->m_Previous = newNode;
					m_Head = newNode;
				}
				else if (pos == cend())
				{
					m_Tail->m_Next = newNode;
					newNode->m_Previous = m_Tail;
					m_Tail = newNode;
				}
				else
				{
					pos.m_Ptr->m_Previous->m_Next = newNode;
					newNode->m_Previous = pos.m_Ptr->m_Previous;
					newNode->m_Next = pos.m_Ptr;
					pos.m_Ptr->m_Previous = newNode;
				}

				if (i == 0)
				{
					returnVal = makeIterator(newNode);
				}

				++i;
				++m_Size;
			}
			return returnVal;
		}

	}

	iterator insert(const_iterator pos, std::initializer_list<T> ilist)
	{
		if (ilist.size() == 0)
			return makeIterator(pos.m_Ptr);

		iterator returnVal = makeIterator(pos.m_Ptr);

		if (m_Head == nullptr)
		{
			for (const auto& it : ilist)
			{
				push_back(it);
			}
			return begin();
		}
		else if (pos == cend())
		{
			int i = 0;
			for (const auto& it : ilist)
			{
				ListNode_t<T>* newNode = new ListNode_t<T>(it);
				m_Tail->m_Next = newNode;
				newNode->m_Previous = m_Tail;
				m_Tail = newNode;

				if (i == 0)
				{
					returnVal = makeIterator(newNode);
				}
				++i;
			}

			m_Size += ilist.size();
			return returnVal;
		}
		else
		{
			int i = 0;
			for (const auto& it : ilist)
			{
				ListNode_t<T>* newNode = new ListNode_t<T>(it);
				pos.m_Ptr->m_Previous->m_Next = newNode;
				newNode->m_Previous = pos.m_Ptr->m_Previous;
				newNode->m_Next = pos.m_Ptr;
				pos.m_Ptr->m_Previous = newNode;

				if (i == 0)
				{
					returnVal = makeIterator(newNode);
				}
				++i;
			}

			m_Size += ilist.size();
			return returnVal;
		}
	}

	// Remove last node
	void pop_back()
	{
		if (m_Size == 0)
			return;

		if (m_Size == 1)
		{
			delete m_Tail;
			m_Head = nullptr;
			m_Tail = nullptr;
		}
		else if (m_Size > 1)
		{
			ListNode_t<T>* newTail = m_Tail->m_Previous;
			newTail->m_Next = nullptr;
			delete m_Tail;
			m_Tail = newTail;
		}

		m_Size--;
	}

	// Remove first node
	void pop_front()
	{
		if (m_Size == 0)
			return;

		if (m_Size == 1)
		{
			delete m_Head;
			m_Head = nullptr;
			m_Tail = nullptr;
		}
		else if (m_Size > 1)
		{
			ListNode_t<T>* newHead = m_Head->m_Next;
			newHead->m_Previous = nullptr;
			delete m_Head;
			m_Head = newHead;
		}

		m_Size--;
	}

	// Remove node at specified Index
	iterator erase(const_iterator pos)
	{
		iterator returnedIt = makeIterator(pos.m_Ptr->m_Next);
		if (pos == begin())
		{
			ListNode_t<T>* currHead = m_Head;
			m_Head = m_Head->m_Next;
			delete currHead;
		}
		else if (pos == makeIterator(m_Tail))
		{
			ListNode_t<T>* newTail = m_Tail->m_Previous;
			m_Tail = newTail;
			delete m_Tail->m_Next;
			m_Tail->m_Next = nullptr;
		}
		else
		{
			ListNode_t<T>* nodeToDel = pos.m_Ptr;
			nodeToDel->m_Previous->m_Next = nodeToDel->m_Next;
			nodeToDel->m_Next->m_Previous = nodeToDel->m_Previous;
			delete nodeToDel;
		}

		m_Size--;
		return returnedIt;
	}

	// Removes in range [First, Last)
	iterator erase(const_iterator first, const_iterator last)
	{
		if (first == last)
		{
			return makeIterator(last.m_Ptr);
		}
		else
		{
			do
			{
				ListNode_t<T>* nodeToDel = first.m_Ptr;
				first.m_Ptr = nodeToDel->m_Next;
				first.m_Ptr->m_Previous = nodeToDel->m_Previous;
				nodeToDel->m_Previous->m_Next = first.m_Ptr;
				delete nodeToDel;
				m_Size--;
			} while (first.m_Ptr != last.m_Ptr);

			return makeIterator(last.m_Ptr);
		}
	}

	// Clear the content of the List
	void clear()
	{
		// Go from m_Head to m_Tail and free memory
		while (m_Head != nullptr)
		{
			ListNode_t<T>* temp = m_Head->m_Next;
			delete m_Head;
			m_Head = temp;
		}

		m_Size = 0;
		m_Head = nullptr;
		m_Tail = nullptr;
	}

	inline bool empty() const { return m_Size == 0; }
	inline size_t size() const { return m_Size; }
	inline T& front() { return m_Size > 0 ? m_Head->m_Data : throw std::runtime_error("[ERROR] Trying to access an empty list"); }
	inline const T& front() const { return m_Size > 0 ? m_Head->m_Data : throw std::runtime_error("[ERROR] Trying to access an empty list"); }
	inline T& back() { return m_Size > 0 ? m_Tail->m_Data : throw std::runtime_error("[ERROR] Trying to access an empty list"); }
	inline const T& back() const { return m_Size > 0 ? m_Tail->m_Data : throw std::runtime_error("[ERROR] Trying to access an empty list"); }
	inline iterator begin() { return iterator(m_Head); }
	inline const_iterator cbegin() const { return const_iterator(m_Head); }
	inline reverse_iterator rbegin() { return reverse_iterator(end()); }
	inline const_reverse_iterator crbegin() const { return const_reverse_iterator(cend()); }
	inline iterator end() { return iterator(nullptr); }
	inline const_iterator cend() const { return const_iterator(nullptr); }
	inline reverse_iterator rend() { return reverse_iterator(begin()); }
	inline const_reverse_iterator crend() const { return const_reverse_iterator(cbegin()); }

	void PrintList()
	{
		ListNode_t<T>* current = m_Head;
		while (current != nullptr)
		{
			std::cout << " -> " << current->m_Data;
			current = current->m_Next;
		}
	}

	// Copy
	List<T>& operator=(const List<T>& other)
	{
		if (this == &other)
			return *this;

		ListNode_t<T>* temp = other.m_Head;
		while (temp != nullptr)
		{
			this->push_back(temp->m_Data);
			temp = temp->m_Next;
		}

		return *this;
	}

	// Assign
	List<T>& operator=(std::initializer_list<T> ilist)
	{
		for (const auto& it : ilist)
		{
			push_back(it);
		}
		return *this;
	}

private:
	iterator makeIterator(const pointer ptr)
	{
		return iterator(ptr);
	}

private:
	ListNode_t<T>* m_Head = nullptr;
	ListNode_t<T>* m_Tail = nullptr;
	size_t m_Size = 0;
};
