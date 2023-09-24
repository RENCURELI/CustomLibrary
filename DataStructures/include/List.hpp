#pragma once
#include "ListNode.hpp"
#include <compare>
#include <initializer_list>
#include <stdexcept>
#include <iterator>
#include <utility>

#pragma region ConstIterator
template<typename List>
class ListConstIterator
{
public:
	using iterator_concept = std::bidirectional_iterator_tag;
	using value_type = typename List::value_type;
	using pointer = typename List::const_pointer;
	using reference = const value_type&;
	using difference_type = std::ptrdiff_t;

	using PtrType = typename List::pointer;

	ListConstIterator(PtrType ptr) : m_Ptr(ptr) {}

	// preincrement
	ListConstIterator& operator++()
	{
		m_Ptr = m_Ptr->m_Next;
		return *this;
	}

	// postincrement
	ListConstIterator operator++(int)
	{
		ListConstIterator tmp = *this;
		m_Ptr = m_Ptr.m_Next;
		return tmp;
	}

	// preincrement
	ListConstIterator& operator--()
	{
		m_Ptr = m_Ptr->m_Previous;
		return *this;
	}

	// postincrement
	ListConstIterator operator--(int)
	{
		ListConstIterator tmp = *this;
		m_Ptr = m_Ptr.m_Previous;
		return tmp;
	}

	const reference operator*() const { return m_Ptr->m_Data; }
	const pointer operator->() const { return this->m_Ptr; }
	bool operator==(const ListConstIterator& other) const { return m_Ptr == other.m_Ptr; }
	bool operator!=(const ListConstIterator& other) const { return !(*this == other); }

	PtrType m_Ptr;
};

#pragma endregion ConstIterator

#pragma region Iterator
template<typename List>
class ListIterator : public ListConstIterator<List>
{
public:
	using value_type = typename List::value_type;
	using pointer = typename List::pointer;
	using reference = value_type&;
	using difference_type = std::ptrdiff_t;
	using BaseIt = ListConstIterator<List>;
public:
	// preincrement
	ListIterator& operator++()
	{
		BaseIt::operator++();
		return *this;
	}

	// postincrement
	ListIterator operator++(int)
	{
		ListIterator tmp = *this;
		BaseIt::operator++();
		return tmp;
	}

	// preincrement
	ListIterator& operator--()
	{
		BaseIt::operator--();
		return *this;
	}

	// postincrement
	ListIterator operator--(int)
	{
		ListIterator tmp = *this;
		BaseIt::operator--();
		return tmp;
	}

	reference operator*() const { return const_cast<reference>(BaseIt::operator*()); }
	pointer operator->() const { return this->m_Ptr; }
	bool operator==(const ListIterator& other) const { return this->m_Ptr == other.m_Ptr; }
	bool operator!=(const ListIterator& other) const { return !(*this == other); }

};
#pragma endregion Iterator

template<typename T>
bool operator==(const ListIterator<T>& lhs, const ListConstIterator<T>& rhs) { return lhs.m_Ptr == rhs.m_Ptr; }

template<class T>
class List
{
public:
	using value_type = T;
	using pointer = ListNode_t<T>*;
	using const_pointer = const T*;
	using iterator = ListIterator<List<T>>;
	using const_iterator = ListConstIterator<List<T>>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

public:
	List() {};

	List(size_t count, const T& value)
	{
		for (; count > 0; --count)
		{
			push_back(value);
		}
	}

	List(size_t count)
	{
		for (; count > 0; --count)
		{
			push_back(T());
		}
	}

	template<std::input_iterator InputIt>
	List(InputIt first, InputIt last)
	{
		for (; first != last; ++first)
		{
			push_back(*first);
		}
	}

	List(std::initializer_list<T> l)
	{
		for (const auto& it : l)
		{
			push_back(it);
		}
	}

	List(const List& other)
	{
		ListNode_t<T>* temp = other.m_Head;
		while (temp != nullptr)
		{
			this->push_back(temp->m_Data);
			temp = temp->m_Next;
		}
	}

	List(List<T>&& other)
	{
		std::swap(this->m_Head, other.m_Head);
		std::swap(this->m_Tail, other.m_Tail);
		std::swap(this->m_Size, other.m_Size);
	}

	~List()
	{
		clear();
	}

	void push_front(T data)
	{
		ListNode_t<T>* newNode = new ListNode_t<T>(data);

		// We are adding the first node
		if (m_Head == nullptr)
		{
			m_Head = newNode;
			m_Tail = newNode;
		}
		else
		{
			newNode->m_Next = m_Head;
			m_Head->m_Previous = newNode;
			m_Head = newNode;
		}
		m_Size++;
	}

	void push_back(T data)
	{
		ListNode_t<T>* newNode = new ListNode_t<T>(data);

		// We are adding the first node
		if (m_Head == nullptr)
		{
			m_Head = newNode;
			m_Tail = newNode;
		}
		else
		{
			m_Tail->m_Next = newNode;
			newNode->m_Previous = m_Tail;
			m_Tail = newNode;
		}
		m_Size++;
	}

	iterator insert(const_iterator pos, const T& data)
	{
		ListNode_t<T>* newNode = new ListNode_t<T>(data);

		// Empty list case handled by creating first element
		if (m_Head == nullptr)
		{
			m_Head = newNode;
			m_Tail = newNode;
		}
		else
		{
			// We insert at index 0, specific behaviour
			if (pos == cbegin())
			{
				newNode->m_Next = m_Head;
				m_Head->m_Previous = newNode;
				m_Head = newNode;
			}
			else if (pos == cend())
			{
				m_Tail->m_Next = newNode;
				newNode->m_Previous = m_Tail;
				m_Tail = newNode;
			}
			else
			{
				ListNode_t<T>* prevNode = pos.m_Ptr->m_Previous;
				newNode->m_Next = prevNode->m_Next;
				newNode->m_Previous = prevNode;
				prevNode->m_Next = newNode;
			}
		}

		m_Size++;
		return makeIterator(pos.m_Ptr);
	}

	iterator insert(const_iterator pos, size_t count, const T& data)
	{
		iterator returnVal = makeIterator(pos.m_Ptr);

		// No insertion
		if (count == 0)
		{
			return returnVal;
		}
		
		if (m_Head == nullptr)
		{
			for (; count > 0; --count)
			{
				push_back(data);
			}
			return begin();
		}
		else
		{
			ListNode_t<T>* newNode = new ListNode_t<T>(data);
			returnVal = makeIterator(newNode);

			for (int i = 0; i <= count; ++i)
			{
				if (pos == cbegin())
				{
					newNode->m_Next = m_Head;
					m_Head->m_Previous = newNode;
					m_Head = newNode;
				}
				else if (pos == cend())
				{
					m_Tail->m_Next = newNode;
					newNode->m_Previous = m_Tail;
					m_Tail = newNode;
				}
				else
				{
					ListNode_t<T>* prevNode = pos.m_Ptr->m_Previous;
					newNode->m_Next = prevNode->m_Next;
					newNode->m_Previous = prevNode;
					prevNode->m_Next = newNode;
				}

				newNode = new ListNode_t<T>(data);
			}
		}

		m_Size += count;
		return returnVal;
	}

	// inserts [first last)
	template<std::input_iterator InputIt>
	iterator insert(const_iterator pos, InputIt first, InputIt last)
	{
		iterator returnVal = makeIterator(pos.m_Ptr);

		if (first == last)
		{
			return returnVal;
		}

		if (m_Head == nullptr)
		{
			for (; first != last; ++first)
			{
				push_back(first.m_Ptr->m_Data);
			}
			return begin();
		}
		else
		{
			returnVal = first;
			int i = 0;
			for (; first != last; ++first)
			{
				ListNode_t<T>* newNode = new ListNode_t<T>(first.m_Ptr->m_Data);
				if (pos == cbegin() && i == 0)
				{
					newNode->m_Next = m_Head;
					m_Head->m_Previous = newNode;
					m_Head = newNode;
				}
				else if (pos == cend())
				{
					m_Tail->m_Next = newNode;
					newNode->m_Previous = m_Tail;
					m_Tail = newNode;
				}
				else
				{
					pos.m_Ptr->m_Previous->m_Next = newNode;
					newNode->m_Previous = pos.m_Ptr->m_Previous;
					newNode->m_Next = pos.m_Ptr;
					pos.m_Ptr->m_Previous = newNode;
				}

				if (i == 0)
				{
					returnVal = makeIterator(newNode);
				}

				++i;
				++m_Size;
			}
			return returnVal;
		}

	}

	iterator insert(const_iterator pos, std::initializer_list<T> ilist)
	{
		if (ilist.size() == 0)
			return makeIterator(pos.m_Ptr);

		iterator returnVal = makeIterator(pos.m_Ptr);

		if (m_Head == nullptr)
		{
			for (const auto& it : ilist)
			{
				push_back(it);
			}
			return begin();
		}
		else if (pos == cend())
		{
			int i = 0;
			for (const auto& it : ilist)
			{
				ListNode_t<T>* newNode = new ListNode_t<T>(it);
				m_Tail->m_Next = newNode;
				newNode->m_Previous = m_Tail;
				m_Tail = newNode;

				if (i == 0)
				{
					returnVal = makeIterator(newNode);
				}
				++i;
			}

			m_Size += ilist.size();
			return returnVal;
		}
		else
		{
			int i = 0;
			for (const auto& it : ilist)
			{
				ListNode_t<T>* newNode = new ListNode_t<T>(it);
				pos.m_Ptr->m_Previous->m_Next = newNode;
				newNode->m_Previous = pos.m_Ptr->m_Previous;
				newNode->m_Next = pos.m_Ptr;
				pos.m_Ptr->m_Previous = newNode;

				if (i == 0)
				{
					returnVal = makeIterator(newNode);
				}
				++i;
			}

			m_Size += ilist.size();
			return returnVal;
		}
	}

	// Remove last node
	void pop_back()
	{
		if (m_Size == 0)
			return;

		if (m_Size == 1)
		{
			delete m_Tail;
			m_Head = nullptr;
			m_Tail = nullptr;
		}
		else if (m_Size > 1)
		{
			ListNode_t<T>* newTail = m_Tail->m_Previous;
			newTail->m_Next = nullptr;
			delete m_Tail;
			m_Tail = newTail;
		}

		m_Size--;
	}

	// Remove first node
	void pop_front()
	{
		if (m_Size == 0)
			return;

		if (m_Size == 1)
		{
			delete m_Head;
			m_Head = nullptr;
			m_Tail = nullptr;
		}
		else if (m_Size > 1)
		{
			ListNode_t<T>* newHead = m_Head->m_Next;
			newHead->m_Previous = nullptr;
			delete m_Head;
			m_Head = newHead;
		}

		m_Size--;
	}

	// Remove node at specified Index
	iterator erase(const_iterator pos)
	{
		iterator returnedIt = makeIterator(pos.m_Ptr->m_Next);
		if (pos == begin())
		{
			ListNode_t<T>* currHead = m_Head;
			m_Head = m_Head->m_Next;
			delete currHead;
		}
		else if (pos == makeIterator(m_Tail))
		{
			ListNode_t<T>* newTail = m_Tail->m_Previous;
			m_Tail = newTail;
			delete m_Tail->m_Next;
			m_Tail->m_Next = nullptr;
		}
		else
		{
			ListNode_t<T>* nodeToDel = pos.m_Ptr;
			nodeToDel->m_Previous->m_Next = nodeToDel->m_Next;
			nodeToDel->m_Next->m_Previous = nodeToDel->m_Previous;
			delete nodeToDel;
		}

		m_Size--;
		return returnedIt;
	}

	// Removes in range [First, Last)
	iterator erase(const_iterator first, const_iterator last)
	{
		if (first == last)
		{
			return makeIterator(last.m_Ptr);
		}
		else
		{
			do
			{
				ListNode_t<T>* nodeToDel = first.m_Ptr;
				first.m_Ptr = nodeToDel->m_Next;
				first.m_Ptr->m_Previous = nodeToDel->m_Previous;
				nodeToDel->m_Previous->m_Next = first.m_Ptr;
				delete nodeToDel;
				m_Size--;
			} while (first.m_Ptr != last.m_Ptr);

			return makeIterator(last.m_Ptr);
		}
	}

	// Clear the content of the List
	void clear()
	{
		// Go from m_Head to m_Tail and free memory
		while (m_Head != nullptr)
		{
			ListNode_t<T>* temp = m_Head->m_Next;
			delete m_Head;
			m_Head = temp;
		}

		m_Size = 0;
		m_Head = nullptr;
		m_Tail = nullptr;
	}

	void splice(const_iterator pos, List<T>&& other)
	{
		if (pos == nullptr)
		{
			return;
		}

		if (std::addressof(other) == this || other.size() == 0)
		{
			return;
		}

		pos.m_Ptr->m_Previous->m_Next = other.m_Head;
		other.m_Head->m_Previous = pos.m_Ptr->m_Previous;
		other.m_Tail->m_Next = pos.m_Ptr;

		other.m_Head = nullptr;
		other.m_Tail = nullptr;
		m_Size += other.m_Size;
		other.m_Size = 0;
	}

	void splice(const_iterator pos, List<T>&& other, const_iterator it)
	{

	}

	void splice(const_iterator pos, List<T>&& other, const_iterator first, const_iterator last)
	{

	}

	template<class Compare>
	void merge(List<T>&& other, Compare comp)
	{
		if (other == *this)
		{
			return;
		}

		auto it = begin();
		for (; it != end(); ++it)
		{
			if (other.empty())
			{
				break;
			}

			ListNode<T>* newHead = other.m_Head->m_Next;
			if (comp(it.m_Ptr, other.m_Head))
			{
				other.m_Head->m_Next = it.m_Ptr->m_Next;
				it.m_Ptr->m_Next = other.m_Head;
				other.m_Head->m_Previous = it.m_Ptr;

			}
			else
			{
				other.m_Head->m_Next = it.m_Ptr;
				other.m_Head->m_Previous = it.m_Ptr->m_Previous;

				if (it.m_Ptr->m_Previous != nullptr)
				{
					it.m_Ptr->m_Previous->m_Next = other.m_Head;
				}
			}

			--other.m_Size;
			++m_Size;
			other.m_Head = newHead;
		}

		// append any leftovers to this
		if (!other.empty())
		{
			m_Tail->m_Next = other.m_Head;
		}

		m_Size += other.size();
	}

	void merge(List<T>&& other)
	{
		merge(std::move(other), std::less<>{});
	}

	// Merge sort the list
	template<class Compare>
	void sort(Compare comp)
	{
		//MergeSort(&m_Head, m_Size, comp);
	}

	void sort()
	{
		sort(std::less<>{});
	}

	template<class BinaryPredicate>
	void unique(BinaryPredicate p)
	{
		if (empty())
		{
			return;
		}

		iterator current = begin();
		for (; current != end();)
		{
			ListNode<T>* curNode = current.m_Ptr;
			if (curNode->m_Next != nullptr && p(curNode->m_Data, curNode->m_Next->m_Data))
			{
				curNode->m_Next = curNode->m_Next->m_Next;
				delete curNode->m_Next->m_Previous;
				curNode->m_Next->m_Previous = curNode;
				--m_Size;
			}
			else
			{
				++current;
			}
		}
	}

	void unique()
	{
		unique(std::equal_to<>{});
	}

	inline bool empty() const { return m_Size == 0; }
	inline size_t size() const { return m_Size; }
	inline T& front() { return m_Size > 0 ? m_Head->m_Data : throw std::runtime_error("[ERROR] Trying to access an empty list"); }
	inline const T& front() const { return m_Size > 0 ? m_Head->m_Data : throw std::runtime_error("[ERROR] Trying to access an empty list"); }
	inline T& back() { return m_Size > 0 ? m_Tail->m_Data : throw std::runtime_error("[ERROR] Trying to access an empty list"); }
	inline const T& back() const { return m_Size > 0 ? m_Tail->m_Data : throw std::runtime_error("[ERROR] Trying to access an empty list"); }
	inline iterator begin() { return iterator(m_Head); }
	inline const_iterator cbegin() const { return const_iterator(m_Head); }
	inline reverse_iterator rbegin() { return reverse_iterator(end()); }
	inline const_reverse_iterator crbegin() const { return const_reverse_iterator(cend()); }
	inline iterator end() { return iterator(nullptr); }
	inline const_iterator cend() const { return const_iterator(nullptr); }
	inline reverse_iterator rend() { return reverse_iterator(begin()); }
	inline const_reverse_iterator crend() const { return const_reverse_iterator(cbegin()); }

	// Copy
	List<T>& operator=(const List<T>& other)
	{
		if (this == &other)
			return *this;

		clear();

		ListNode_t<T>* temp = other.m_Head;
		while (temp != nullptr)
		{
			this->push_back(temp->m_Data);
			temp = temp->m_Next;
		}

		return *this;
	}

	// Assign
	List<T>& operator=(std::initializer_list<T> ilist)
	{
		clear();

		for (const auto& it : ilist)
		{
			push_back(it);
		}
		return *this;
	}

	// Move
	List<T>& operator=(List<T>&& other)
	{
		if (this == std::addressof(other))
		{
			return *this;
		}

		clear();
		std::swap(this->m_Tail, other.m_Tail);
		std::swap(this->m_Head, other.m_Head);
		std::swap(this->m_Size, other.m_Size);

		return *this;
	}

private:
	iterator makeIterator(const pointer ptr)
	{
		return iterator(ptr);
	}

	// Code not from me, trying to redo on my own after implementing merge and splice
//	template<class Compare>
// 	void MergeSort(ListNode<T>** first, size_t size, Compare comp)
// 	{
// 		ListNode<T>* head = *first;
// 		ListNode<T>* a;
// 		ListNode<T>* b;
// 
// 		/* Base case -- length 0 or 1 */
// 		if ((head == NULL) || (head->m_Next == NULL)) {
// 			return;
// 		}
// 
// 		/* Split head into 'a' and 'b' sublists */
// 		FrontBackSplit(head, &a, &b);
// 
// 		/* Recursively sort the sublists */
// 		MergeSort(&a, size, comp);
// 		MergeSort(&b, size, comp);
// 
// 		/* answer = merge the two sorted lists together */
// 		*first = SortedMerge(a, b);
// 	}
// 
// 	/* See https:// www.geeksforgeeks.org/?p=3622 for details of this
// function */
// 	ListNode<T>* SortedMerge(ListNode<T>* a, ListNode<T>* b)
// 	{
// 		ListNode<T>* result = NULL;
// 
// 		/* Base cases */
// 		if (a == NULL)
// 			return (b);
// 		else if (b == NULL)
// 			return (a);
// 
// 		/* Pick either a or b, and recur */
// 		if (a->m_Data <= b->m_Data) {
// 			result = a;
// 			result->m_Next = SortedMerge(a->m_Next, b);
// 		}
// 		else {
// 			result = b;
// 			result->m_Next = SortedMerge(a, b->m_Next);
// 		}
// 		return (result);
// 	}
// 
// 	/* UTILITY FUNCTIONS */
// 	/* Split the nodes of the given list into front and back halves,
// 		and return the two lists using the reference parameters.
// 		If the length is odd, the extra node should go in the front list.
// 		Uses the fast/slow pointer strategy. */
// 	void FrontBackSplit(ListNode<T>* source,
// 		ListNode<T>** frontRef, ListNode<T>** backRef)
// 	{
// 		ListNode<T>* fast;
// 		ListNode<T>* slow;
// 		slow = source;
// 		fast = source->m_Next;
// 
// 		/* Advance 'fast' two nodes, and advance 'slow' one node */
// 		while (fast != NULL) {
// 			fast = fast->m_Next;
// 			if (fast != NULL) {
// 				slow = slow->m_Next;
// 				fast = fast->m_Next;
// 			}
// 		}
// 
// 		/* 'slow' is before the midpoint in the list, so split it in two
// 		at that point. */
// 		*frontRef = source;
// 		*backRef = slow->m_Next;
// 		slow->m_Next = NULL;
// 	}

private:
	ListNode_t<T>* m_Head = nullptr;
	ListNode_t<T>* m_Tail = nullptr;
	size_t m_Size = 0;
};

template<class T>
bool operator==(const List<T>& lhs, const List<T>& rhs)
{
	if (lhs.size() != rhs.size())
	{
		return false;
	}

	return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
}

template <class T>
constexpr auto operator<=>(const List<T>& lhs, const List<T>& rhs)
{
	return std::lexicographical_compare_three_way(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
}