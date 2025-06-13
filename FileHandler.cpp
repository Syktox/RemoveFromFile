#include "FileHandler.h"

FileHandler::FileHandler(PATH& filepath) : fsFilePath               (filepath)
                                        , bMessageToDelete          (false)
                                        , StrMessageToDeleteBuffer  ()
                                        , vecFileBuffer             ()
{
    std::fstream file(fsFilePath, std::ios::in);
    SplitFile(file, vecFileBuffer, StrMessageToDeleteBuffer);
}

void FileHandler::SplitFile(std::fstream& file, std::vector<String>& fileBuffer, String& MessageToDeleteBuffer)
{
    std::cout << "Checking if file is valid" << std::endl;
    if (file.is_open())
    {
        std::cout << "File valid!\n" << std::endl;
        String StrLine;

        while (!file.eof())
        {
            getline(file, StrLine);

            // logic for file / add new file when its not a empty line
            if (StrLine.empty())
                bMessageToDelete = true;
            else
                StrLine.append("\n");

            // write message to delete in a buffer
            if (bMessageToDelete)
                MessageToDeleteBuffer += StrLine;
            else
            {
                fileBuffer.emplace_back(StrLine);
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

    for (auto& files : vecFileBuffer)
    {
        auto start = std::chrono::high_resolution_clock::now();
        std::thread RemoveContentThread(&FileHandler::RemoveContent, this, std::ref(files), std::ref(StrMessageToDeleteBuffer));
        RemoveContentThread.join();
        auto stop = std::chrono::high_resolution_clock::now();
        std::cout << "Thread took " << (stop - start) << " for this task" << std::endl;

        // Finished File output
        std::cout << "Finished File: " << nCurrentFile << "/" << vecFileBuffer.size() << "\n" << std::endl;
        nCurrentFile++;
    }



    return true;
}

void FileHandler::RemoveContent(String& file, String& messageToDelete)
{
    std::cout << "Removed content from " << file;
}