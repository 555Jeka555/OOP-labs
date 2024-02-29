#include <gtest/gtest.h>
#include "../src/prime.h"

TEST (prime, prime_numbers)
{
    std::set<int> expected = {2, 3, 5, 7, 11, 13, 17, 19};
    std::set<int> primes = GeneratePrimeNumbersSet(20);

    EXPECT_EQ(expected, primes);
}

TEST (prime, prime_boundar_number)
{
    std::set<int> expected = {2, 3, 5, 7, 11, 13, 17, 19};
    std::set<int> primes = GeneratePrimeNumbersSet(19);

    EXPECT_EQ(expected, primes);
}

TEST (prime, min_allow_boundary_value)
{
    std::set<int> expected = {};
    std::set<int> primes = GeneratePrimeNumbersSet(1);

    EXPECT_EQ(expected, primes);
}

TEST (prime, min_boundary_value)
{
    std::set<int> expected = {2};
    std::set<int> primes = GeneratePrimeNumbersSet(2);

    EXPECT_EQ(expected, primes);
}

TEST (prime, max_boundary_value)
{
    int lastNumber = 99999989;
    int dimension = 5761455;
    std::set<int> primes = GeneratePrimeNumbersSet(100000000);

    EXPECT_EQ(*primes.rbegin(), lastNumber);
    EXPECT_EQ(primes.size(), dimension);
}

GTEST_API_ int main (int argc, char **argv)
{
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}