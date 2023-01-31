#pragma once
#include "SListNode.h"
#include <iostream>
#include <initializer_list>

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
	};

	~SList() 
	{
		// Go from m_Head to m_Tail and free memory
		while (m_Head != nullptr)
		{
			SListNode<T>* temp = m_Head->GetNext();
			delete m_Head;
			m_Head = temp;
		}
	};

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
	};

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
	};

	SListNode<T>* InsertAt(T data, int index) // Will want to use an iterator here, similar to standard library ???
	{
		if (m_Head == nullptr)
		{

		}
	};

	// Remove last node
	void Remove()
	{

	};

	void RemoveAt(); // Remove node at specified Index

	inline bool IsEmpty() { return m_IsEmpty; };
	inline int GetSize() { return m_Size; };

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
