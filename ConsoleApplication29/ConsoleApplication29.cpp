﻿#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>
#include <cctype>

using namespace std;

//question-answer pair
struct QA_PAIR {
    string word, definition;
};

void parseUserInput(int& out)
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

// function for checking whether user's answer is correct
bool isCorrect(vector <string> answerPool, QA_PAIR currentQuestion, int answer) {
    if (answer == answerPool.size() + 1) {
        if (find(answerPool.begin(), answerPool.end(), currentQuestion.word) == answerPool.end()) {
            return true;
        }
        return false;
    }
    if (answerPool[answer-1] == currentQuestion.word) {
        return true;
    }
    return false;
}

void readWordsFromFile(vector <string> filenames, int difficulty, vector <string> &words, vector <QA_PAIR> &questionAnswerPairs) {
    ifstream file;
    file.open(filenames[difficulty - 1]);
    string temp;
    QA_PAIR temp2;
    while (file.good()) {
        getline(file,temp);
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

// function for the easy words of our program
void runQuiz(vector <string> filenames, int difficulty)
{
    vector <string> words;
    vector <QA_PAIR> questionAnswerPairs;
    vector <string> answerPool;
    int userAnswer;
    auto rng = default_random_engine(time(0));
    int j;
    int correctAnswers = 0;
    readWordsFromFile(filenames, difficulty, words, questionAnswerPairs);
    shuffle(questionAnswerPairs.begin(), questionAnswerPairs.end(), rng);
    for (int i = 0; i < 4; i++) {
        shuffle(words.begin(), words.end(), rng);
        
        answerPool.clear();

        for (int j = 0; j < 4; j++) {
            answerPool.push_back(words[j]);
        }
        shuffle(answerPool.begin(), answerPool.end(), rng);

        cout << endl << questionAnswerPairs[i].definition << endl;
        for (j = 0; j < 4; j++) {
            cout << j + 1 << ". " << answerPool[j] << endl;
        }
        cout << j + 1 << ". " << "None of the above\n";

        cout << "\n Enter your answer: ";
        parseUserInput(userAnswer);
        if (userAnswer<1 or userAnswer>j + 1) {
            i--;
            cout << "\nPlease enter a valid number!!!\n";
            continue;
        }
        if (isCorrect(answerPool, questionAnswerPairs[i],userAnswer)) {
            cout << "\n Great!!!\n\n";
            correctAnswers++;
        }
        else
        {
            cout << "\n Dumbass!!!\n\n";
        }
    }
    cout << "\n You guessed " << correctAnswers << " out of " << 4 << endl;
}

void addWord(vector <string> filenames, int difficulty, QA_PAIR toAdd)
{
    ofstream file;

    file.open(filenames[difficulty - 1], ofstream::app);

    file << toAdd.word << endl;
    file << toAdd.definition << endl;

    file.close();
}

void showAddMenu(vector <string> filenames)
{
    int difficulty;
    QA_PAIR temp;

    cout << "--- Add a word ---\n\n";
    cout << "1. Add to easy words\n";
    cout << "2. Add to advanced words\n";
    cout << "Enter option from the menu by typing a number: ";
    parseUserInput(difficulty);

    if (difficulty < 1 or difficulty > 2) return;

    cout << "Enter new word: ";
    getline(cin, temp.word);

    cout << "Enter definition for \"" << temp.word << "\":\n";
    getline(cin, temp.definition);

    addWord(filenames, difficulty, temp);
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

void showDeleteMenu(vector <string> filenames)
{
    int difficulty;
    string word;

    cout << "--- Delete a word ---\n\n";
    cout << "1. Delete from easy words\n";
    cout << "2. Delete from advanced words\n";
    cout << "Enter option from the menu by typing a number: ";
    parseUserInput(difficulty);

    if (difficulty < 1 or difficulty > 2) return;

    cout << "Enter word to delete: ";
    getline(cin, word);

    deleteWord(filenames, difficulty, word);
}

void showBrowseMenu(vector <string> filenames)
{
    ifstream oldFile;
    ofstream updatedFile;
    vector <string> lines;
    string temp;
    char choice;
    int difficulty;

    cout << "--- Browse Words ---\n\n";
    cout << "1. Browse easy words\n";
    cout << "2. Browse advanced words\n";
    cout << "Enter option from the menu by typing a number: ";
    parseUserInput(difficulty);

    if (difficulty < 1 or difficulty > 2) return;

    oldFile.open(filenames[difficulty - 1]);
    while (oldFile.good()) {
        getline(oldFile, temp);
        if (!temp.size()) break;

        lines.push_back(temp);
    }
    oldFile.close();

    for (size_t i = 0; i < lines.size(); i+=2) {
        cout << lines[i] << ":\n";
        cout << lines[i+1] << endl;
        cout << "Do you want to delete this word? (y/n) ";
        parseUserInput(choice);
        if (tolower(choice) == 'y') {
            lines.erase(lines.begin() + i, lines.begin() + i + 2);
            i -= 2;
        }
    }

    updatedFile.open(filenames[difficulty - 1], ofstream::trunc);
    for (size_t i = 0; i < lines.size(); i++) {
        updatedFile << lines[i] << endl;
    }
    updatedFile.close();
}

bool showEditMenu(vector <string> filenames)
{
    int userInput;

    cout << "---- Editing Menu ----\n\n";
    cout << "1. Add a word\n";
    cout << "2. Delete a specific word\n";
    cout << "3. Browse words\n";
    cout << "4. Return to Main Menu\n";
    cout << "Enter option from the menu by typing a number: ";
    parseUserInput(userInput);

    switch (userInput) {
        case 1:
            showAddMenu(filenames);
            break;
        case 2:
            showDeleteMenu(filenames);
            break;
        case 3:
            showBrowseMenu(filenames);
            break;
        case 4:
            return false;
        default:
            cout << "\nPlease enter a valid option!\n";
            break;
    }

    return true;
}

void editMode(vector <string> filenames) {
    while (showEditMenu(filenames));
}
// function for displaying greetings
void showInitialGreeting()
{
    cout << "\n                                         Wordy\n";
    cout << "  Welcome to our game called Wordy.\n";
    cout << "  Thank you for choosing our software!\n";
    cout << "  Please refer to the Documentation for a more detailed explanation about using the program.\n";
    cout << "  Our Team takes no responsibility for misuse of the program.\n\n";
}
// function for displaying goodbye message
void showGoodbyeMessage()
{
    cout << "\n  Thank you for using our game Wordy!\n\n";
    cout << "  Copyright (c) 2020 team\n";;
}
// function for our menu from which the player can chose difficulty, see his score or exit the program 
bool doShowMenu(vector <string> filenames)
{
    vector<string> words;
    vector<string> definitions;
    int userInput;

    cout << "\n------- Main Menu -------\n";
    cout << "\n1. Easy" << endl;
    cout << "2. Advanced" << endl;
    cout << "3. Edit" << endl;
    cout << "4. Quit" << endl;
    cout << "Enter option from the menu by typing a number: ";
    parseUserInput(userInput);

    switch (userInput)
    {
    case 1:
        runQuiz(filenames, 1);
        break;
    case 2:
        runQuiz(filenames, 2);
        break;
    case 3:
        editMode(filenames);
        break;
    case 4:
        showGoodbyeMessage();
        return false;
   
    default: cout << "\nPlease enter a valid number!\n"; break;
    }
    return true;
}

int main()
{
    vector <string> filenames = {
        "easy.txt",
        "advanced.txt"
    };

    showInitialGreeting();
    while (doShowMenu(filenames)); // loop for the menu
}
