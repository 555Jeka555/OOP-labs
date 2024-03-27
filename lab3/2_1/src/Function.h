#ifndef INC_2_1_FUNCTION_H
#define INC_2_1_FUNCTION_H

#include <utility>

#include "Operation.h"
#include "stdafx.h"

class Function {
public:
    std::string Execute() const;

    Function() = default;

    explicit Function(const std::vector<std::string>& attributes, const Operation& operation = Operation::NAN) {
        m_attributes = std::move(attributes);
        m_operation = operation;
    }

private:
    const std::string DEFAULT_NULL = "nan";

    Operation m_operation;
    std::vector<std::string> m_attributes;
};


#endif //INC_2_1_FUNCTION_H
