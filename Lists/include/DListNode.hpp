#pragma once

template<typename T>
class DListNode
{
public:
	DListNode(T data) : m_Data(data) {}
	~DListNode() {}

	DListNode* GetNext() { return m_Next; }
	void SetNext(DListNode* nextNode) { m_Next = nextNode; }
	DListNode* GetPrev() { return m_Previous; }
	void SetPrev(DListNode* prevNode) { m_Previous = prevNode; }

	T GetData() { return m_Data; }
private:
	T m_Data;
	DListNode* m_Next = nullptr;
	DListNode* m_Previous = nullptr;
};