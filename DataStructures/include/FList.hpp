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

	~FList()
	{
		Clear();
	}

	FListNode<T>* push_front(T data)
	{
		FListNode<T>* newNode = new FListNode<T>(data);

		// We are adding the first node
		if (m_Head == nullptr)
		{
			m_Head = newNode;
		}
		else
		{
			newNode->SetNext(m_Head);
			m_Head = newNode;
		}
		m_Size++;
		return newNode;
	}

	FListNode<T>* InsertAt(T data, int index)
	{
		CheckIndex(index, true);
		FListNode<T>* newNode = new FListNode<T>(data);

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
				newNode->SetNext(m_Head);
				m_Head = newNode;
			}
			else
			{
				FListNode<T>* prevNode = AdvanceTo(index - 1);
				newNode->SetNext(prevNode->GetNext());
				prevNode->SetNext(newNode);
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
			FListNode<T>* newHead = m_Head->GetNext();
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
			FListNode<T>* currHead = m_Head;
			m_Head = m_Head->GetNext();
			delete currHead;
		}
		else
		{
			FListNode<T>* prevNode = AdvanceTo(index - 1);
			FListNode<T>* nodeToDel = AdvanceTo(index);
			prevNode->SetNext(nodeToDel->GetNext());
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
			FListNode<T>* temp = m_Head->GetNext();
			delete m_Head;
			m_Head = temp;
		}

		m_Size = 0;
		m_Head = nullptr;
	}

	//inline bool IsEmpty() const { return m_IsEmpty = m_Size == 0; }
	inline bool IsEmpty() const { return m_Size == 0; }
	inline int GetSize() const { return m_Size; }
	inline FListNode<T>* front() const { return m_Head; }

	void PrintList()
	{
		FListNode<T>* current = m_Head;
		while (current != nullptr)
		{
			std::cout << " -> " << current->GetData();
			current = current->GetNext();
		}
	}

	FList<T>& operator=(const List<T>& other)
	{
		if (this == &other)
			return *this;

		FListNode<T>* temp = other.front();
		while (temp != nullptr)
		{
			this->push_front(temp->GetData());
			temp = temp->GetNext();
		}

		return *this;
	}

	FList<T>& operator=(std::initializer_list<T> ilist)
	{
		for (const auto& it : ilist)
		{
			push_front(it);
		}
		return *this;
	}

private:
	FListNode<T>* m_Head = nullptr;
	//bool m_IsEmpty = true;
	int m_Size = 0;

	FListNode<T>* AdvanceTo(int index) const
	{
		// If we are accessing already allocated values, return those
		if (index == 0)
			return m_Head;
		else
		{
			// Loop within the list to find the proper element
			FListNode<T>* prevNode = m_Head;
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
