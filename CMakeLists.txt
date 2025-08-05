cmake_minimum_required(VERSION 3.31) # Using 3.10 for broader compatibility. 3.31 is fine if you need specific features.
project(RemoveElementsFromFile LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(RemoveElementsFromFile
        main.cpp
        FileHandler.cpp
        FileHandler.h)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) removed it for now
# NO data copying or installation logic needed in CMakeLists.txt anymore for this approach.
# You just need to ensure your C++ code knows where to find the 'data' folder.