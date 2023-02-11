#pragma once

// FListNode is used for Forward List ( Forward List Node )
template<typename T>
class FListNode
{
public:
	FListNode(T data) : m_Data(data) {}
	~FListNode() {}

	FListNode* GetNext() { return m_Next; }
	void SetNext(FListNode* nextNode) { m_Next = nextNode; }

	T GetData() { return m_Data; }
private:
	T m_Data;
	FListNode* m_Next = nullptr;
};

