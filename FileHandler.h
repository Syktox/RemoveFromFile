#pragma once

#include <filesystem>
#include <fstream>
#include <print>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>

////// typedefs
typedef std::filesystem::path PATH;
typedef std::string String;
//////

class FileHandler {
public:
    explicit FileHandler(PATH& filepath);
    virtual ~FileHandler(); // virtual in case someone changes the class to an interface or abstract.

    /* Function takes a file and splits it into paths to files and stores it in the vec
     * and finds the message that should be deleted.
     * std::vector<PATH>& - vector of paths to files where a specific message should be deleted
     * String& - message that should be deleted in the files
     * */
    void SplitFile(std::fstream& file, std::vector<PATH>& fileBuffer, String& MessageToDeleteBuffer);

    /*  This functions start to remove the message in the files. It only start the process.
     *  It doesn't actually remove the content.
     */
    bool StartRemovingContentFromFile();

    /*
     * This function remove the content of the file.
     * const PATH& - path to the file where the content should be removed
     * String& message that should be remove
     */
    bool RemoveContent(const PATH& file, String& messageToDelete);

    String GetMessageToDeleteBuffer() { return StrMessageToDeleteBuffer; }
    std::vector<PATH> GetFileBuffer() { return vecFileBuffer; }

private:
    PATH fsFilePath;                    //< Path to the file containing the files and message (the main file)
    bool bMessageToDelete;              //< bool to mark if the message comes next so I can save it
    String StrMessageToDeleteBuffer;    //< Message that should be deleted from the files
    std::vector<PATH> vecFileBuffer;    //< Vector containing the paths of the files
    std::mutex fileMutex;               //< This should lock the file while a threads works on it
};
