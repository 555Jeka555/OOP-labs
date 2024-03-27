#include "Function.h"

std::string Function::Execute() const
{
    double resultOfCalculations;
    switch (m_operation)
    {
        case (Operation::ADD):
            resultOfCalculations = std::stoi(m_attributes[0]) + std::stoi(m_attributes[1]);
        case Operation::SUB:
            resultOfCalculations = std::stoi(m_attributes[0]) - std::stoi(m_attributes[1]);
        case Operation::MUL:
            resultOfCalculations = std::stoi(m_attributes[0]) * std::stoi(m_attributes[1]);
        case Operation::DIV:
            resultOfCalculations = std::stoi(m_attributes[0]) / std::stoi(m_attributes[1]);
        case Operation::NAN:
            return m_attributes[0];
    }

    return std::to_string(resultOfCalculations);
}
