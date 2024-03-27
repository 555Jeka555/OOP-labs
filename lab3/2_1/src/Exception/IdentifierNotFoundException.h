#include <iostream>
#include <exception>

#ifndef INC_2_1_IDENTIFIERNOTFOUNDEXCEPTION_H
#define INC_2_1_IDENTIFIERNOTFOUNDEXCEPTION_H


class IdentifierNotFoundException : std::exception {
    virtual const char* what() const noexcept override
    {
        return msg.c_str();
    }

public:
    explicit IdentifierNotFoundException(const std::string& identifier) : msg("Identifier " + identifier + " not found") {}

private:
    std::string msg;
};


#endif //INC_2_1_IDENTIFIERNOTFOUNDEXCEPTION_H
