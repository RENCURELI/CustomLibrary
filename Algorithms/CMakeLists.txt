cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(target_sources
	NonModifyingSequenceOperations.hpp
	SortingOperations.hpp
	HeapOperations.hpp
)

list(TRANSFORM target_sources PREPEND "include/")

add_library(Algorithms INTERFACE ${target_sources})

target_include_directories(Algorithms INTERFACE include)