#include "stdafx.h"
#include "arithmetic-mean.h"

const std::string SEPARATOR = ", ";

std::vector<float> ReadNumbers() {
    std::vector<float> numbers(std::istream_iterator<float>(std::cin), (std::istream_iterator<float>()));

    while (!std::cin.eof()) {
        float number;
        if (std::cin >> number) {
            numbers.push_back(number);
        } else {
            break;
        }
    }

    copy(std::istream_iterator<double>(std::cin), std::istream_iterator<double>(), back_inserter(numbers));

    return numbers;
}

void PrintNumbers(const std::vector<float> &numbers) {
    for (int i = 0; i < numbers.size(); i++) {
        std::cout << numbers[i];
        if (i != numbers.size() - 1) {
            std::cout << SEPARATOR;
        }
    }
    std::cout << std::endl;
}


int main() {
    std::vector<float> numbers = ReadNumbers();
    HandleNumbersByArithmeticMean(numbers);
    std::sort(numbers.begin(), numbers.end());
    PrintNumbers(numbers);
    return 0;
}
