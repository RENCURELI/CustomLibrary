cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(Algorithms INTERFACE 
include/NonModifyingSequenceOperations.hpp
)

target_include_directories(Algorithms INTERFACE include)