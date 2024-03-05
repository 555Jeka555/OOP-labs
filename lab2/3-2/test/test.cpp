#include <gtest/gtest.h>
#include <sstream>
#include "../src/dictionary.h"

TEST (dict, error_en_to_ru)
{
    std::map<std::string, std::vector<std::string>> enToRuDict = {};
    std::map<std::string, std::vector<std::string>> ruToEnDict = {};
    std::map<std::string, std::vector<std::string>> expectedEnToRuDict = {};
    std::map<std::string, std::vector<std::string>> expectedRuToEnDict = {};

    std::istringstream mockInput("cat\n");
    std::streambuf* origCin = std::cin.rdbuf(mockInput.rdbuf());

    AddTranslate(enToRuDict, ruToEnDict, "cat");

    EXPECT_EQ(enToRuDict, expectedEnToRuDict);
    EXPECT_EQ(ruToEnDict, expectedRuToEnDict);

    std::cin.rdbuf(origCin);
}

TEST (dict, error_ru_to_en)
{
    std::map<std::string, std::vector<std::string>> enToRuDict = {};
    std::map<std::string, std::vector<std::string>> ruToEnDict = {};
    std::map<std::string, std::vector<std::string>> expectedEnToRuDict = {};
    std::map<std::string, std::vector<std::string>> expectedRuToEnDict = {};

    std::istringstream mockInput("кот\n");
    std::streambuf* origCin = std::cin.rdbuf(mockInput.rdbuf());

    AddTranslate(enToRuDict, ruToEnDict, "кот");

    EXPECT_EQ(enToRuDict, expectedEnToRuDict);
    EXPECT_EQ(ruToEnDict, expectedRuToEnDict);

    std::cin.rdbuf(origCin);
}

TEST (dict, add_en_word_with_ru_translates)
{
    std::map<std::string, std::vector<std::string>> enToRuDict = {};
    std::map<std::string, std::vector<std::string>> ruToEnDict = {};
    std::map<std::string, std::vector<std::string>> expectedEnToRuDict = {
            {"cat", {"кот"}},
            {"dog", {"пёс"}},
    };
    std::map<std::string, std::vector<std::string>> expectedRuToEnDict = {
            {"кот", {"cat"}},
            {"пёс", {"dog"}},
    };

    std::istringstream mockInput("кот\nпёс\n");
    std::streambuf* origCin = std::cin.rdbuf(mockInput.rdbuf());

    AddTranslate(enToRuDict, ruToEnDict, "cat");
    AddTranslate(enToRuDict, ruToEnDict, "dog");

    EXPECT_EQ(enToRuDict, expectedEnToRuDict);
    EXPECT_EQ(ruToEnDict, expectedRuToEnDict);

    std::cin.rdbuf(origCin);
}

TEST (dict, add_ru_word_with_en_translates)
{
    std::map<std::string, std::vector<std::string>> enToRuDict = {};
    std::map<std::string, std::vector<std::string>> ruToEnDict = {};
    std::map<std::string, std::vector<std::string>> expectedEnToRuDict = {
            {"cat", {"кот"}},
            {"dog", {"пёс"}},
    };
    std::map<std::string, std::vector<std::string>> expectedRuToEnDict = {
            {"кот", {"cat"}},
            {"пёс", {"dog"}},
    };

    std::istringstream mockInput("cat\ndog\n");
    std::streambuf* origCin = std::cin.rdbuf(mockInput.rdbuf());

    AddTranslate(enToRuDict, ruToEnDict, "кот");
    AddTranslate(enToRuDict, ruToEnDict, "пёс");

    EXPECT_EQ(enToRuDict, expectedEnToRuDict);
    EXPECT_EQ(ruToEnDict, expectedRuToEnDict);

    std::cin.rdbuf(origCin);
}

TEST (dict, add_any_translates_for_word)
{
    std::map<std::string, std::vector<std::string>> enToRuDict = {};
    std::map<std::string, std::vector<std::string>> ruToEnDict = {};
    std::map<std::string, std::vector<std::string>> expectedEnToRuDict = {
            {"cat", {"кот", "кошка"}},
            {"kitty", {"кошка"}},
    };
    std::map<std::string, std::vector<std::string>> expectedRuToEnDict = {
            {"кот", {"cat"}},
            {"кошка", {"cat", "kitty"}},
    };

    std::istringstream mockInput("кот\ncat\nкошка\n");
    std::streambuf* origCin = std::cin.rdbuf(mockInput.rdbuf());

    AddTranslate(enToRuDict, ruToEnDict, "cat");
    AddTranslate(enToRuDict, ruToEnDict, "кошка");
    AddTranslate(enToRuDict, ruToEnDict, "kitty");

    EXPECT_EQ(enToRuDict, expectedEnToRuDict);
    EXPECT_EQ(ruToEnDict, expectedRuToEnDict);

    std::cin.rdbuf(origCin);
}

TEST (dict, add_en_phrase_with_ru_translates)
{
    std::map<std::string, std::vector<std::string>> enToRuDict = {};
    std::map<std::string, std::vector<std::string>> ruToEnDict = {};
    std::map<std::string, std::vector<std::string>> expectedEnToRuDict = {
            {"The Red Square", {"Красная Площадь"}},
            {"Rosa Khutor", {"Роза Xутор"}},
    };
    std::map<std::string, std::vector<std::string>> expectedRuToEnDict = {
            {"Красная Площадь", {"The Red Square"}},
            {"Роза Xутор", {"Rosa Khutor"}},
    };

    std::istringstream mockInput("Красная Площадь\nРоза Xутор\n");
    std::streambuf* origCin = std::cin.rdbuf(mockInput.rdbuf());

    AddTranslate(enToRuDict, ruToEnDict, "The Red Square");
    AddTranslate(enToRuDict, ruToEnDict, "Rosa Khutor");

    EXPECT_EQ(enToRuDict, expectedEnToRuDict);
    EXPECT_EQ(ruToEnDict, expectedRuToEnDict);

    std::cin.rdbuf(origCin);
}

TEST (dict, add_ru_phrase_with_en_translates)
{
    std::map<std::string, std::vector<std::string>> enToRuDict = {};
    std::map<std::string, std::vector<std::string>> ruToEnDict = {};
    std::map<std::string, std::vector<std::string>> expectedEnToRuDict = {
            {"The Red Square", {"Красная Площадь"}},
            {"Rosa Khutor", {"Роза Xутор"}},
    };
    std::map<std::string, std::vector<std::string>> expectedRuToEnDict = {
            {"Красная Площадь", {"The Red Square"}},
            {"Роза Xутор", {"Rosa Khutor"}},
    };

    std::istringstream mockInput("The Red Square\nRosa Khutor\n");
    std::streambuf* origCin = std::cin.rdbuf(mockInput.rdbuf());

    AddTranslate(enToRuDict, ruToEnDict, "Красная Площадь");
    AddTranslate(enToRuDict, ruToEnDict, "Роза Xутор");

    EXPECT_EQ(enToRuDict, expectedEnToRuDict);
    EXPECT_EQ(ruToEnDict, expectedRuToEnDict);

    std::cin.rdbuf(origCin);
}


GTEST_API_ int main (int argc, char **argv)
{
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}