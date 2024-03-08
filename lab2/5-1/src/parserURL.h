#ifndef INC_5_1_PARSERURL_H
#define INC_5_1_PARSERURL_H

#include "stdafx.h"

enum class Protocol
{
    HTTP,
    HTTPS,
    FTP
};

bool ParseURL(std::string const& url, Protocol &  protocol, int & port, std::string & host, std::string & document);
void PrintURLComponents(int & port, std::string & host, std::string & document);

#endif //INC_5_1_PARSERURL_H
