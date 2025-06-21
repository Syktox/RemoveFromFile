#include "FileHandler.h"

int main() {
    PATH filePath;
    std::cout << "Enter the file containing the filepath and the thing that should be removed" << std::endl;
    // std::cin >> filePath;
    filePath = "data/Test.txt";  // Test only

    FileHandler rFileHandler(filePath);
    if ( rFileHandler.StartRemovingContentFromFile() )
        std::cout << "\n***** Finished removing content *****" << std::endl;

    return 0;
}