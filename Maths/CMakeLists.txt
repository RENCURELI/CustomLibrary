cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(Maths INTERFACE 
include/MathematicalConstants.hpp
)

target_include_directories(Maths INTERFACE include)