#include "parserURL.h"

const std::string PATTERN_TO_URL = R"(^(https?|ftp):\/\/([^\/:]+)(?::(\d+))?\/(.*)$)";
const int PORT_MIN = 1;
const int PORT_MAX = 65535;
const std::string HTTP_STRING = "http";
const std::string HTTPS_STRING = "https";
const std::string FTP_STRING = "ftp";
const int DEFAULT_HTTP_PORT = 80;
const int DEFAULT_HTTPS_PORT = 443;
const int DEFAULT_FTP_PORT = 21;

bool ParseProtocol(const std::string& protocolParsed, Protocol &  protocol)
{
    if (protocolParsed == HTTP_STRING)
    {
        protocol = Protocol::HTTP;
        return true;
    }
    else if (protocolParsed == HTTPS_STRING)
    {
        protocol = Protocol::HTTPS;
        return true;
    }
    else if (protocolParsed == FTP_STRING)
    {
        protocol = Protocol::FTP;
        return true;
    }
    return false;
}

bool ParseHost(const std::string& hostParsed, std::string & host)
{
    if (hostParsed.empty())
    {
        return false;
    }

    host = hostParsed;
    return true;
}

bool CheckValidPort(const std::string& portParsed, int & port)
{
    try
    {
        int portParsedInt = std::stoi(portParsed);

        if (portParsedInt < PORT_MIN || portParsedInt > PORT_MAX)
        {
            return false;
        }

        port = portParsedInt;
        return true;
    }
    catch (const std::runtime_error &e)
    {
        return false;
    }
}

bool ParsePort(const std::string& portParsed, Protocol &  protocol, int & port)
{
    if (portParsed.empty())
    {
        if (protocol == Protocol::HTTP)
        {
            port = DEFAULT_HTTP_PORT;
            return true;
        }
        else if (protocol == Protocol::HTTPS)
        {
            port = DEFAULT_HTTPS_PORT;
            return true;
        }
        else if (protocol == Protocol::FTP)
        {
            port = DEFAULT_FTP_PORT;
            return true;
        }
    }

    return CheckValidPort(portParsed, port);
}

bool ParseURL(std::string const& url, Protocol &  protocol, int & port, std::string & host, std::string & document)
{
    std::regex pattern(PATTERN_TO_URL);
    std::smatch matches;

    if (std::regex_match(url, matches, pattern))
    {
        bool isProtocolParse = ParseProtocol(matches[1], protocol);
        bool isHostParse = ParseHost(matches[2], host);
        bool isPortParse = ParsePort(matches[3], protocol, port);
        document = matches[4];
        return isProtocolParse && isHostParse && isPortParse;
    }
    return false;
}

void PrintURLComponents(int & port, std::string & host, std::string & document)
{
    std::cout << "HOST: " <<  host << std::endl;
    std::cout << "PORT: " <<  port << std::endl;
    std::cout << "DOC: " <<  document << std::endl;
}
