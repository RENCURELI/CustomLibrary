#pragma once

template<typename T>
class SListNode
{
public:
	SListNode(T data) { m_Data = data; };
	~SListNode() {};

private:
	SListNode* m_Next = nullptr;
	T m_Data;
};

