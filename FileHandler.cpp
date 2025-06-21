#include "FileHandler.h"

FileHandler::FileHandler(PATH& filepath) : fsFilePath               (filepath)
                                        , bMessageToDelete          (false)
                                        , StrMessageToDeleteBuffer  ()
                                        , vecFileBuffer             ()
{
    std::fstream file(fsFilePath, std::ios::in);
    SplitFile(file, vecFileBuffer, StrMessageToDeleteBuffer);
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
            std::cout << StrLine <<std::endl;

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
    unsigned int nThreads = std::thread::hardware_concurrency();
    // if it fails to retrieve the data be safe and use only one core
    if (nThreads == 0) nThreads = 1;

    for (const auto& files : vecFileBuffer)
    {
        // start time
        auto start = std::chrono::high_resolution_clock::now();



        std::thread WorkerThread (&FileHandler::RemoveContent, this, std::cref(files), std::cref(StrMessageToDeleteBuffer));



        // stop time
        auto stop = std::chrono::high_resolution_clock::now();
        std::cout << "Thread took " << (stop - start) << " for this task" << std::endl;

        // Finished File output
        std::cout << "Finished File: " << nCurrentFile << "/" << vecFileBuffer.size() << "\n" << std::endl;
        nCurrentFile++;
    }

    return true;
}

bool FileHandler::RemoveContent(const String& file, String& messageToDelete)
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

    std::cout << buffer.str() << std::endl;

    std::string fileContent = buffer.str();
    size_t pos = fileContent.find(messageToDelete);
    while (pos != std::string::npos)
    {
        fileContent.erase(pos, messageToDelete.length());
        pos = fileContent.find(messageToDelete);
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