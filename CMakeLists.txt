cmake_minimum_required(VERSION 3.31)
project(RemoveElementsFromFile)

set(CMAKE_CXX_STANDARD 20)

add_executable(RemoveElementsFromFile main.cpp
        FileHandler.cpp
        FileHandler.h)

# Create a runtime data directory
set(DATA_DIR ${CMAKE_BINARY_DIR}/data)

file(MAKE_DIRECTORY ${DATA_DIR})
