#include "FileHandler.h"

FileHandler::FileHandler(PATH& filepath) : fsFilePath               (filepath)
                                        , bMessageToDelete          (false)
                                        , StrMessageToDeleteBuffer  ()
                                        , vecFileBuffer             ()
{
    std::fstream file(fsFilePath, std::ios::in);
    SplitFile(file, vecFileBuffer, StrMessageToDeleteBuffer);
}

FileHandler::~FileHandler()
{
    // Here we need to delete every pointer
}

void FileHandler::SplitFile(std::fstream& file, std::vector<PATH>& fileBuffer, String& MessageToDeleteBuffer)
{
    std::cout << "Checking if file is valid" << std::endl;
    if (file.is_open())
    {
        std::cout << "File valid!\n" << std::endl;
        String StrLine;

        while (!file.eof())
        {
            getline(file, StrLine);

            // write message to delete in a buffer
            if (StrLine.empty())
                bMessageToDelete = true;

            if (bMessageToDelete)
                MessageToDeleteBuffer += StrLine;
            else
            {
                // logic for file / add new file when it's not an empty line
                fileBuffer.emplace_back(StrLine);
                StrLine.append("\n");
            }
        }
        file.close();
    }
    else
        std::cout << "File invalid!" << std::endl;
}

bool FileHandler::StartRemovingContentFromFile()
{
    int nCurrentFile = 1;

    for (const auto& files : vecFileBuffer)
    {
        // start time
        auto start = std::chrono::high_resolution_clock::now();

        // start thread
        std::thread WorkerThread(&FileHandler::RemoveContent, this, std::cref(files), std::ref(StrMessageToDeleteBuffer));
        WorkerThread.join();

        // stop time
        auto stop = std::chrono::high_resolution_clock::now();
        std::cout << "Thread took " << (stop - start) << " for this task" << std::endl;

        // Finished File output
        std::cout << "Finished File: " << nCurrentFile << "/" << vecFileBuffer.size() << "\n" << std::endl;
        nCurrentFile++;
    }

    return true;
}

bool FileHandler::RemoveContent(const PATH& file, String& messageToDelete)
{
    std::ifstream fileInput(file);
    std::stringstream buffer;

    // Error Message when it fails
    if (fileInput.bad())
    {
        std::cout << "File: " << file << " invalid!" << std::endl;
        return false;
    }

    if (fileInput.is_open())
    {
        std::cout << "Opened file - Reading Content" << std::endl;
        // Read entire file into buffer
        buffer << fileInput.rdbuf();
        fileInput.close();
    }

    String fileContent = buffer.str();
    size_t pos = fileContent.find(messageToDelete);
    size_t fileContentLen = fileContent.length();

    while (pos != std::string::npos)
    {
        fileContent.erase(pos, messageToDelete.length());
        pos = fileContent.find(messageToDelete);
    }

    if (fileContentLen >= fileContent.length())
    {
        // nothing to do because the give string wasn't found
        std::cout << "Give string was not found in file: " << file << std::endl;
        return true;
    }

    std::ofstream fileOutput(file, std::ios::trunc);
    if (!fileOutput)
    {
        std::cout << "Failed to open file for writing: " << file << std::endl;
        return false;
    }

    fileOutput << fileContent;
    fileOutput.close();
    std::cout << "Removed content and updated file." << std::endl;
    return true;
}