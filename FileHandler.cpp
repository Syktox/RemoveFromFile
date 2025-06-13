#include "FileHandler.h"

FileHandler::FileHandler(PATH& filepath) : fsFilePath               (filepath)
                                        , bMessageToDelete          (false)
                                        , StrMessageToDeleteBuffer  ()
                                        , StrFileBuffer             ()
{
    std::fstream file(fsFilePath, std::ios::in);
    SplitFile(file, StrFileBuffer, StrMessageToDeleteBuffer);
}

void FileHandler::SplitFile(std::fstream& file, String& fileBuffer, String& MessageToDeleteBuffer)
{
    std::cout << "Checking if file is valid" << std::endl;
    if (file.is_open())
    {
        std::cout << "File valid!\nOpened file" << std::endl;
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
                fileBuffer += StrLine;
        }
        file.close();
        std::cout << "Closed file" << std::endl;
    }
}