#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "structs.h"
#include "io functions.h"

using namespace std;

void parseUserInput(int &out)
{
    string in;

    getline(cin, in);

    for (int i = 0; i < in.size(); i++) {
        if (in[i] < '0' or in[i]>'9') {
            out = -1;
            return;
        }
    }

    out = stoi(in);
}

void parseUserInput(char &out)
{
    string in;

    getline(cin, in);

    out = in[0];
}

void addWord(vector <string> filenames, int difficulty, QA_PAIR toAdd)
{
    ofstream file;

    file.open(filenames[difficulty - 1], ofstream::app);

    file << toAdd.word << endl;
    file << toAdd.definition << endl;

    file.close();
}

void deleteWord(vector <string> filenames, int difficulty, string toDelete)
{
    ifstream oldFile;
    ofstream updatedFile;
    vector <string> lines;
    string temp;

    oldFile.open(filenames[difficulty - 1]);
    while (oldFile.good()) {
        getline(oldFile, temp);
        if (!temp.size()) break;

        lines.push_back(temp);
    }
    oldFile.close();

    updatedFile.open(filenames[difficulty - 1], ofstream::trunc);
    for (size_t i = 0; i < lines.size(); i++) {
        if (lines[i] == toDelete) {
            i++;
            continue;
        }
        updatedFile << lines[i] << endl;
    }
    updatedFile.close();
}

void readWordsFromFile(vector <string> filenames, int difficulty, vector <string> &words, vector <QA_PAIR> &questionAnswerPairs) {
    ifstream file;
    file.open(filenames[difficulty - 1]);
    string temp;
    QA_PAIR temp2;
    while (file.good()) {
        getline(file, temp);
        if (!temp.size()) break;

        words.push_back(temp);
        temp2.word = temp;

        getline(file, temp);
        if (!temp.size()) break;

        temp2.definition = temp;
        questionAnswerPairs.push_back(temp2);
    }
    file.close();
}
