#pragma once

// FListNode is used for Forward List ( Forward List Node )
template<typename T>
struct FListNode
{
	FListNode(T data) : m_Data(data) {}
	~FListNode() {}

	T m_Data;
	FListNode* m_Next = nullptr;
};

template <typename T>
using FListNode_t = struct FListNode<T>;
