#pragma once
#include "SListNode.hpp"
#include <iostream>
#include <initializer_list>
#include <stdexcept>

template<class T>
class SList
{
public:
	SList() {};
	SList(std::initializer_list<T> l)
	{
		for (const auto& it : l)
		{
			AddToBack(it);
		}
	}

	~SList() 
	{
		// Go from m_Head to m_Tail and free memory
		while (m_Head != nullptr)
		{
			SListNode<T>* temp = m_Head->GetNext();
			delete m_Head;
			m_Head = temp;
		}
	}

	// Keeping for reference when implementing DoublyLinked List and Forward List
	SListNode<T>* AddToFront(T data) 
	{
		SListNode<T>* newNode = new SListNode<T>(data);

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
			m_Head = newNode;
		}
		m_Size++;
		return newNode;
	}

	SListNode<T>* AddToBack(T data)
	{
		SListNode<T>* newNode = new SListNode<T>(data);

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
			m_Tail = newNode;
		}
		m_Size++;
		return newNode;
	}

	SListNode<T>* InsertAt(T data, int index) // Will want to use an iterator here, similar to standard library ???
	{
		//assert(index >= 0 && index <= m_Size); // We assert that we pass a valid index
		CheckIndex(index, true);
		SListNode<T>* newNode = new SListNode<T>(data);

		// Empty list case handled by creating first element
		if (m_Head == nullptr)
		{
			m_Head = newNode;
			m_Tail = newNode;
			m_IsEmpty = false;
		}
		else
		{
			// Start by handling Head node case
			// We insert at index 0, specific behaviour
			if (index == 0)
			{
				newNode->SetNext(m_Head);
				m_Head = newNode;
			}
			else if (index == m_Size)
			{
				m_Tail->SetNext(newNode);
				m_Tail = newNode;
			}
			else
			{
				SListNode<T>* prevNode = AdvanceTo(index - 1);
				newNode->SetNext(prevNode->GetNext());
				prevNode->SetNext(newNode);
			}
		}

		m_Size++;
		return newNode;
	}

	// Remove last node
	void Remove()
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
			// We go to the second to last element
			SListNode<T>* newTail = AdvanceTo(m_Size - 2);
			newTail->SetNext(nullptr);
			delete m_Tail;
			m_Tail = newTail;
		}

		m_Size--;
	}

	// Remove node at specified Index
	void RemoveAt(int index)
	{
		CheckIndex(index);
		if (index == 0)
		{
			SListNode<T>* currHead = m_Head;
			m_Head = m_Head->GetNext();
			delete currHead;
		}
		else if (index == m_Size - 1)
		{
			SListNode<T>* newTail = AdvanceTo(index - 1);
			m_Tail = newTail;
			delete m_Tail->GetNext();
			m_Tail->SetNext(nullptr);
		}
		else
		{
			SListNode<T>* prevNode = AdvanceTo(index - 1);
			SListNode<T>* nodeToDel = AdvanceTo(index);
			prevNode->SetNext(nodeToDel->GetNext());
			delete nodeToDel;
		}

		m_Size--;
		if (m_Size == 0)
			m_IsEmpty = true;
	}

	inline bool IsEmpty() { return m_IsEmpty; }
	inline int GetSize() { return m_Size; }

	void PrintList()
	{
		SListNode<T>* current = m_Head;
		while (current != nullptr)
		{
			std::cout << " -> " << current->GetData();
			current = current->GetNext();
		}
	}

private:
	SListNode<T>* m_Head = nullptr;
	SListNode<T>* m_Tail = nullptr;
	bool m_IsEmpty = true;
	int m_Size = 0;

	SListNode<T>* AdvanceTo(int index) const
	{
		// If we are accessing already allocated values, return those
		if (index == 0)
			return m_Head;
		else if (index == m_Size - 1)
			return m_Tail;
		else
		{
			// Loop within the list to find the proper element
			SListNode<T>* prevNode = m_Head;
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
	void CheckIndex(const int index, bool allowExtra = false)
	{
		if (allowExtra)
		{
			if (index < 0 || index > m_Size)
				throw std::runtime_error("[ERROR] : Index Out of Bounds.");
		}
		else if (index < 0 || index > m_Size - 1)
			throw std::runtime_error("[ERROR] : Index Out of Bounds.");
	}
};
