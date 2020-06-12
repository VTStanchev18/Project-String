#pragma once
#include <vector>
#include <string>
#include "structs.h"

void parseUserInput(int &out);
void parseUserInput(char &out);
void addWord(std::vector <std::string> filenames, int difficulty, QA_PAIR toAdd);
void deleteWord(std::vector <std::string> filenames, int difficulty, std::string toDelete);
void readWordsFromFile(std::vector <std::string> filenames, int difficulty, std::vector <std::string> &words, std::vector <QA_PAIR> &questionAnswerPairs);
