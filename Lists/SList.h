#pragma once
#include "SListNode.h"

template<class T>
class SList
{
public:
	SList() {};
	~SList() {};

	void AddToFront();
	void AddToBack();
	void InsertAt();
	void Remove();

private:
	SListNode<T>* m_Head = nullptr;
	SListNode<T>* m_Tail = nullptr;
};

