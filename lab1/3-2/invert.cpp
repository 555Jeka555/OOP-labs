#include "stdafx.h"

const char CHAR_NEGATIVE = '-';
const char CHAR_POINT_DECIMAL = '.';
const char SPACE = ' ';
const int NUMBER_OF_SIGNIFICANT_DIGITS_AFTER_DECIMAL_POINT = 3;
const int DEFAULT_VALUE_IN_ARRAY = 0;
const char SEPARATOR_TO_PRINT_MATRIX = ' ';
const int DIMENSION_MATRIX_OF_3 = 3;
const int DIMENSION_MATRIX_OF_2 = 2;

void CheckValidArgumentCount(const int argc)
{
    if (argc != 2)
    {
        throw std::runtime_error("Invalid argument count\n"
                                 "Usage: invert.exe <matrix file.txt>");
    }
}

void CheckValidLineInput(const std::string& line)
{
    bool isMinusFirst = true;
    for (char c : line)
    {
        bool isValidChar = std::isdigit(c) || (c == CHAR_NEGATIVE && isMinusFirst) || c == CHAR_POINT_DECIMAL || c == SPACE;
        if (!isValidChar)
        {
            throw std::runtime_error("Invalid input matrix. Matrix must consist of digits");
        }

        isMinusFirst = false;
        if (c == SPACE)
        {
            isMinusFirst = true;
        }
    }
}

void CheckDeterminantIsZero(const float determinant)
{
    if (determinant == 0)
    {
        throw std::runtime_error("The inverse matrix cannot be found, since the determinant of the matrix is zero");
    }
}

void CheckValidDimensionMatrixOf3(int index)
{
    if (index != DIMENSION_MATRIX_OF_3)
    {
        throw std::runtime_error("Invalid input matrix. Matrix must be 3x3");
    }
}

std::ifstream GetInputFile(const std::string& inputFileName)
{
    std::ifstream inputFile;
    inputFile.open(inputFileName);
    if (!inputFile.is_open())
    {
        throw std::runtime_error( "Failed to open " + inputFileName + " for writing");
    }
    return inputFile;
}

void AppendLineToMatrix(
        std::array<std::array<float, DIMENSION_MATRIX_OF_3>, DIMENSION_MATRIX_OF_3>& matrix,
        const std::string& line,
        int i
        )
{
    std::istringstream iss(line);
    std::array<float, DIMENSION_MATRIX_OF_3> numbers = {DEFAULT_VALUE_IN_ARRAY};
    float number;

    int j = 0;
    while (iss >> number)
    {
        numbers[j] = number;
        j++;
    }

    CheckValidDimensionMatrixOf3(j);

    matrix[i] = numbers;
}

std::array<std::array<float, DIMENSION_MATRIX_OF_3>, DIMENSION_MATRIX_OF_3> GetMatrixByFile(std::istream& inputFile)
{
    std::array<std::array<float, DIMENSION_MATRIX_OF_3>, DIMENSION_MATRIX_OF_3> matrix = {DEFAULT_VALUE_IN_ARRAY};
    std::string line;

    int i = 0;
    while (std::getline(inputFile, line))
    {
        CheckValidLineInput(line);
        AppendLineToMatrix(matrix, line, i);
        i++;
    }
    CheckValidDimensionMatrixOf3(i);

    return matrix;
}

float GetDeterminantOfMatrixX2(const std::array<std::array<float, DIMENSION_MATRIX_OF_2>, DIMENSION_MATRIX_OF_2>& matrix)
{
    return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
}

std::array<std::array<float, DIMENSION_MATRIX_OF_2>, DIMENSION_MATRIX_OF_2> GetMatrixByMinor(
        const std::array<std::array<float, DIMENSION_MATRIX_OF_3>, DIMENSION_MATRIX_OF_3>& matrix,
        const int i,
        const int j
        )
{
    std::array<std::array<float, DIMENSION_MATRIX_OF_2>, DIMENSION_MATRIX_OF_2> matrixByMinor = {DEFAULT_VALUE_IN_ARRAY};

    for (int majorX = 0, minorX = 0; majorX < 3; majorX++)
    {
        if (majorX == i)
        {
            continue;
        }
        for (int majorY = 0, minorY = 0; majorY < 3; majorY++)
        {
            if (majorY == j)
            {
                continue;
            }
            matrixByMinor[minorX][minorY] = matrix[majorX][majorY];
            minorY++;
        }
        minorX++;
    }
    return matrixByMinor;
}

float GetDeterminantOfMatrixX3(const std::array<std::array<float, DIMENSION_MATRIX_OF_3>, DIMENSION_MATRIX_OF_3>& matrix)
{
    float determinant = 0;
    for (int i = 0; i < 3; i++)
    {
        std::array<std::array<float, DIMENSION_MATRIX_OF_2>, DIMENSION_MATRIX_OF_2> matrixByMinor = GetMatrixByMinor(matrix, 0, i);
        determinant += static_cast<float>(i == 1 ? -1 : 1) * matrix[0][i] * GetDeterminantOfMatrixX2(matrixByMinor);
    }
    return determinant;
}

std::array<std::array<float, DIMENSION_MATRIX_OF_3>, DIMENSION_MATRIX_OF_3> GetTransposedUnionMatrix
(const std::array<std::array<float, DIMENSION_MATRIX_OF_3>, DIMENSION_MATRIX_OF_3>& matrix)
{
    std::array<std::array<float, DIMENSION_MATRIX_OF_3>, DIMENSION_MATRIX_OF_3> transposedMatrix = {DEFAULT_VALUE_IN_ARRAY};

    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix.size(); j++)
        {
            std::array<std::array<float, DIMENSION_MATRIX_OF_2>, DIMENSION_MATRIX_OF_2> matrixByMinor = GetMatrixByMinor(matrix, i, j);
            transposedMatrix[j][i] = static_cast<float>(std::pow(-1, i+j)) * GetDeterminantOfMatrixX2(matrixByMinor);
        }
    }
    return transposedMatrix;
}

void MulMatrixByNumber(std::array<std::array<float, DIMENSION_MATRIX_OF_3>, DIMENSION_MATRIX_OF_3>& matrix, const float number)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix.size(); j++)
        {
            matrix[i][j] = matrix[i][j]*number;
        }
    }
}

void HandlerNegativeZeroWithNumbersDecimalPoint(std::stringstream& ss)
{
    std::string negZeroWithNumbersDecimalPoint = "-0";
    
    for (int i = 0; i < NUMBER_OF_SIGNIFICANT_DIGITS_AFTER_DECIMAL_POINT; i++)
    {
        if (i == 0)
        {
            negZeroWithNumbersDecimalPoint += CHAR_POINT_DECIMAL;
        }
        negZeroWithNumbersDecimalPoint += "0";
    }

    if (ss.str() == negZeroWithNumbersDecimalPoint)
    {
        ss.str(negZeroWithNumbersDecimalPoint.substr(1, negZeroWithNumbersDecimalPoint.size() - 1));
    }
}

void PrintMatrix(std::array<std::array<float, DIMENSION_MATRIX_OF_3>, DIMENSION_MATRIX_OF_3>& matrix)
{
    for (int i = 0; i < DIMENSION_MATRIX_OF_3; i++) {
        int elementIndex = 0;
        for (int j = 0; j < DIMENSION_MATRIX_OF_3; j++) {
            std::stringstream ss;
            ss << std::setprecision(NUMBER_OF_SIGNIFICANT_DIGITS_AFTER_DECIMAL_POINT) << std::fixed << matrix[i][j];
            HandlerNegativeZeroWithNumbersDecimalPoint(ss);
            std::cout << ss.str();

            elementIndex++;
            if (elementIndex <= matrix[i].size() - 1)
            {
                std::cout << SEPARATOR_TO_PRINT_MATRIX;
            }
        }
        std::cout << std::endl;
    }
}

std::array<std::array<float, DIMENSION_MATRIX_OF_3>, DIMENSION_MATRIX_OF_3> InvertMatrixX3(std::ifstream& inputFile)
{
    std::array<std::array<float, DIMENSION_MATRIX_OF_3>, DIMENSION_MATRIX_OF_3> matrix = GetMatrixByFile(inputFile);

    float determinant = GetDeterminantOfMatrixX3(matrix);
    CheckDeterminantIsZero(determinant);

    float multiplier = 1/determinant;
    std::array<std::array<float, DIMENSION_MATRIX_OF_3>, DIMENSION_MATRIX_OF_3> transposedMatrix = GetTransposedUnionMatrix(matrix);

    MulMatrixByNumber(transposedMatrix, multiplier);

    return transposedMatrix;
}

//TODO: тест на переполнение
int main(int argc, char *argv[])
{
    try
    {
        CheckValidArgumentCount(argc);
        std::ifstream inputFile = GetInputFile(argv[1]);
        std::array<std::array<float, DIMENSION_MATRIX_OF_3>, DIMENSION_MATRIX_OF_3> matrix = InvertMatrixX3(inputFile);
        PrintMatrix(matrix);
    }
    catch (const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
