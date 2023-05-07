#pragma once
#pragma once
#include "FListNode.hpp"
#include <iostream>
#include <initializer_list>
#include <stdexcept>

template<class T>
class FList
{
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
		Clear();
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
	void Clear()
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
	FList<T>& operator=(const List<T>& other)
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
