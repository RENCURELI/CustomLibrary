cmake_minimum_required(VERSION 3.26)
project(Libraries)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(DataStructures)
#add_subdirectory(Algorithms)
#add_subdirectory(Maths)
add_subdirectory(TST_DataStructures)

add_executable(Libraries
TST_DataStructures/test.cpp
TST_DataStructures/ContainerTests/ArrayTest.hpp
TST_DataStructures/ContainerTests/DequeTest.hpp
TST_DataStructures/ContainerTests/FListTest.hpp
TST_DataStructures/ContainerTests/ListTest.hpp
TST_DataStructures/ContainerTests/QueueTest.hpp
TST_DataStructures/ContainerTests/PriorityQueueTest.hpp
TST_DataStructures/ContainerTests/StackTest.hpp
TST_DataStructures/ContainerTests/VectorTest.hpp
)

target_link_libraries(Libraries PUBLIC DataStructures)
#target_link_libraries(Libraries PUBLIC Algorithms)
#target_link_libraries(Libraries PUBLIC Maths)
target_link_libraries(Libraries PUBLIC GTest::gtest_main)

include(GoogleTest)

target_include_directories(Libraries PUBLIC DataStructures/include)