#pragma once
#include "ListNode.hpp"
#include <iostream>
#include <initializer_list>
#include <stdexcept>

template<class T>
class List
{
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
		Clear();
	}

	//ListNode_t<T>* push_front(T data)
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
		//return newNode;
	}

	//ListNode_t<T>* push_back(T data)
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
		//return newNode;
	}

	//ListNode_t<T>* InsertAt(T data, int index)
	void InsertAt(T data, int index)
	{
		CheckIndex(index, true);
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
			if (index == 0)
			{
				newNode->m_Next = m_Head;
				m_Head = newNode;
			}
			else if (index == m_Size)
			{
				m_Tail->m_Next = newNode;
				newNode->m_Previous = m_Tail;
				m_Tail = newNode;
			}
			else
			{
				ListNode_t<T>* prevNode = AdvanceTo(index - 1);
				newNode->m_Next = prevNode->m_Next;
				prevNode->m_Next = newNode;
			}
		}

		m_Size++;
		//return newNode;
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
	void RemoveAt(int index)
	{
		CheckIndex(index);
		if (index == 0)
		{
			ListNode_t<T>* currHead = m_Head;
			m_Head = m_Head->m_Next;
			delete currHead;
		}
		else if (index == m_Size - 1)
		{
			ListNode_t<T>* newTail = m_Tail->m_Previous;
			m_Tail = newTail;
			delete m_Tail->m_Next;
			m_Tail->m_Next = nullptr;
		}
		else
		{
			ListNode_t<T>* nodeToDel = AdvanceTo(index);
			nodeToDel->m_Previous->m_Next = nodeToDel->m_Next;
			nodeToDel->m_Next->m_Previous = nodeToDel->m_Previous;
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
			ListNode_t<T>* temp = m_Head->m_Next;
			delete m_Head;
			m_Head = temp;
		}

		m_Size = 0;
		m_Head = nullptr;
		m_Tail = nullptr;
	}

	inline bool empty() const { return m_Size == 0; }
	inline int size() const { return m_Size; }
	inline T& front() { return m_Size > 0 ? m_Head->m_Data : throw std::runtime_error("[ERROR] Trying to access and empty list"); }
	inline const T& front() const { return m_Size > 0 ? m_Head->m_Data : throw std::runtime_error("[ERROR] Trying to access and empty list"); }
	inline T& back() { return m_Size > 0 ? m_Tail->m_Data : throw std::runtime_error("[ERROR] Trying to access and empty list"); }
	inline const T& back() const { return m_Size > 0 ? m_Tail->m_Data : throw std::runtime_error("[ERROR] Trying to access and empty list"); }

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
	ListNode_t<T>* m_Head = nullptr;
	ListNode_t<T>* m_Tail = nullptr;
	int m_Size = 0;

	ListNode_t<T>* AdvanceTo(int index) const
	{
		// If we are accessing already allocated values, return those
		if (index == 0)
			return m_Head;
		else if (index == m_Size - 1)
			return m_Tail;
		else
		{
			// Loop within the list to find the proper element
			ListNode_t<T>* prevNode = m_Head;
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
