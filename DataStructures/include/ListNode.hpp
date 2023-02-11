#pragma once

// The Node class used for the List structure, these are doubly linked list
template<typename T>
class ListNode
{
public:
	ListNode(T data) : m_Data(data) {}
	~ListNode() {}

	ListNode* GetNext() { return m_Next; }
	void SetNext(ListNode* nextNode) { m_Next = nextNode; }
	ListNode* GetPrev() { return m_Previous; }
	void SetPrev(ListNode* prevNode) { m_Previous = prevNode; }

	T GetData() { return m_Data; }
private:
	T m_Data;
	ListNode* m_Next = nullptr;
	ListNode* m_Previous = nullptr;
};