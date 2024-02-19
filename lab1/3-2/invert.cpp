#include "stdafx.h"

const char CHAR_NEGATIVE = '-';
const char CHAR_DOT = '.';
const char SPACE = ' ';
const int NUMBER_OF_SIGNIFICANT_DIGITS_AFTER_DECIMAL_POINT = 3;
const int DEFAULT_VALUE_IN_ARRAY = 0;

void CheckValidArgumentCount(const int& argc)
{
    if (argc != 2) {
        throw std::runtime_error("Invalid argument count\n"
                                 "Usage: invert.exe <matrix file.txt>");
    }
}

void CheckValidLineInput(const std::string& line)
{
    bool isMinusFirst = true;
    for (char c : line)
    {
        bool isValidChar = std::isdigit(c) || (c == CHAR_NEGATIVE && isMinusFirst) || c == CHAR_DOT || c == SPACE;
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

std::ifstream GetInputFile(const std::string& inputFileName)
{
    std::ifstream inputFile;
    inputFile.open(inputFileName);
    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open" << inputFileName << " for writing" << std::endl;
    }
    return inputFile;
}

void AppendLineToMatrix(std::vector<std::vector<float>>& matrix, const std::string& line)
{
    std::istringstream iss(line);
    std::vector<float> numbers;
    float number;

    while (iss >> number)
    {
        numbers.push_back(number);
    }

    if (numbers.size() != 3)
    {
        throw std::runtime_error("Invalid input matrix. Matrix must be 3x3");
    }

    matrix.push_back(numbers);
}

std::vector<std::vector<float>> GetMatrixByFile(std::istream& inputFile)
{
    std::vector<std::vector<float>> matrix;
    std::string line;
    while (std::getline(inputFile, line))
    {
        CheckValidLineInput(line);
        AppendLineToMatrix(matrix, line);
    }
    return matrix;
}

float GetDeterminantOfMatrixX2(const std::vector<std::vector<float>>& matrix)
{
    return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
}

std::vector<std::vector<float>> GetMatrixByMinor(const std::vector<std::vector<float>>& matrix, int i, int j)
{
    std::vector<std::vector<float>> matrixByMinor(2, std::vector<float>(2, DEFAULT_VALUE_IN_ARRAY));
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

float GetDeterminantOfMatrixX3(const std::vector<std::vector<float>>& matrix)
{
    float determinant = 0;
    for (int i = 0; i < 3; i++)
    {
        std::vector<std::vector<float>> matrixByMinor = GetMatrixByMinor(matrix, 0, i);
        determinant += (float)(i == 1 ? -1 : 1) * matrix[0][i] * GetDeterminantOfMatrixX2(matrixByMinor);
    }
    return determinant;
}

std::vector<std::vector<float>> GetTransposedMatrix(const std::vector<std::vector<float>>& matrix)
{
    int dimension = static_cast<int>(matrix.size());
    std::vector<std::vector<float>> transposedMatrix(dimension, std::vector<float>(dimension, DEFAULT_VALUE_IN_ARRAY));
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix.size(); j++)
        {
            std::vector<std::vector<float>> matrixByMinor = GetMatrixByMinor(matrix, i, j);
            transposedMatrix[j][i] = (float)std::pow(-1, i+j) * GetDeterminantOfMatrixX2(matrixByMinor);
        }
    }

    return transposedMatrix;
}

void mulMatrixByNumber(std::vector<std::vector<float>>& matrix, const float& number)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix.size(); j++)
        {
            matrix[i][j] = matrix[i][j]*number;
        }
    }
}

int main(int argc, char *argv[])
{
    try
    {
        CheckValidArgumentCount(argc);
        std::ifstream inputFile = GetInputFile(argv[1]);
        std::vector<std::vector<float>> matrix = GetMatrixByFile(inputFile);
        float determinant = GetDeterminantOfMatrixX3(matrix);
        std::vector<std::vector<float>> transposedMatrix = GetTransposedMatrix(matrix);
        mulMatrixByNumber(transposedMatrix, 1/determinant);

        for (const auto& row : transposedMatrix) {
            for (const auto& element : row) {
                std::cout << std::setprecision(NUMBER_OF_SIGNIFICANT_DIGITS_AFTER_DECIMAL_POINT)
                    << std::fixed << element << "\t";
            }
            std::cout << std::endl;
        }
    }
    catch (const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
