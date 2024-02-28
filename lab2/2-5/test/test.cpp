#include <gtest/gtest.h>
#include "../src/html-decode.h"

TEST (html_decode, decode_with_all_entities)
{
    std::string encodeHTML = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
    std::string expectedDecodeHTML = "Cat <says> \"Meow\". M&M's";
    EXPECT_EQ(expectedDecodeHTML, HtmlDecode(encodeHTML));
}

TEST (html_decode, decode_all_entities_together)
{
    std::string encodeHTML = "&lt;&gt;&quot;&quot;&amp;&apos;";
    std::string expectedDecodeHTML = "<>\"\"&'";
    EXPECT_EQ(expectedDecodeHTML, HtmlDecode(encodeHTML));
}

TEST (html_decode, decode_with_all_entities_invalid)
{
    std::string encodeHTML = "&lt&gt&quot&quot&amp&apos";
    std::string expectedDecodeHTML = "&lt&gt&quot&quot&amp&apos";
    EXPECT_EQ(expectedDecodeHTML, HtmlDecode(encodeHTML));

    encodeHTML = "lt;gt;quot;quot;amp;apos;";
    expectedDecodeHTML = "lt;gt;quot;quot;amp;apos;";
    EXPECT_EQ(expectedDecodeHTML, HtmlDecode(encodeHTML));

    encodeHTML = "&ltgt;quot;&quotamp;apos;";
    expectedDecodeHTML = "&ltgt;quot;&quotamp;apos;";
    EXPECT_EQ(expectedDecodeHTML, HtmlDecode(encodeHTML));
}

TEST (html_decode, decode_empty_html)
{
    std::string encodeHTML;
    std::string expectedDecodeHTML;
    EXPECT_EQ(expectedDecodeHTML, HtmlDecode(encodeHTML));
}

GTEST_API_ int main (int argc, char **argv)
{
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}