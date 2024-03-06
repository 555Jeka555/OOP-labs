#include "stdafx.h"
#include "dictionary.h"

void CheckValidArgumentCount(const int argc)
{
    if (argc != 2)
    {
        throw std::runtime_error("Invalid arguments count\n"
                                 "Usage: <dictionary.txt>>");
    }
}

int main(int argc, char *argv[]) {
    try
    {
        SetConsoleOutputCP(1251);
        SetConsoleCP(1251);

        CheckValidArgumentCount(argc);

        std::string dictFileName = argv[1];
        InitSessionTranslate(dictFileName);
    }
    catch (const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}
