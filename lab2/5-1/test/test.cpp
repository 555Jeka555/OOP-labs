#include <gtest/gtest.h>
#include "../src/parserURL.h"

// http://www.mysite.com/docs/document1.html?page=30&lang=en#title

TEST (parse_url, parse_protocols_success)
{
    Protocol protocol;
    int port;
    std::string host;
    std::string document;
    std::string url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
    bool isParseURL = ParseURL(url, protocol, port, host, document);
    EXPECT_EQ(true, isParseURL);
    EXPECT_EQ(Protocol::HTTP, protocol);

    url = "https://www.mysite.com/docs/document1.html?page=30&lang=en#title";
    isParseURL = ParseURL(url, protocol, port, host, document);
    EXPECT_EQ(true, isParseURL);
    EXPECT_EQ(Protocol::HTTPS, protocol);

    url = "ftp://www.mysite.com/docs/document1.html?page=30&lang=en#title";
    isParseURL = ParseURL(url, protocol, port, host, document);
    EXPECT_EQ(true, isParseURL);
    EXPECT_EQ(Protocol::FTP, protocol);
}

TEST (parse_url, parse_protocols_error)
{
    Protocol protocol;
    int port;
    std::string host;
    std::string document;
    std::string url = "htt://www.mysite.com/docs/document1.html?page=30&lang=en#title";
    bool isParseURL = ParseURL(url, protocol, port, host, document);
    EXPECT_EQ(false, isParseURL);

    url = "://www.mysite.com/docs/document1.html?page=30&lang=en#title";
    isParseURL = ParseURL(url, protocol, port, host, document);
    EXPECT_EQ(false, isParseURL);

    url = "www.mysite.com/docs/document1.html?page=30&lang=en#title";
    isParseURL = ParseURL(url, protocol, port, host, document);
    EXPECT_EQ(false, isParseURL);
}

TEST (parse_url, parse_ports_success)
{
    Protocol protocol;
    int port;
    std::string host;
    std::string document;
    std::string url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
    bool isParseURL =  ParseURL(url, protocol, port, host, document);
    EXPECT_EQ(true, isParseURL);
    EXPECT_EQ(80, port);

    url = "https://www.mysite.com/docs/document1.html?page=30&lang=en#title";
    isParseURL =  ParseURL(url, protocol, port, host, document);
    EXPECT_EQ(true, isParseURL);
    EXPECT_EQ(443, port);

    url = "ftp://www.mysite.com/docs/document1.html?page=30&lang=en#title";
    isParseURL =  ParseURL(url, protocol, port, host, document);
    EXPECT_EQ(true, isParseURL);
    EXPECT_EQ(21, port);

    url = "ftp://www.mysite.com:8000/docs/document1.html?page=30&lang=en#title";
    isParseURL =  ParseURL(url, protocol, port, host, document);
    EXPECT_EQ(true, isParseURL);
    EXPECT_EQ(8000, port);
}

TEST (parse_url, parse_ports_error)
{
    Protocol protocol;
    int port;
    std::string host;
    std::string document;
    std::string url = "http://www.mysite.com:0/docs/document1.html?page=30&lang=en#title";
    bool isParseURL =  ParseURL(url, protocol, port, host, document);
    EXPECT_EQ(false, isParseURL);

    url = "http://www.mysite.com:65536/docs/document1.html?page=30&lang=en#title";
    isParseURL =  ParseURL(url, protocol, port, host, document);
    EXPECT_EQ(false, isParseURL);

    url = "http://www.mysite.com:/docs/document1.html?page=30&lang=en#title";
    isParseURL =  ParseURL(url, protocol, port, host, document);
    EXPECT_EQ(false, isParseURL);

    url = "http://www.mysite.com:cat/docs/document1.html?page=30&lang=en#title";
    isParseURL =  ParseURL(url, protocol, port, host, document);
    EXPECT_EQ(false, isParseURL);
}

TEST (parse_url, parse_host_success)
{
    Protocol protocol;
    int port;
    std::string host;
    std::string document;
    std::string url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
    bool isParseURL =  ParseURL(url, protocol, port, host, document);
    EXPECT_EQ(true, isParseURL);
    EXPECT_EQ("www.mysite.com", host);

    url = "https://www/docs/document1.html?page=30&lang=en#title";
    isParseURL =  ParseURL(url, protocol, port, host, document);
    EXPECT_EQ(true, isParseURL);
    EXPECT_EQ("www", host);
}

TEST (parse_url, parse_host_error)
{
    Protocol protocol;
    int port;
    std::string host;
    std::string document;
    std::string url = "http:///docs/document1.html?page=30&lang=en#title";
    bool isParseURL =  ParseURL(url, protocol, port, host, document);
    EXPECT_EQ(false, isParseURL);
}

TEST (parse_url, parse_document_success)
{
    Protocol protocol;
    int port;
    std::string host;
    std::string document;
    std::string url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
    bool isParseURL =  ParseURL(url, protocol, port, host, document);
    EXPECT_EQ(true, isParseURL);
    EXPECT_EQ("docs/document1.html?page=30&lang=en#title", document);

    url = "http://www.mysite.com/";
    isParseURL =  ParseURL(url, protocol, port, host, document);
    EXPECT_EQ(true, isParseURL);
    EXPECT_EQ("", document);
}

TEST (parse_url, parse_document_error)
{
    Protocol protocol;
    int port;
    std::string host;
    std::string document;
    std::string url = "http://www.mysite.com";
    bool isParseURL =  ParseURL(url, protocol, port, host, document);
    EXPECT_EQ(false, isParseURL);
}

TEST (parse_url, empty_url_error)
{
    Protocol protocol;
    int port;
    std::string host;
    std::string document;
    std::string url;
    bool isParseURL =  ParseURL(url, protocol, port, host, document);
    EXPECT_EQ(false, isParseURL);
}

TEST (parse_url, parse_url_success)
{
    Protocol protocol;
    int port;
    std::string host;
    std::string document;
    std::string url = "http://www.mysite.com:8085/docs/document1.html?page=30&lang=en#title";
    bool isParseURL = ParseURL(url, protocol, port, host, document);
    EXPECT_EQ(true, isParseURL);
    EXPECT_EQ(Protocol::HTTP, protocol);
    EXPECT_EQ("www.mysite.com", host);
    EXPECT_EQ(8085, port);
    EXPECT_EQ("docs/document1.html?page=30&lang=en#title", document);
}


GTEST_API_ int main (int argc, char **argv)
{
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}