#include "stdafx.h"
#include "prime.h"

const int MIN_LIMIT = 1;
const int MAX_LIMIT = 100000000;
const char SEPARATOR = ' ';

void CheckValidInputLine(const std::string& line)
{
    for (char c : line)
    {
        if (!std::isdigit(c))
        {
            throw std::runtime_error("Invalid input, enter number");
        }
    }
}

void CheckInputOverlaps(int upperBound)
{
    if (upperBound < MIN_LIMIT || upperBound > MAX_LIMIT)
    {
        throw std::runtime_error("Invalid input overlaps, enter number in range 1 to 100000000");
    }
}

void PrintNumbers(const std::set<int>& primes)
{
    for (int prime : primes)
    {
        std::cout << prime << SEPARATOR;
    }
    std::cout << std::endl;
}

int main()
{
    try
    {
        std::string line;
        std::cin >> line;
        CheckValidInputLine(line);

        int upperBound = std::stoi(line);
        CheckInputOverlaps(upperBound);

        std::set<int> primes = GeneratePrimeNumbersSet(upperBound);
        PrintNumbers(primes);
    }
    catch (const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
