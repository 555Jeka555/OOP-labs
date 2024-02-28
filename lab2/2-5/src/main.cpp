#include "stdafx.h"
#include "html-decode.h"

int main()
{
    std::string encodeHTML;
    std::getline(std::cin, encodeHTML);
    std::cout << HtmlDecode(encodeHTML) << std::endl;
    return 0;
}
