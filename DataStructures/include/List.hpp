#pragma once
#include "ListNode.hpp"
#include <iostream>
#include <initializer_list>
#include <stdexcept>

// Update to also set prevNode pointer as this is doubly linked list

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

	~List()
	{
		Clear();
	}

	ListNode<T>* push_front(T data)
	{
		ListNode<T>* newNode = new ListNode<T>(data);

		// We are adding the first node
		if (m_Head == nullptr)
		{
			m_Head = newNode;
			m_Tail = newNode;
			m_IsEmpty = false;
		}
		else
		{
			newNode->SetNext(m_Head);
			m_Head->SetPrev(newNode);
			m_Head = newNode;
		}
		m_Size++;
		return newNode;
	}

	ListNode<T>* push_back(T data)
	{
		ListNode<T>* newNode = new ListNode<T>(data);

		// We are adding the first node
		if (m_Head == nullptr)
		{
			m_Head = newNode;
			m_Tail = newNode;
			m_IsEmpty = false;
		}
		else
		{
			m_Tail->SetNext(newNode);
			newNode->SetPrev(m_Tail);
			m_Tail = newNode;
		}
		m_Size++;
		return newNode;
	}

	ListNode<T>* InsertAt(T data, int index)
	{
		CheckIndex(index, true);
		ListNode<T>* newNode = new ListNode<T>(data);

		// Empty list case handled by creating first element
		if (m_Head == nullptr)
		{
			m_Head = newNode;
			m_Tail = newNode;
			m_IsEmpty = false;
		}
		else
		{
			// We insert at index 0, specific behaviour
			if (index == 0)
			{
				newNode->SetNext(m_Head);
				m_Head = newNode;
			}
			else if (index == m_Size)
			{
				m_Tail->SetNext(newNode);
				newNode->SetPrev(m_Tail);
				m_Tail = newNode;
			}
			else
			{
				ListNode<T>* prevNode = AdvanceTo(index - 1);
				newNode->SetNext(prevNode->GetNext());
				prevNode->SetNext(newNode);
			}
		}

		m_Size++;
		return newNode;
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
			m_IsEmpty = true;
		}
		else if (m_Size > 1)
		{
			ListNode<T>* newTail = m_Tail->GetPrev();
			newTail->SetNext(nullptr);
			delete m_Tail;
			m_Tail = newTail;
		}

		m_Size--;
	}

	// Remove first ndoe
	void pop_front()
	{
		if (m_Size == 0)
			return;

		if (m_Size == 1)
		{
			delete m_Head;
			m_Head = nullptr;
			m_Tail = nullptr;
			m_IsEmpty = true;
		}
		else if (m_Size > 1)
		{
			ListNode<T>* newHead = m_Head->GetNext();
			newHead->SetPrev(nullptr);
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
			ListNode<T>* currHead = m_Head;
			m_Head = m_Head->GetNext();
			delete currHead;
		}
		else if (index == m_Size - 1)
		{
			//ListNode<T>* newTail = AdvanceTo(index - 1);
			ListNode<T>* newTail = m_Tail->GetPrev();
			m_Tail = newTail;
			delete m_Tail->GetNext();
			m_Tail->SetNext(nullptr);
		}
		else
		{
			ListNode<T>* nodeToDel = AdvanceTo(index);
			nodeToDel->GetPrev()->SetNext(nodeToDel->GetNext());
			nodeToDel->GetNext()->SetPrev(nodeToDel->GetPrev());
			delete nodeToDel;
		}

		m_Size--;
		if (m_Size == 0)
			m_IsEmpty = true;
	}

	// Clear the content of the List
	void Clear()
	{
		// Go from m_Head to m_Tail and free memory
		while (m_Head != nullptr)
		{
			ListNode<T>* temp = m_Head->GetNext();
			delete m_Head;
			m_Head = temp;
		}

		m_Size = 0;
		m_Head = nullptr;
		m_Tail = nullptr;
		m_IsEmpty = true;
	}

	inline bool IsEmpty() const { return m_IsEmpty; }
	inline int GetSize() const { return m_Size; }
	inline ListNode<T>* front() const { return m_Head; }
	inline ListNode<T>* back() const { return m_Tail; }

	void PrintList()
	{
		ListNode<T>* current = m_Head;
		while (current != nullptr)
		{
			std::cout << " -> " << current->GetData();
			current = current->GetNext();
		}
	}

	List<T>& operator=(const List<T>& other)
	{
		if (this == &other)
			return *this;

		ListNode<T>* temp = other.front();
		while (temp != nullptr)
		{
			this->push_back(temp->GetData());
			temp = temp->GetNext();
		}

		return *this;
	}

	List<T>& operator=(std::initializer_list<T> ilist)
	{
		for (const auto& it : ilist)
		{
			push_back(it);
		}
		return *this;
	}

private:
	ListNode<T>* m_Head = nullptr;
	ListNode<T>* m_Tail = nullptr;
	bool m_IsEmpty = true;
	int m_Size = 0;

	ListNode<T>* AdvanceTo(int index) const
	{
		// If we are accessing already allocated values, return those
		if (index == 0)
			return m_Head;
		else if (index == m_Size - 1)
			return m_Tail;
		else
		{
			// Loop within the list to find the proper element
			ListNode<T>* prevNode = m_Head;
			int i = 0;

			do
			{
				prevNode = prevNode->GetNext();
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
