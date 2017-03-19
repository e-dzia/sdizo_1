cmake_minimum_required(VERSION 3.6)
project(sdizo_1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Array.h List.h List.cpp BinaryHeap.h BinaryHeap.cpp RedBlackTree.h RedBlackTree.cpp Array.cpp cmake-build-debug/DataStructure.h)
add_executable(sdizo_1 ${SOURCE_FILES})