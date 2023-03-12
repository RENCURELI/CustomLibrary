#pragma once

// The Node class used for the List structure, these are doubly linked list
template<typename T>
struct ListNode
{
	ListNode(T data) : m_Data(data), m_Next(nullptr), m_Previous(nullptr) {}
	~ListNode() {}

	T m_Data;
	ListNode<T>* m_Next = nullptr;
	ListNode<T>* m_Previous = nullptr;
};

template <typename T>
using ListNode_t = struct ListNode<T>;