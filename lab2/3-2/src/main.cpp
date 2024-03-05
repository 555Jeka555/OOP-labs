#include "stdafx.h"
#include "dictionary.h"

const std::string DEFAULT_DICT_PATH = "../src/dictionary.txt";

void CheckValidArgumentCount(const int argc)
{
    if (argc != 2)
    {
        throw std::runtime_error("Invalid arguments count\n"
                                 "Usage: <dictionary.txt>>");
    }
}

void CheckOpenAndRecreateFile(std::ofstream& outputFile)
{
    if (!outputFile.is_open())
    {
        outputFile.open(DEFAULT_DICT_PATH);
        if (!outputFile.is_open()) {
            throw std::runtime_error("Failed to create file");
        }
    }
}

void CheckFlushToOutputFile(std::ofstream& outputFile)
{
    if (!outputFile.flush())
    {
        throw std::runtime_error("Failed flush to file");
    }
}

int main(int argc, char *argv[]) {
    try
    {
        CheckValidArgumentCount(argc);

        std::string outputFileName = argv[1];
        std::ofstream outputFile(outputFileName);
        CheckOpenAndRecreateFile(outputFile);

        InitSessionTranslate(outputFile);

        CheckFlushToOutputFile(outputFile);
    }
    catch (const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}
