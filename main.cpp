#include "FileHandler.h"
#include <iostream>

int main() {
    PATH filePath;
    std::printf("Enter the file containing the filepath and the text that should be removed\n");
    std::cin >> filePath;

    // removed for building binary's
    // filePath = "data/Test.txt";

    FileHandler rFileHandler(filePath);
    if ( rFileHandler.StartRemovingContentFromFile() )
        std::printf("\n***** Finished removing content *****\n");

    return 0;
}