#include "dictionary.h"

const std::string DEFAULT_DICT_PATH = "../src/dictionary.txt";
const std::string AGREE_CHAR = "y";
const std::string STOP_ENTER = "...";
const std::string SEPARATOR = ", ";
const std::string SEPARATOR_TRANSLATE = ":";
const std::string STRIP_REGEX = " \t\n\r";
const char SEPARATOR_CHAR = ',';
const char SEPARATOR_TRANSLATE_CHAR = ':';
const char SPACE = ' ';
const char APOSTROPHE = '`';
const char QUOT = '\'';
const char DOUBLE_QUOT = '\"';
const char FIRST_CHAR_IN_ALF_LOW = 'a';
const char LAST_CHAR_IN_ALF_LOW = 'z';
const char FIRST_CHAR_IN_ALF_HIGH = 'A';
const char LAST_CHAR_IN_ALF_HIGH = 'Z';

void AddWordsInDicts(std::vector<std::string> words,
                    std::map<std::string, std::vector<std::string>>& enToRuDict,
                    std::map<std::string, std::vector<std::string>>& ruToEnDict)
{
    enToRuDict[words[0]] = {};
    for (int i = 1; i < words.size(); i++)
    {
        enToRuDict[words[0]].push_back(words[i]);
        ruToEnDict[words[i]] = {words[0]};
    }
}

void StripWords(std::vector<std::string>& words)
{
    for (auto &w: words)
    {
        w.erase(0, w.find_first_not_of(STRIP_REGEX));
        w.erase(w.find_last_not_of(STRIP_REGEX) + 1);
    }
}

void ParseWordsByInputFile(std::ifstream& inputFile,
                           std::map<std::string, std::vector<std::string>>& enToRuDict,
                           std::map<std::string, std::vector<std::string>>& ruToEnDict)
{
    std::string line;
    while (std::getline(inputFile, line))
    {
        std::vector<std::string> words;
        std::istringstream iss(line);
        std::string word;
        while (std::getline(iss, word, SEPARATOR_TRANSLATE_CHAR))
        {
            std::istringstream inner_iss(word);
            while (std::getline(inner_iss, word, SEPARATOR_CHAR))
            {
                words.push_back(word);
            }
        }
        if (words.empty())
        {
            continue;
        }

        StripWords(words);
        AddWordsInDicts(words, enToRuDict, ruToEnDict);
    }
}

void ParseInputFile(std::ifstream& inputFile,
                    std::map<std::string, std::vector<std::string>>& enToRuDict,
                    std::map<std::string, std::vector<std::string>>& ruToEnDict)
{
    if (!inputFile.is_open())
    {
        std::ofstream outputFile(DEFAULT_DICT_PATH);
        if (!outputFile.is_open()) {
            throw std::runtime_error("Failed to create file");
        }
    }
    else {
        ParseWordsByInputFile(inputFile, enToRuDict, ruToEnDict);
    }
}

bool IsEnglandString(const std::string& string)
{
    return std::all_of(string.begin(), string.end(),
                       [](char c) {
        return (c >= FIRST_CHAR_IN_ALF_LOW && c <= LAST_CHAR_IN_ALF_LOW)
        || (c >= FIRST_CHAR_IN_ALF_HIGH && c <= LAST_CHAR_IN_ALF_HIGH)
        || c == SPACE
        || c == APOSTROPHE
        || c == QUOT
        || c == DOUBLE_QUOT;
    });
}

std::string ToStingTranslateByDict(const std::vector<std::string>& translateByDict)
{
    std::string result;

    for (int i = 0; i < translateByDict.size(); i++)
    {
        result += translateByDict[i];
        if (i != translateByDict.size() - 1)
        {
            result += SEPARATOR;
        }
    }

    return result;
}

bool FindTranslate(std::map<std::string, std::vector<std::string>>& enToRuDict,
                   std::map<std::string, std::vector<std::string>>& ruToEnDict,
                   const std::string& enter)
{
    if (ruToEnDict.contains(enter))
    {
        std::cout << "Word \"" << enter << "\" save in dict as "
                  << ToStingTranslateByDict(ruToEnDict[enter]) << std::endl;
        return true;
    }
    else if (enToRuDict.contains(enter))
    {
        std::cout << "Word \"" << enter << "\" save in dict as "
                  << ToStingTranslateByDict(enToRuDict[enter]) << std::endl;
        return true;
    }
    return false;
}

void SaveTranslate(std::map<std::string, std::vector<std::string>>& toDict,
                   std::map<std::string, std::vector<std::string>>& intoDict,
                   const std::string& enter,
                   const std::string& translate)
{
    toDict[enter].push_back(translate);
    intoDict[translate].push_back(enter);
    std::cout << "Undefined word \"" << enter << "\" save as \"" << translate << "\"" << std::endl;
}

void AddTranslateEnToRu(std::map<std::string, std::vector<std::string>>& enToRuDict,
                    std::map<std::string, std::vector<std::string>>& ruToEnDict,
                    const std::string& enter)
{
    std::string translate;
    std::cout << "Enter russian word" << std::endl;
    std::getline(std::cin, translate);

    if (translate.empty())
    {
        std::cout << "Word \"" << enter << "\" was ignored" << std::endl;
        return;
    }

    if (IsEnglandString(translate))
    {
        std::cout << "Please enter correct string first in one language, then in another" << std::endl;
        return;
    }

    SaveTranslate(enToRuDict, ruToEnDict, enter, translate);
}

void AddTranslateRuToEn(std::map<std::string, std::vector<std::string>>& enToRuDict,
                    std::map<std::string, std::vector<std::string>>& ruToEnDict,
                    const std::string& enter)
{
    std::string translate;
    std::cout << "Enter england word" << std::endl;
    std::getline(std::cin, translate);

    if (translate.empty())
    {
        std::cout << "Word \"" << enter << "\" was ignored" << std::endl;
        return;
    }

    if (!IsEnglandString(translate))
    {
        std::cout << "Please enter correct string first in one language, then in another" << std::endl;
        return;
    }

    SaveTranslate(ruToEnDict, enToRuDict, enter, translate);
}

void AddTranslate(std::map<std::string, std::vector<std::string>>& enToRuDict,
                  std::map<std::string, std::vector<std::string>>& ruToEnDict,
                  const std::string& enter)
{
    if (IsEnglandString(enter) && !enToRuDict.contains(enter))
    {
        AddTranslateEnToRu(enToRuDict, ruToEnDict, enter);
    }
    else if (!ruToEnDict.contains(enter))
    {
        AddTranslateRuToEn(enToRuDict, ruToEnDict, enter);
    }
}

void SaveDict(std::ofstream& outputFile, const std::map<std::string, std::vector<std::string>>& dict)
{
    std::cout << "Changes have been made to the dictionary. Enter Y or y to save before exiting" << std::endl;
    std::string enter;
    std::getline(std::cin, enter);
    std::transform(enter.begin(), enter.end(), enter.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    if (enter == AGREE_CHAR)
    {
        for (auto & it : dict) {
            const std::string& word = it.first;
            std::vector<std::string> translates = it.second;
            outputFile << word << SEPARATOR_TRANSLATE << ToStingTranslateByDict(translates) << std::endl;
        }
        std::cout << "Changes have been made to the dictionary" << std::endl;
    }
}

void CheckFlushToOutputFile(std::ofstream& outputFile)
{
    if (!outputFile.flush())
    {
        throw std::runtime_error("Failed flush to file");
    }
}

void CheckOpenOutputFile(std::ofstream& outputFile)
{
    if (!outputFile.is_open())
    {
        throw std::runtime_error("Failed to open output file");
    }
}

void InitSessionTranslate(const std::string& dictFileName)
{
    std::map<std::string, std::vector<std::string>> enToRuDict = {};
    std::map<std::string, std::vector<std::string>> ruToEnDict = {};

    std::ifstream inputFile;
    inputFile.open(dictFileName);
    ParseInputFile(inputFile, enToRuDict, ruToEnDict);
    inputFile.close();

    std::ofstream outputFile(dictFileName);
    CheckOpenOutputFile(outputFile);

    while (true)
    {
        std::cout << "Enter word" << std::endl;
        std::string enter;
        std::getline(std::cin, enter);

        if (enter == STOP_ENTER)
        {
            SaveDict(outputFile, enToRuDict);
            CheckFlushToOutputFile(outputFile);
            break;
        }

        bool isFindTranslate = FindTranslate(enToRuDict, ruToEnDict, enter);

        if (!isFindTranslate)
        {
            AddTranslate(enToRuDict, ruToEnDict, enter);
        }
    }
    std::cout << "Bye" << std::endl;
}