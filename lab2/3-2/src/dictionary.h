#ifndef INC_3_2_DICTIONARY_H
#define INC_3_2_DICTIONARY_H

#include "stdafx.h"

void InitSessionTranslate(std::ofstream& outputFile);
void SaveTranslate(std::map<std::string, std::vector<std::string>>& toDict,
                   std::map<std::string, std::vector<std::string>>& intoDict,
                   const std::string& enter,
                   const std::string& translate);
void AddTranslate(std::map<std::string, std::vector<std::string>>& enToRuDict,
                  std::map<std::string, std::vector<std::string>>& ruToEnDict,
                  const std::string& enter);

#endif //INC_3_2_DICTIONARY_H
