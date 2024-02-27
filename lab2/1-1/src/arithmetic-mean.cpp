#include "arithmetic-mean.h"

void HandleNumbersByArithmeticMean(std::vector<float> &numbers) {
    float sumPosNumber = std::accumulate(numbers.begin(), numbers.end(), 0,
                                         [](float acc, float val)
                                         {
                                             return val > 0 ? acc + val : acc;
                                         });

    float countPosNumber = std::accumulate(numbers.begin(), numbers.end(), 0,
                                           [](float acc, float val)
                                           {
                                               return val > 0 ? ++acc : acc;
                                           });

    if (countPosNumber == 0)
    {
        return;
    }

    float arithmeticMean = sumPosNumber / countPosNumber;

    for (float & number : numbers)
    {
        number = number + arithmeticMean;
    }
}
