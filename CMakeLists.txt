cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add all source files
add_executable(MyProject
    src/main.cpp
    src/utils.cpp
    src/compress.cpp
    src/huffman_tree.cpp
    src/bit_stack.cpp
)
