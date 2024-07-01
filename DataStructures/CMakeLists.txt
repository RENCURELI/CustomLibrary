cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(target_sources
	Array.hpp
	DeQue.hpp
	FList.hpp
	FListNode.hpp
	HashTable.hpp
	List.hpp
	ListNode.hpp
	PriorityQueue.hpp
	Queue.hpp
	Span.hpp
	Stack.hpp
	UnorderedMap.hpp
	Vector.hpp
)
list(TRANSFORM target_sources PREPEND "include/")

add_library(DataStructures INTERFACE ${target_sources})

target_include_directories(DataStructures INTERFACE include)