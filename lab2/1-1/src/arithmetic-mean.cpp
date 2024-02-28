#include "arithmetic-mean.h"

void HandleNumbersByArithmeticMean(std::vector<double> &numbers)
{
    std::vector<double> positiveNumbers;
    std::copy_if(numbers.begin(), numbers.end(), std::back_inserter(positiveNumbers),
                 [](double x) { return x > 0; });

    auto countPositiveNumber = static_cast<double>(positiveNumbers.size());
    if (countPositiveNumber == 0)
    {
        return;
    }

    double sumPositiveNumber = std::accumulate(positiveNumbers.begin(), positiveNumbers.end(), 0.0);
    double arithmeticMean = sumPositiveNumber / countPositiveNumber;

    for (double & number : numbers)
    {
        number = number + arithmeticMean;
    }
}

void SortNumbers(std::vector<double> &numbers)
{
    std::sort(numbers.begin(), numbers.end());
}
