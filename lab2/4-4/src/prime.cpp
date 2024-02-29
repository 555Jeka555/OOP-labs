#include "prime.h"

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
    std::vector<bool> isPrime(upperBound + 1, true);
    std::set<int> primes;

    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i <= std::sqrt(upperBound); ++i)
    {
        if (isPrime[i])
        {
            for (int j = i * i; j <= upperBound; j += i)
            {
                isPrime[j] = false;
            }
        }
    }

    for (int i = 2; i <= upperBound; ++i)
    {
        if (isPrime[i])
        {
            primes.insert(i);
        }
    }
    return primes;
}
