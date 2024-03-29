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

void CheckValidArgumentCount(const std::optional<Args> &args) {
    if (!args) {
        throw std::runtime_error("Invalid argument count\n"
                                 "Usage: radix.exe <source notation> <destination notation> <value>");
    }
}

void CheckValidRadix(const int &radix) {
    if (radix < 2 || radix > 36) {
        throw std::runtime_error("Invalid system number\n"
                                 "Use the number systems from 2 to 36");
    }
}

void CheckValidValueInput(const std::string &value, const int &radix) {
    bool isFirstCharLetter = true;
    for (char c: value) {
        bool isCharLetter = c >= FIRST_CHAR_LETTER && c <= LAST_CHAR_LETTER;
        bool isCharDigit = c >= FIRST_CHAR_DIGIT && c <= LAST_CHAR_DIGIT;
        bool isNegativeValue = c == CHAR_NEGATIVE && isFirstCharLetter;

        bool isValidChar = isCharLetter || isCharDigit || isNegativeValue;
        if (!isValidChar) {
            throw std::runtime_error("Invalid char in value input");
        }

        bool isCharLetterInRadix = isCharLetter && radix > c - FIRST_CHAR_LETTER + RADIX_DECIMAL;
        bool isCharDigitInRadix = isCharDigit && radix > c - FIRST_CHAR_DIGIT;

        bool isCharInRadix = isCharLetterInRadix || isCharDigitInRadix || isNegativeValue;
        if (!isCharInRadix) {
            throw std::runtime_error("Invalid char in radix");
        }
        isFirstCharLetter = false;
    }
}

int CharToInt(char digit) {
    if (isdigit(digit)) {
        return digit - FIRST_CHAR_DIGIT;
    }
    return toupper(digit) - FIRST_CHAR_LETTER + RADIX_DECIMAL;
}

char IntToChar(int n) {
    n = abs(n);
    if (n > 10) {
        return char(FIRST_CHAR_LETTER + n - RADIX_DECIMAL);
    }
    return char(FIRST_CHAR_DIGIT + n);
}

int StringToInt(const std::string &str, const int &radix) {
    int result = 0;
    int sign = 1;
    for (char c: str) {
        if (c == CHAR_NEGATIVE) {
            sign *= -1;
            continue;
        }
        int digit = CharToInt(c);

        if (
            (result * sign) < (std::numeric_limits<int>::min() + digit) / radix ||
            sign > 0 && result > (std::numeric_limits<int>::max() - digit) / radix
        ) {
            throw std::runtime_error("Invalid max value in integer");
        }

        result = result * radix + digit;
    }
    return result * sign;
}

std::string IntToString(int n, const int &radix) {
    if (n == 0) {
        return "0";
    }
    bool isNegative = n < 0;
    std::string result;

    while (n != 0) {
        int remained = n % radix;
        result = IntToChar(remained) + result;
        n /= radix;
    }

    if (isNegative) {
        result = CHAR_NEGATIVE + result;
    }

    return result;
}

std::optional<Args> ParseArgs(int argc, char *argv[]) {
    if (argc != 4) {
        return std::nullopt;
    }
    Args args;
    args.sourceRadix = StringToInt(argv[1], RADIX_DECIMAL);
    CheckValidRadix(args.sourceRadix);

    args.destRadix = StringToInt(argv[2], RADIX_DECIMAL);
    CheckValidRadix(args.destRadix);

    args.value = argv[3];
    return args;
}

int main(int argc, char *argv[]) {
    try {
        auto args = ParseArgs(argc, argv);
        CheckValidArgumentCount(args);
        CheckValidValueInput(args->value, args->sourceRadix);
        int value = StringToInt(args->value, args->sourceRadix);
        std::cout << IntToString(value, args->destRadix) << std::endl;
    }
    catch (const std::runtime_error &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
