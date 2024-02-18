cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(DataStructures INTERFACE 
include/Array.hpp
include/DeQue.hpp
include/FList.hpp
include/FListNode.hpp
include/List.hpp
include/ListNode.hpp
include/Queue.hpp
include/PriorityQueue.hpp
include/Span.hpp
include/Stack.hpp
include/Vector.hpp
)

target_include_directories(DataStructures INTERFACE include)