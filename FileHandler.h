#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono> // to check the time

////// typedefs
typedef std::filesystem::path PATH;
typedef std::string String;
//////

class FileHandler {
public:
    FileHandler(PATH& filepath);
    void SplitFile(std::fstream& file, std::vector<PATH>& fileBuffer, String& MessageToDeleteBuffer);
    bool StartRemovingContentFromFile();
    bool RemoveContent(const String& file, String& messageToDelete);

    String GetMessageToDeleteBuffer() { return StrMessageToDeleteBuffer; }
    std::vector<PATH> GetFileBuffer() { return vecFileBuffer; }

private:
    PATH fsFilePath;
    bool bMessageToDelete;
    String StrMessageToDeleteBuffer;
    std::vector<PATH> vecFileBuffer;
};
