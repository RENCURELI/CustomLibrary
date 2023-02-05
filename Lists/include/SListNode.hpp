#pragma once

template<typename T>
class SListNode
{
public:
	SListNode(T data) : m_Data(data) {}
	~SListNode() {}

	SListNode* GetNext() { return m_Next; }
	void SetNext(SListNode* nextNode) { m_Next = nextNode; }

	T GetData() { return m_Data; }
private:
	T m_Data;
	SListNode* m_Next = nullptr;
};

