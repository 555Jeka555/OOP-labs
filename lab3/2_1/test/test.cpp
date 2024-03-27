#include <gtest/gtest.h>
#include <sstream>
#include "../src/Calculator.h"

const std::string SEPARATOR_ID_AND_VALUE = ":";

TEST (calc, init_nan_var_success)
{
    Calculator calculator;
    std::string var = "x";
    std::string expectedValue = "nan";
    std::ostringstream mockOutput;
    std::streambuf* oldCout = std::cout.rdbuf(mockOutput.rdbuf());

    calculator.AddVar(var);
    calculator.Print(var, mockOutput);

    std::cout.rdbuf(oldCout);

    EXPECT_EQ(mockOutput.str(), var + SEPARATOR_ID_AND_VALUE + expectedValue + "\n");
}

TEST (calc, init_nan_var_reserved_error)
{
    Calculator calculator;
    std::string var = "printfns";

    EXPECT_THROW(calculator.AddVar(var), IdentifierReservedException);
}

TEST (calc, init_nan_var_already_exist_error)
{
    Calculator calculator;
    std::string var = "x";

    calculator.AddVar(var);
    EXPECT_THROW(calculator.AddVar(var), IdentifierAlreadyExistException);

    std::string func = "y";
    calculator.AddFunc(func, var);
    var = "y";
    EXPECT_THROW(calculator.AddVar(var), IdentifierAlreadyExistException);
}

GTEST_API_ int main (int argc, char **argv)
{
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}