#include <iostream>

#include "FileHandler.h"

int main() {
    PATH filePath;
    std::cout << "Enter the file containing the filepath and the thing that should be removed" << std::endl;
    // std::cin >> filePath;
    filePath = "Test.txt";  // Test only

    FileHandler rFileHandler(filePath);
    String file1 = rFileHandler.GetFileBuffer();
    String file2 = rFileHandler.GetMessageToDeleteBuffer();

    std::cout << file1 << std::endl;
    std::cout << file2 << std::endl;

    return 0;
}