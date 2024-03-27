#ifndef INC_2_1_CALCULATOR_H
#define INC_2_1_CALCULATOR_H

#include "stdafx.h"
#include "Function.h"
#include "Exception/IdentifierReservedException.h"
#include "Exception/IdentifierAlreadyExistException.h"
#include "Exception/IdentifierNotFoundException.h"

class Calculator {
public:
    void AddVar(const std::string& identifier, std::string value = "nan");

    void AddFunc(const std::string& identifier1,
                 const std::string& identifier2,
                 Operation operation = Operation::NAN,
                 const std::string& identifier3 = "");

    void Print(std::string identifier, std::ostream& cout) const;

    void PrintVars(std::ostream& cout) const;

    void PrintFunctions(std::ostream& cout) const;

private:
    const std::string SEPARATOR_ID_AND_VALUE = ":";
    const std::vector<std::string> IDENTIFIERS_RESERVED = {
            "var",
            "let",
            "fn",
            "print",
            "printvars",
            "printfns",
    };

    std::map<std::string, std::string> m_vars;
    std::map<std::string, std::shared_ptr<Function>> m_funcs;

    void CheckIdentifierNotReserved(const std::string& identifier) const;
    void CheckIdentifierNotAlreadyExist(const std::string& identifier) const;
    void AssertIdentifierNotExist(const std::string& identifier) const;

};


#endif //INC_2_1_CALCULATOR_H
