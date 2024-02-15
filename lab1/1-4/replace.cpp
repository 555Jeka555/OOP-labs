#include "stdafx.h"

struct Args {
    std::string inputFileName;
    std::string outputFileName;
    std::string search;
    std::string replace;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 5)
    {
        return std::nullopt;
    }
    Args args;
    args.inputFileName = argv[1];
    args.outputFileName = argv[2];
    args.search = argv[3];
    args.replace = argv[4];
    return args;
}

void CheckValidArgumentCount(const std::optional<Args>& args)
{
    if (!args)
    {
        throw std::runtime_error( "Invalid argument count\n"
                                  "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n");
    }
}

std::ifstream GetInputFile(std::optional<Args> args)
{
    std::ifstream inputFile;
    inputFile.open(args->inputFileName);
    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open" << args->inputFileName << " for reading" << std::endl;
    }
    return inputFile;
}

std::ofstream GetOutputFile(std::optional<Args> args)
{
    std::ofstream outputFile;
    outputFile.open(args->outputFileName);
    if (!outputFile.is_open())
    {
        std::cerr << "Failed to open" << args->outputFileName << " for writing" << std::endl;
    }
    return outputFile;
}

std::string ReplaceString(const std::string& subject,
                          const std::string& searchString, const std::string& replacementString)
{
    if (searchString.empty())
    {
        return subject;
    }

    size_t pos = 0;
    // Результат будет записан в новую строку result, оставляя строку subject неизменной
    // Какие преимущества есть у этого способа по сравнению с алгоритмом, выполняющим
    // замену прямо в строке subject?
    // Исходная строка subject остаётся неизменной, для последующего сравнения
    // Чистота кода - каждая строка отвечает за одну операцию
    std::string result;
    while (pos < subject.length())
    {
        size_t foundPos = subject.find(searchString, pos);
        if (foundPos == std::string::npos)
        {
            result.append(subject, pos);
            return result;
        }

        result.append(subject, pos, foundPos - pos);
        result.append(replacementString);
        pos = foundPos + searchString.length();
    }
    return result;
}

void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
                               const std::string& searchString, const std::string& replacementString)
{
    std::string line;

    while (std::getline(input, line))
    {
        output << ReplaceString(line, searchString, replacementString) << "\n";
    }
}

int main(int argc, char* argv[]) {
    try
    {
        auto args = ParseArgs(argc, argv);
        CheckValidArgumentCount(args);

        std::ifstream inputFile = GetInputFile(args);
        std::ofstream outputFile = GetOutputFile(args);

        CopyStreamWithReplacement(inputFile, outputFile, args->search, args->replace);

        // Используется для синхронизации буфера выходного потока с соответствующей выходной последовательностью.
        // Это гарантирует, что все символы, записанные в поток, будут фактически записаны в устройство вывода.
        outputFile.flush();
    }
    catch (const std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
