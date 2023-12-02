cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(Algorithms INTERFACE 
include/NonModifyingSequenceOperations.hpp
include/SortingOperations.hpp
include/HeapOperations.hpp
)

target_include_directories(Algorithms INTERFACE include)