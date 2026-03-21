cmake_minimum_required(VERSION 4.1)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled main.cpp
        sort/ShellSort.cpp
        sort/ShellSort.h
        sort/HybridSort.cpp
        sort/HybridSort.h
        sort/HeapSort.cpp
        sort/HeapSort.h
        utils/utils.cpp
        utils/utils.h
)
