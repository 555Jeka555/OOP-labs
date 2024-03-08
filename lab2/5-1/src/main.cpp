#include "parserURL.h"

const std::string STOP_ENTER = "exit";

int main() {
    while (true)
    {
        std::string url;
        std::getline(std::cin, url);

        if (url == STOP_ENTER) {
            break;
        }

        Protocol protocol;
        int port;
        std::string host;
        std::string document;

        bool isParseURL = ParseURL(url, protocol, port, host, document);

        if (isParseURL)
        {
            PrintURLComponents(port, host, document);
        }
        else
        {
            std::cout << "Invalid url" << std::endl;
        }
    }



    return 0;
}
