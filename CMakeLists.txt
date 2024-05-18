cmake_minimum_required(VERSION 3.27)
project(Libraries CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/4c676b94b8ec284f20337862829412aab7e7927f.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(DataStructures)
add_subdirectory(Algorithms)
add_subdirectory(Maths)
add_subdirectory(TST_DataStructures)

add_executable(Libraries)
set(target_sources
	HelperFuncs.hpp
	ContainerTests/ArrayTest.hpp
	ContainerTests/DequeTest.hpp
	ContainerTests/FListTest.hpp
	ContainerTests/ListTest.hpp
	ContainerTests/QueueTest.hpp
	ContainerTests/PriorityQueueTest.hpp
	ContainerTests/SpanTest.hpp
	ContainerTests/StackTest.hpp
	ContainerTests/VectorTest.hpp
	NMSequenceOperationsTests/FindTest.hpp
	SortingOperationsTests/HeapTest.hpp
	SortingOperationsTests/SortTest.hpp
)
list(TRANSFORM target_sources PREPEND "TST_DataStructures/")
target_sources(Libraries PUBLIC TST_DataStructures/test.cpp PUBLIC FILE_SET HEADERS FILES)

set_target_properties(DataStructures PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(Libraries PUBLIC DataStructures)

set_target_properties(Algorithms PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(Libraries PUBLIC Algorithms)

target_link_libraries(Libraries PUBLIC Maths)
target_link_libraries(Libraries PUBLIC GTest::gtest_main)

include(GoogleTest)

target_include_directories(Libraries INTERFACE DataStructures/include)
target_include_directories(Libraries INTERFACE Algorithms/include)

#set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Libraries)