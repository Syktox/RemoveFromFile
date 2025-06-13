#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>

////// typedefs
typedef std::filesystem::path PATH;
typedef std::string String;
//////

class FileHandler {
public:
    FileHandler(PATH& filepath);
    void SplitFile(std::fstream& file, String& fileBuffer, String& MessageToDeleteBuffer);

    String GetMessageToDeleteBuffer() { return StrMessageToDeleteBuffer; }
    String GetFileBuffer() { return StrFileBuffer; }

private:
    PATH fsFilePath;
    bool bMessageToDelete;
    String StrMessageToDeleteBuffer;
    String StrFileBuffer;

};
