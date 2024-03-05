#ifndef INC_3_2_DICTIONARY_H
#define INC_3_2_DICTIONARY_H

#include "stdafx.h"

void InitSessionTranslate(std::ofstream& outputFile);
void AddTranslate(std::map<std::string, std::vector<std::string>>& enToRuDict,
                  std::map<std::string, std::vector<std::string>>& ruToEnDict,
                  const std::string& enter);

#endif //INC_3_2_DICTIONARY_H
