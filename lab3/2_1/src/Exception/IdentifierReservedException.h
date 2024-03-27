#include <iostream>
#include <exception>

#ifndef INC_2_1_IDENTIFIERRESERVEDEXCEPTION_H
#define INC_2_1_IDENTIFIERRESERVEDEXCEPTION_H


class IdentifierReservedException : public std::exception {

    virtual const char* what() const noexcept override
    {
        return msg.c_str();
    }

public:
    explicit IdentifierReservedException(const std::string& identifier) : msg("Identifier " + identifier + " reserved") {}

private:
    std::string msg;
};


#endif //INC_2_1_IDENTIFIERRESERVEDEXCEPTION_H
