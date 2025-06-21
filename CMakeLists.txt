cmake_minimum_required(VERSION 3.31)
project(RemoveElementsFromFile)

set(CMAKE_CXX_STANDARD 20)

add_executable(RemoveElementsFromFile main.cpp
        FileHandler.cpp
        FileHandler.h)

# Create a runtime data directory
set(DATA_DIR ${CMAKE_BINARY_DIR}/data)

file(MAKE_DIRECTORY ${DATA_DIR})

# Copy test files once during the build
foreach(file IN LISTS Test.txt Test2.txt Test3.txt)
    add_custom_command(
            TARGET RemoveElementsFromFile PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/data/${file}
            ${DATA_DIR}/${file}
    )
endforeach()
