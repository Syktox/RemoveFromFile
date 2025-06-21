cmake_minimum_required(VERSION 3.31)
project(RemoveElementsFromFile)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE DATA_FILES "data/*")

add_executable(RemoveElementsFromFile
        main.cpp
        FileHandler.cpp
        FileHandler.h)

install(TARGETS RemoveElementsFromFile DESTINATION bin)
install(DIRECTORY data/ DESTINATION share)