#include "html-decode.h"

const std::string DOUBLE_QUOTATION_MARK_DECODE = "\"";
const std::string APOSTROPHE_DECODE = "'";
const std::string SIGN_LESS_DECODE = "<";
const std::string SIGN_MORE_DECODE = ">";
const std::string AMPERSAND_DECODE_STRING = "&";
const char AMPERSAND_DECODE_CHAR = '&';
const char SEMICOLON = ';';
const std::string DOUBLE_QUOTATION_MARK_ENCODE = "&quot;";
const std::string APOSTROPHE_ENCODE = "&apos;";
const std::string SIGN_LESS_ENCODE = "&lt;";
const std::string SIGN_MORE_ENCODE = "&gt;";
const std::string AMPERSAND_ENCODE = "&amp;";

void AddDecodeEntityToResult(const std::string& entity, std::string& result, int& i, int j)
{
    if (entity == DOUBLE_QUOTATION_MARK_ENCODE)
    {
        result += DOUBLE_QUOTATION_MARK_DECODE;
        i = j;
    }
    else if (entity == APOSTROPHE_ENCODE)
    {
        result += APOSTROPHE_DECODE;
        i = j;
    }
    else if (entity == SIGN_LESS_ENCODE)
    {
        result += SIGN_LESS_DECODE;
        i = j;
    }
    else if (entity == SIGN_MORE_ENCODE)
    {
        result += SIGN_MORE_DECODE;
        i = j;
    }
    else if (entity == AMPERSAND_ENCODE)
    {
        result += AMPERSAND_DECODE_STRING;
        i = j;
    }
    else
    {
        int j = entity.find(AMPERSAND_DECODE_CHAR, 0);
        if (j != std::string::npos)
        {
            result += entity[0];
        }
        else
        {
            result += entity;
            i = j;
        }
    }
}

std::string HtmlDecode(std::string const& encodeHTML)
{
    std::string result;

    for (int i = 0; i < encodeHTML.size(); ++i)
    {
        if (encodeHTML[i] == AMPERSAND_DECODE_CHAR)
        {
            int j = encodeHTML.find(SEMICOLON, i);
            if (j != std::string::npos)
            {
                std::string entity = encodeHTML.substr(i, j - i + 1);
                AddDecodeEntityToResult(entity, result, i, j);
            }
            else
            {
                result += encodeHTML[i];
            }
        }
        else
        {
            result += encodeHTML[i];
        }
    }
    return result;
}