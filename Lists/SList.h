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

	~SList() {};

	SListNode<T>* AddToFront(T data) 
	{
		SListNode<T>* newNode = new SListNode<T>(data);

		// We are adding the first node
		if (m_Head == nullptr)
		{
			m_Head = newNode;
			m_Tail = newNode;
		}
		else
		{
			newNode->SetNext(m_Head);
			m_Head = newNode;
		}
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
		}
		else
		{
			m_Tail->SetNext(newNode);
			m_Tail = newNode;
		}
		return newNode;
	};

	void InsertAt(); // Insert new node at Index position
	void Remove(); // Remove last node
	void RemoveAt(); // Remove node at specified Index

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
};
