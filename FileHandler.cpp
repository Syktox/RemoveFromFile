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
    std::printf("Checking if file is valid\n");
    if (file.is_open())
    {
        std::printf("File valid\n");
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
        std::printf("File valid!\n");
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
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();

        std::printf("Thread took %lld ms for this task\n", duration);

        // Finished File output
        std::printf("Finished File: %d / %d\n", nCurrentFile, (int) vecFileBuffer.size());
        nCurrentFile++;
    }

    return true;
}

bool FileHandler::RemoveContent(const PATH& file, String& messageToDelete)
{
    // ChatGPT:
    // std::lock_guard ensures the mutex is automatically released when the function exits.
    // This prevents data races and corruption.
    std::lock_guard<std::mutex> lock(fileMutex);
    std::ifstream fileInput(file);
    std::stringstream buffer;

    // Error Message when it fails
    if (fileInput.bad())
    {
        std::printf("File: %s invalid!\n", file.c_str());
        return false;
    }

    if (fileInput.is_open())
    {
        std::printf("Opened file - Reading Content");
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
        std::printf("\nGive string was not found in file: %s\n", file.c_str());
        return true;
    }

    std::ofstream fileOutput(file, std::ios::trunc);
    if (!fileOutput)
    {
        std::printf("\nFailed to open file for writing: %s\n", file.c_str());
        return false;
    }

    fileOutput << fileContent;
    fileOutput.close();
    std::printf("\nRemoved content and updated file\n");
    return true;
}