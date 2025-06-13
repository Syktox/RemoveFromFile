cmake_minimum_required(VERSION 3.31)
project(RemoveElementsFromFile)

set(CMAKE_CXX_STANDARD 20)

add_executable(RemoveElementsFromFile main.cpp)

configure_file(Test.txt Test.txt COPYONLY)
configure_file(Test2.txt Test2.txt COPYONLY)
