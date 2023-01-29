#pragma once
#include "SListNode.h"
#include <iostream>
#include <vector>
#include <initializer_list>

template<class T>
class SList
{
public:
	std::vector<T> v;
	SList() {};
	SList(std::initializer_list<T> l)
	{
		for (const auto& it : l)
		{
			AddToFront(it);
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

	void AddToBack(SListNode<T>* node)
	{
		// We are adding the first node
		if (m_Head == nullptr)
		{
			m_Head = node;
			m_Tail = node;
		}
		else
		{
			m_Tail->SetNext(node);
			m_Tail = node;
		}
	};

	void InsertAt();
	void Remove();

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
