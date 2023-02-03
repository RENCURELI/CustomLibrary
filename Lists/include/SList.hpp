#pragma once
#include "SListNode.hpp"
#include <iostream>
#include <initializer_list>
#include <assert.h>

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
		assert(index >= 0);
		auto* newNode = new SListNode<T>(data);

		// We will handle out of bound indices by pushing back
		// Negative indices will return an error
		// Empty list case handled by creating first element
		if (m_Head == nullptr)
		{
			m_Head = newNode;
			m_Tail = newNode;
			m_IsEmpty = false;
		}

		return newNode;
	}

	// Remove last node
	void Remove()
	{
		// Loop through List content until current node next pointer is tail
		// Delete data at tail and set tail as current ndoe
	}

	void RemoveAt() {} // Remove node at specified Index

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
};
