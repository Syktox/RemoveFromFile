#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono> // to check the time
#include <mutex>

////// typedefs
typedef std::filesystem::path PATH;
typedef std::string String;
//////

class FileHandler {
public:
    FileHandler(PATH& filepath);
    virtual ~FileHandler(); // virtual in case someone changes the class to a interface or abstract.
    void SplitFile(std::fstream& file, std::vector<PATH>& fileBuffer, String& MessageToDeleteBuffer);
    bool StartRemovingContentFromFile();
    bool RemoveContent(const PATH& file, String& messageToDelete);

    String GetMessageToDeleteBuffer() { return StrMessageToDeleteBuffer; }
    std::vector<PATH> GetFileBuffer() { return vecFileBuffer; }

private:
    PATH fsFilePath;                    //< Path to the file containing the files and message (the main file)
    bool bMessageToDelete;              //< bool to mark if the message comes next so I can save it
    String StrMessageToDeleteBuffer;    //< Message that should be deleted from the files
    std::vector<PATH> vecFileBuffer;    //< Vector containing the paths of the files
    std::mutex fileMutex;           //< This should lock the file while a threads works on it
};
