#include <iostream>
#include <exception>

#ifndef INC_2_1_IDENTIFIERALREADYEXISTEXCEPTION_H
#define INC_2_1_IDENTIFIERALREADYEXISTEXCEPTION_H


class IdentifierAlreadyExistException : std::exception {
    virtual const char* what() const noexcept override
    {
        return msg.c_str();
    }

public:
    explicit IdentifierAlreadyExistException(const std::string& identifier) : msg("Identifier " + identifier + " already exists") {}

private:
    std::string msg;
};


#endif //INC_2_1_IDENTIFIERALREADYEXISTEXCEPTION_H
