#include "Calculator.h"

void Calculator::AddVar(const std::string& identifier, std::string value)
{
    CheckIdentifierNotReserved(identifier);
    CheckIdentifierNotAlreadyExist(identifier);

    m_vars[identifier] = std::move(value);
}

void Calculator::AddFunc(const std::string& identifier1, const std::string& identifier2, Operation operation, const std::string& identifier3)
{
    CheckIdentifierNotReserved(identifier1);
    CheckIdentifierNotAlreadyExist(identifier1);

    Function function = Function({identifier2, identifier3}, operation);
    m_funcs[identifier1] = std::make_shared<Function>(function);
}

void Calculator::Print(const std::string identifier, std::ostream& cout) const
{
    if (m_vars.contains(identifier))
    {
        cout << identifier << SEPARATOR_ID_AND_VALUE << m_vars.at(identifier) << std::endl;
        return;
    }
    else if (m_funcs.contains(identifier))
    {
        cout << identifier << SEPARATOR_ID_AND_VALUE << m_funcs.at(identifier)->Execute() << std::endl;
        return;
    }

    AssertIdentifierNotExist(identifier);
}

void Calculator::PrintVars(std::ostream& cout) const {
    for (const auto& var : m_vars)
    {
        cout << var.first << SEPARATOR_ID_AND_VALUE << var.second << std::endl;
    }
}

void Calculator::PrintFunctions(std::ostream& cout) const {
    for (const auto& func : m_funcs) {
        cout << func.first << SEPARATOR_ID_AND_VALUE << func.second->Execute() << std::endl;
    }
}

void Calculator::CheckIdentifierNotReserved(const std::string &identifier) const
{
    auto it = std::find(IDENTIFIERS_RESERVED.begin(), IDENTIFIERS_RESERVED.end(), identifier);

    if (it != IDENTIFIERS_RESERVED.end())
    {
        throw IdentifierReservedException(identifier);
    }
}

void Calculator::CheckIdentifierNotAlreadyExist(const std::string &identifier) const
{
    if (m_vars.contains(identifier) || m_funcs.contains(identifier))
    {
        throw IdentifierAlreadyExistException(identifier);
    }
}

void Calculator::AssertIdentifierNotExist(const std::string &identifier) const
{
    throw IdentifierNotFoundException(identifier);
}

