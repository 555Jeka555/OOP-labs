#include "stdafx.h"

const int MIN_CRYPT_KEY = 0;
const int MAX_CRYPT_KEY = 255;

enum class Mode
{
    CRYPT,
    DECRYPT
};

struct Args
{
    Mode mode;
    std::string inputFileName;
    std::string outputFileName;
    int key;
};

void CheckValidArgumentCount(const int argc)
{
    if (argc != 5)
    {
        throw std::runtime_error("Invalid arguments count\n"
                                 "Usage: crypt|decrypt <input file> <output file> <key>");
    }
}

Mode ParseMode(const std::string& modeStr)
{
    if (modeStr == "crypt")
    {
        return Mode::CRYPT;
    }
    else if (modeStr == "decrypt")
    {
        return Mode::DECRYPT;
    }
    else
    {
        throw std::invalid_argument("Invalid mode. Use 'crypt'/'decrypt'");
    }
}

Args ParseArgs(char* argv[])
{
    Args args;
    args.mode = ParseMode(argv[1]);
    args.inputFileName = argv[2];
    args.outputFileName = argv[3];

    try
    {
        args.key = std::stoi(argv[4]);
    }
    catch (const std::runtime_error& e)
    {
        throw std::invalid_argument("Invalid input crypt key");
    }

    return args;
}

void CheckValidCryptKey(int key)
{
    if (key < MIN_CRYPT_KEY || key > MAX_CRYPT_KEY)
    {
        throw std::invalid_argument("Invalid crypt key");
    }
}

void CheckValidOpenFiles(const std::ifstream& inputFile, const std::ofstream& outputFile)
{
    if (!inputFile.is_open())
    {
        throw std::runtime_error("Failed to open input file for reading");
    }

    if (!outputFile.is_open())
    {
        throw std::runtime_error("Failed to open output file for writing");
    }
}

void CheckValidFlushOutputFile(std::ofstream& outputFile)
{
    if (!outputFile.flush())
    {
        throw std::runtime_error("Failed to save data on disk");
    }
}

void CheckReadingInputFile(const std::ifstream& inputFile)
{
    if (!inputFile.eof())
    {
        throw std::runtime_error("Error reading input file");
    }
}

unsigned char MixBits(unsigned char byte)
{
    unsigned char result = 0;

    result |= (byte & 0b00000111) << 2;
    result |= (byte & 0b00011000) << 3;
    result |= (byte & 0b01100000) >> 5;
    result |= (byte & 0b10000000) >> 2;

    return result;
}

unsigned char UnmixBits(unsigned char byte)
{
    unsigned char result = 0;

    result |= (byte & 0b00000011) << 5;
    result |= (byte & 0b00011100) >> 2;
    result |= (byte & 0b00100000) << 2;
    result |= (byte & 0b11000000) >> 3;

    return result;
}

void CryptFile(std::ifstream& inputFile, std::ofstream& outputFile, int key)
{
    char byte;
    while (inputFile.read(&byte, sizeof(byte)))
    {
        byte = static_cast<char>(byte ^ key);
        outputFile.put(static_cast<char>(MixBits(byte)));
    }

    CheckReadingInputFile(inputFile);
}

void DecryptFile(std::ifstream& inputFile, std::ofstream& outputFile, int key)
{
    char byte;
    while (inputFile.read(&byte, sizeof(byte)))
    {
        byte = static_cast<char>(UnmixBits(byte) ^ key);
        outputFile.put(byte);
    }

    CheckReadingInputFile(inputFile);
}

void Crypt(const std::string& inputFilePath, const std::string& outputFilePath, int key)
{
    CheckValidCryptKey(key);
    std::ifstream inputFile(inputFilePath, std::ios::binary | std::ios::in);
    std::ofstream outputFile(outputFilePath, std::ios::binary | std::ios::out);
    CheckValidOpenFiles(inputFile, outputFile);

    CryptFile(inputFile, outputFile, key);

    CheckValidFlushOutputFile(outputFile);
}

void Decrypt(const std::string& inputFilePath, const std::string& outputFilePath, int key)
{
    CheckValidCryptKey(key);
    std::ifstream inputFile(inputFilePath, std::ios::binary | std::ios::in);
    std::ofstream outputFile(outputFilePath, std::ios::binary | std::ios::out);

    CheckValidOpenFiles(inputFile, outputFile);

    DecryptFile(inputFile, outputFile, key);

    CheckValidFlushOutputFile(outputFile);
}

int main(int argc, char *argv[])
{
    try
    {
        CheckValidArgumentCount(argc);
        Args args = ParseArgs(argv);
        if (args.mode == Mode::CRYPT)
        {
            Crypt(args.inputFileName, args.outputFileName, args.key);
        }
        else
        {
            Decrypt(args.inputFileName, args.outputFileName, args.key);
        }
    }
    catch (const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}