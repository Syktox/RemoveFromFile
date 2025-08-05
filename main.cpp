#include "FileHandler.h"
#include <print>

int main() {
    PATH filePath;
    std::printf("Enter the file containing the filepath and the text that should be removed");
    // std::cin >> filePath;
    filePath = "data/Test.txt";  // Test only

    FileHandler rFileHandler(filePath);
    if ( rFileHandler.StartRemovingContentFromFile() )
        std::cout << "\n***** Finished removing content *****" << std::endl;

    return 0;
}