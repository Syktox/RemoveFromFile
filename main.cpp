#include <iostream>
#include <filesystem>
#include <fstream>

int main() {
    std::filesystem::path filePath;
    bool bMessageToDelete = false;
    std::string messageToDelete;
    std::string files;

    std::cout << "Enter the file containing the filepath and the thing that should be removed" << std::endl;
    // std::cin >> filePath;
    filePath = "Test.txt";  // Test only

    // Same as ifstream
    std::fstream file(filePath, std::ios::in);

    std::cout << "Checking if file is valid" << std::endl;

    // Should print out the whole textfile
    if (file.is_open())
    {
        std::cout << "Opened file: " << filePath << std::endl;
        std::string line;

        while (!file.eof())
        {
            getline(file, line);
            std::cout << line << std::endl;

            // logic for file / add new file when its not a empty line
            if (line.empty())
                bMessageToDelete = true;
            else
                line.append("\n");

            // write message to delete in a buffer
            if (bMessageToDelete)
                messageToDelete += line;
            else
                files += line;
        }
        file.close();
        std::cout << "Closed file" << std::endl;
    }
    return 0;
}