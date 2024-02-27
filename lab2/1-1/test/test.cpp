#include <gtest/gtest.h>
#include "../src/arithmetic-mean.h"

TEST (handle_numbers_by_arithmetic_mean, handle_pos)
{
    std::vector<float> numbers = {1, 2, 3, 4, 5};
    std::vector<float> expected = {4, 5, 6, 7, 8};

    HandleNumbersByArithmeticMean(numbers);

    for (int i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(expected[i], numbers[i]);
    }
}

GTEST_API_ int main (int argc, char **argv)
{
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}