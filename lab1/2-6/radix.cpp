#include "stdafx.h"

const int RADIX_DECIMAL = 10;
const char FIRST_CHAR_DIGIT = '0';
const char LAST_CHAR_DIGIT = '9';
const char FIRST_CHAR_LETTER = 'A';
const char LAST_CHAR_LETTER = 'Z';
const char CHAR_NEGATIVE = '-';

struct Args {
    int sourceRadix;
    int destRadix;
    std::string value;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 4)
    {
        return std::nullopt;
    }
    Args args;
    args.sourceRadix = std::stoi(argv[1]);
    args.destRadix = std::stoi(argv[2]);
    args.value = argv[3];
    return args;
}

void CheckValidArgumentCount(const std::optional<Args>& args)
{
    if (!args)
    {
        throw std::runtime_error( "Invalid argument count\n"
                                  "Usage: radix.exe <source notation> <destination notation> <value>");
    }
}

void CheckValidRadix(const int& radix)
{
    if (radix < 2 || radix > 36)
    {
        throw std::runtime_error( "Invalid system number\n"
                                  "Use the number systems from 2 to 36");
    }
}

void CheckValidValueInput(const std::string& value, const int& radix)
{
    for (char c : value)
    {
        bool isCharLetter = c >= FIRST_CHAR_LETTER && c <= LAST_CHAR_LETTER;
        bool isCharDigit = c >= FIRST_CHAR_DIGIT && c <= LAST_CHAR_DIGIT;
        bool isCharMinus = c == CHAR_NEGATIVE;

        bool isValidChar = isCharLetter || isCharDigit || isCharMinus;
        if (!isValidChar)
        {
            throw std::runtime_error( "Invalid char in value input");
        }

        bool isCharLetterInRadix = radix > c - FIRST_CHAR_LETTER + RADIX_DECIMAL;
        bool isCharDigitInRadix = radix > c - FIRST_CHAR_DIGIT;
        bool isCharInRadix = isCharLetter && isCharLetterInRadix
                || isCharDigit && isCharDigitInRadix || isCharMinus;
        if (!isCharInRadix)
        {
            throw std::runtime_error( "Invalid char in radix");
        }
    }
}

int StringToInt(char digit)
{
    if (isdigit(digit))
    {
        return digit - FIRST_CHAR_DIGIT;
    }
    return toupper(digit) - FIRST_CHAR_LETTER + RADIX_DECIMAL;
}

char IntToString(int n)
{
    if (n > 10)
    {
        return char(FIRST_CHAR_LETTER + n - RADIX_DECIMAL);
    }
    return char(FIRST_CHAR_DIGIT + n);
}

int ConvertAnyRadixToDecimal(const std::string& value, const int& radix)
{
    int result = 0;
    int power = 0;
    for (char i : value)
    {
        int digit = StringToInt(i);
        result = result * radix + digit;
        ++power;
    }
    return result;
}

std::string CovertDecimalToAnyRadix(int decimal, const int& radix, const bool& isNegative)
{
    if (decimal == 0)
    {
        return "0";
    }

    std::string result;

    while (decimal > 0)
    {
        int remained = decimal % radix;
        result = IntToString(remained) + result;
        decimal /= radix;
    }

    if (isNegative) {
        result = CHAR_NEGATIVE + result;
    }

    return result;
}

std::string ConvertRadix(int sourceRadix, int destRadix, std::string value)
{
    CheckValidRadix(sourceRadix);
    CheckValidRadix(destRadix);
    CheckValidValueInput(value, sourceRadix);

    bool isNegative = false;
    if (value[0] == CHAR_NEGATIVE)    {
        value = value.substr(1, value.size() - 1);
        isNegative = true;
    }

    int decimal = ConvertAnyRadixToDecimal(value, sourceRadix);
    return CovertDecimalToAnyRadix(decimal, destRadix, isNegative);
}

int main(int argc, char* argv[]) {
    try
    {
        auto args = ParseArgs(argc, argv);
        CheckValidArgumentCount(args);
        std::string numberConverted = ConvertRadix(args->sourceRadix, args->destRadix, args->value);
        std::cout << numberConverted << std::endl;
    }
    catch (const std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
