#pragma once
#pragma once
#include "FListNode.hpp"
#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <iterator>

#pragma region ConstIterator
template<typename FList>
class FListConstIterator
{
public:
	using iterator_concept = std::forward_iterator_tag;
	using value_type = typename FList::value_type;
	using pointer = FList::const_pointer;
	using reference = const value_type&;
	using difference_type = std::ptrdiff_t;

	using PtrType = typename FList::pointer;

	FListConstIterator(PtrType ptr) : m_Ptr(ptr) {}

	// preincrement
	FListConstIterator& operator++()
	{
		m_Ptr = m_Ptr->m_Next;
		return *this;
	}

	// postincrement
	FListConstIterator operator++(int)
	{
		FListConstIterator tmp = *this;
		m_Ptr = m_Ptr.m_Next;
		return tmp;
	}

	const reference operator*() const { return m_Ptr->m_Data; }
	const pointer operator->() const { return this->m_Ptr; }
	bool operator==(const FListConstIterator& other) const { return m_Ptr == other.m_Ptr; }
	bool operator!=(const FListConstIterator& other) const { return !(*this == other); }

	PtrType m_Ptr;
};
#pragma endregion ConstIterator

#pragma region Iterator
template<typename FList>
class FListIterator : public FListConstIterator<FList>
{
public:
	using value_type = typename FList::value_type;
	using pointer = FList::pointer;
	using reference = value_type&;
	using difference_type = std::ptrdiff_t;
	using BaseIt = FListConstIterator<FList>;
public:
	// preincrement
	FListIterator& operator++()
	{
		BaseIt::operator++();
		return *this;
	}

	// postincrement
	FListIterator operator++(int)
	{
		FListConstIterator tmp = *this;
		BaseIt::operator++();
		return tmp;
	}

	reference operator*() const { return const_cast<reference>(BaseIt::operator*()); }
	pointer operator->() const { return this->m_Ptr; }
	bool operator==(const FListIterator& other) const { return this->m_Ptr == other.m_Ptr; }
	bool operator!=(const FListIterator& other) const { return !(*this == other); }
};
#pragma endregion Iterator

template<class T>
class FList
{
public:
	using value_type = T;
	using pointer = FListNode_t<T>*;
	using const_pointer = const T*;
	using iterator = FListIterator<FList<T>>;
	using const_iterator = FListConstIterator<FList<T>>;

public:
	FList() {};
	FList(std::initializer_list<T> l)
	{
		for (const auto& it : l)
		{
			push_front(it);
		}
	}

	FList(const FList& other)
	{
		FListNode_t<T>* temp = other.m_Head;
		while (temp != nullptr)
		{
			this->push_front(temp->m_Data);
			temp = temp->m_Next;
		}
	}

	~FList()
	{
		clear();
	}

	FListNode_t<T>* push_front(T data)
	{
		FListNode_t<T>* newNode = new FListNode_t<T>(data);

		// We are adding the first node
		if (m_Head == nullptr)
		{
			m_Head = newNode;
		}
		else
		{
			newNode->m_Next = m_Head;
			m_Head = newNode;
		}
		m_Size++;
		return newNode;
	}

	FListNode_t<T>* insert(T data, int index)
	{
		CheckIndex(index, true);
		FListNode_t<T>* newNode = new FListNode_t<T>(data);

		// Empty list case handled by creating first element
		if (m_Head == nullptr)
		{
			m_Head = newNode;
		}
		else
		{
			// Start by handling Head node case
			// We insert at index 0, specific behaviour
			if (index == 0)
			{
				newNode->m_Next = m_Head;
				m_Head = newNode;
			}
			else
			{
				FListNode_t<T>* prevNode = AdvanceTo(index - 1);
				newNode->m_Next = prevNode->m_Next;
				prevNode->m_Next = newNode;
			}
		}

		m_Size++;
		return newNode;
	}

	void pop_front()
	{
		if (m_Size == 0)
			return;

		if (m_Size == 1)
		{
			delete m_Head;
			m_Head = nullptr;
		}
		else
		{
			FListNode_t<T>* newHead = m_Head->m_Next;
			delete m_Head;
			m_Head = newHead;
		}

		m_Size--;
	}

	// Remove node at specified Index
	void remove(int index)
	{
		CheckIndex(index);
		if (index == 0)
		{
			FListNode_t<T>* currHead = m_Head;
			m_Head = m_Head->m_Next;
			delete currHead;
		}
		else
		{
			FListNode_t<T>* prevNode = AdvanceTo(index - 1);
			FListNode_t<T>* nodeToDel = AdvanceTo(index);
			prevNode->m_Next = nodeToDel->m_Next;
			delete nodeToDel;
		}

		m_Size--;
	}

	// Clear the content of the List
	void clear()
	{
		// Go from m_Head to m_Tail and free memory
		while (m_Head != nullptr)
		{
			FListNode_t<T>* temp = m_Head->m_Next;
			delete m_Head;
			m_Head = temp;
		}

		m_Size = 0;
		m_Head = nullptr;
	}

	inline bool empty() const { return m_Size == 0; }
	inline int size() const { return m_Size; }
	inline const T& front() const { return m_Size > 0 ? m_Head->m_Data : throw std::runtime_error("[ERROR] Trying to access and empty list"); }
	inline T& front() { return m_Size > 0 ? m_Head->m_Data : throw std::runtime_error("[ERROR] Trying to access and empty list"); }
	inline iterator begin() { return iterator(m_Head); }
	inline const_iterator cbegin() const { return const_iterator(m_Head); }
	inline iterator end() { return iterator(nullptr); }
	inline const_iterator cend() const { return const_iterator(nullptr); }

	void PrintList()
	{
		FListNode_t<T>* current = m_Head;
		while (current != nullptr)
		{
			std::cout << " -> " << current->m_Data;
			current = current->m_Next;
		}
	}

	// Copy
	FList<T>& operator=(const FList<T>& other)
	{
		if (this == &other)
			return *this;

		FListNode_t<T>* temp = other.front();
		while (temp != nullptr)
		{
			this->push_front(temp->m_Data);
			temp = temp->m_Next;
		}

		return *this;
	}

	// Assign
	FList<T>& operator=(std::initializer_list<T> ilist)
	{
		for (const auto& it : ilist)
		{
			push_front(it);
		}
		return *this;
	}

private:
	FListNode_t<T>* m_Head = nullptr;
	int m_Size = 0;

	FListNode_t<T>* AdvanceTo(int index) const
	{
		// If we are accessing already allocated values, return those
		if (index == 0)
			return m_Head;
		else
		{
			// Loop within the list to find the proper element
			FListNode_t<T>* prevNode = m_Head;
			int i = 0;

			do
			{
				prevNode = prevNode->m_Next;
				++i;
			} while (i < index);

			return prevNode;
		}
	}

	// AllowExtra is to allow using InsertAt the same way as AddToBack
	bool CheckIndex(const int index, bool allowExtra = false)
	{
		if (allowExtra)
		{
			if (index < 0 || index > m_Size)
			{
				throw std::runtime_error("[ERROR] : Index Out of Bounds.");
				return false;
			}
		}
		else if (index < 0 || index > m_Size - 1)
		{
			throw std::runtime_error("[ERROR] : Index Out of Bounds.");
			return false;
		}

		return true;
	}
};
