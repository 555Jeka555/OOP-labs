#include <gtest/gtest.h>
#include "../src/arithmetic-mean.h"

double GetEpsilon(double number)
{
    std::string numberString = std::to_string(number);
    int dotPosition = numberString.find('.');
    if (dotPosition == std::string::npos)
    {
        return 0;
    }
    int countDecimalPlaces = numberString.size() - dotPosition - 1;

    return std::pow(10, (-1 * countDecimalPlaces));
}

TEST (handle_numbers_by_arithmetic_mean, handle_pos_numbers)
{
    std::vector<double> numbers = {1, 2, 3, 4, 5};
    std::vector<double> expected = {4, 5, 6, 7, 8};

    HandleNumbersByArithmeticMean(numbers);

    for (int i = 0; i < expected.size(); ++i)
    {
        EXPECT_EQ(expected[i], numbers[i]);
    }
}

TEST (handle_numbers_by_arithmetic_mean, handle_neg_numbers)
{
    std::vector<double> numbers = {-1, -2, -3, -4, -5};
    std::vector<double> expected = {-1, -2, -3, -4, -5};

    HandleNumbersByArithmeticMean(numbers);

    for (int i = 0; i < expected.size(); ++i)
    {
        EXPECT_EQ(expected[i], numbers[i]);
    }
}

TEST (handle_numbers_by_arithmetic_mean, handle_empty_numbers)
{
    std::vector<double> numbers = {};

    HandleNumbersByArithmeticMean(numbers);

    EXPECT_TRUE(numbers.empty());
}

TEST (handle_numbers_by_arithmetic_mean, handle_one_pos_number_in_neg_numbers)
{
    std::vector<double> numbers = {-1, -2, -3, -4, 5};
    std::vector<double> expected = {4, 3, 2, 1, 10};

    HandleNumbersByArithmeticMean(numbers);

    for (int i = 0; i < expected.size(); ++i)
    {
        EXPECT_EQ(expected[i], numbers[i]);
    }
}

TEST (handle_numbers_by_arithmetic_mean, handle_double_numbers_by_1_count_places)
{
    std::vector<double> numbers = {1.5, -2.5, 4.5};
    std::vector<double> expected = {4.5, 0.5, 7.5};

    HandleNumbersByArithmeticMean(numbers);

    for (int i = 0; i < expected.size(); ++i)
    {
        EXPECT_NEAR(expected[i], numbers[i], GetEpsilon(expected[i]));
    }
}

TEST (handle_numbers_by_arithmetic_mean, handle_double_numbers_by_3_count_places)
{
    std::vector<double> numbers = {-1., 0., 2.5, 3.005, -.9};
    std::vector<double> expected = {1.7525, 2.7525, 5.2525, 5.7575, 1.8525};

    HandleNumbersByArithmeticMean(numbers);

    for (int i = 0; i < expected.size(); ++i)
    {
        EXPECT_NEAR(expected[i], numbers[i], GetEpsilon(expected[i]));
    }
}

TEST (handle_numbers_by_arithmetic_mean, handle_sort_numbers)
{
    std::vector<double> numbers = {-1., 0., 2.5, 3.005, -.9};
    std::vector<double> expected = {-1, -0.9, 0, 2.5, 3.005};

    SortNumbers(numbers);

    for (int i = 0; i < expected.size(); ++i)
    {
        EXPECT_NEAR(expected[i], numbers[i], GetEpsilon(expected[i]));
    }
}


GTEST_API_ int main (int argc, char **argv)
{
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}