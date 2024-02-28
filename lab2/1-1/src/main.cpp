#include "stdafx.h"
#include "arithmetic-mean.h"

const std::string SEPARATOR = ", ";

std::vector<double> ReadNumbers() {
    std::vector<double> numbers(std::istream_iterator<double>(std::cin), (std::istream_iterator<double>()));

    while (!std::cin.eof()) {
        double number;
        if (std::cin >> number) {
            numbers.push_back(number);
        } else {
            break;
        }
    }

    copy(std::istream_iterator<double>(std::cin), std::istream_iterator<double>(), back_inserter(numbers));

    return numbers;
}

void PrintNumbers(const std::vector<double> &numbers) {
    for (int i = 0; i < numbers.size(); i++) {
        std::cout << numbers[i];
        if (i != numbers.size() - 1) {
            std::cout << SEPARATOR;
        }
    }
    std::cout << std::endl;
}

int main() {
    std::vector<double> numbers = ReadNumbers();
    HandleNumbersByArithmeticMean(numbers);
    SortNumbers(numbers);
    PrintNumbers(numbers);
    return 0;
}
