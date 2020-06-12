#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>
#include <cctype>

#include "structs.h"
#include "io functions.h"

using namespace std;

// function for checking whether user's answer is correct
bool isCorrect(vector <string> answerPool, QA_PAIR currentQuestion, int answer) {
    if (answer == answerPool.size() + 1) {
        if (find(answerPool.begin(), answerPool.end(), currentQuestion.word) == answerPool.end()) {
            return true;
        }
        return false;
    }
    if (answerPool[answer - 1] == currentQuestion.word) {
        return true;
    }
    return false;
}
//positive messages for the user
void positiveQuotes() {
    vector<string> quotes = {
        "You are doing great!!!",
        "Woahh, Amaziing!!!",
        "Greaat!!!",
        "Perfect!!!"
    };
    auto rng = default_random_engine(time(0));
    uniform_int_distribution<> distrib(0, quotes.size()-1);
    cout << quotes[distrib(rng)] << endl;
}
//negative messages for the user
void negativeQuotes() {
    vector<string> quotes = {
        "You can do it, you're just not doing it now!",
        "Just do it. It's not that hard",
        "Try again... Please... I know you aren't thaat stupid!!!",
        "Come oon, you are not that stupid"
    };
    auto rng = default_random_engine(time(0));
    uniform_int_distribution<> distrib(0, quotes.size() - 1);
    cout << quotes[distrib(rng)] << endl;
}

//displaying words and defenitions for the game
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
        cout << " ";
        if (userAnswer<1 or userAnswer>j + 1) {
            i--;
            cout << "\nPlease enter a valid number!!!\n";
            continue;
        }
        if (isCorrect(answerPool, questionAnswerPairs[i],userAnswer)) {
            positiveQuotes();
            correctAnswers++;
        }
        else
        {
            negativeQuotes();
        }
    }
    cout << "\n You guessed " << correctAnswers << " out of " << 4 << endl;
}
//menu for adding a word and definition by selecting a level of difficulty
void showAddMenu(vector <string> filenames)
{
    int difficulty;
    QA_PAIR temp;

    cout << "\n--- Add a word ---\n\n";
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
//menu for erasing a word or definition
void showDeleteMenu(vector <string> filenames)
{
    int difficulty;
    string word;

    cout << "\n--- Delete a word ---\n\n";
    cout << "1. Delete from easy words\n";
    cout << "2. Delete from advanced words\n";
    cout << "Enter option from the menu by typing a number: ";
    parseUserInput(difficulty);

    if (difficulty < 1 or difficulty > 2) return;

    cout << "Enter word to delete: ";
    getline(cin, word);

    deleteWord(filenames, difficulty, word);
}
//displays words from a chosen level of difficulty 
void showBrowseMenu(vector <string> filenames)
{
    ifstream oldFile;
    ofstream updatedFile;
    vector <string> lines;
    string temp;
    char choice;
    int difficulty;

    cout << "\n--- Browse Words ---\n\n";
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

bool compareFunction(string word1, string word2){
    return word1 < word2;
}

void seeAllWords(vector <string> filenames) {
    vector <string> words;
    vector <QA_PAIR> questionAnswerPairs;
    int difficulty;
    cout << "\n--- See Words ---\n\n";
    cout << "1. See easy words\n";
    cout << "2. See advanced words\n";
    cout << "Enter option from the menu by typing a number: ";
    parseUserInput(difficulty);

    if (difficulty < 1 or difficulty > 2) return;
    readWordsFromFile(filenames, difficulty, words, questionAnswerPairs);
    sort(words.begin(), words.end(), compareFunction);
    cout << endl;
    for (int i = 0; i < words.size(); i++) {
        cout << words[i] << endl;
    }
}
//menu for editing
bool showEditMenu(vector <string> filenames)
{
    int userInput;

    cout << "\n---- Editing Menu ----\n\n";
    cout << "1. Add a word\n";
    cout << "2. Delete a specific word\n";
    cout << "3. Browse words\n";
    cout << "4. See all words\n";
    cout << "5. Return to Main Menu\n";
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
            seeAllWords(filenames);
            break;
        case 5:
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
//displaying greetings
void showInitialGreeting()
{
    cout << "\n                                         Bits Please\n";
    cout << "  Welcome to our game called Guess The Word.\n";
    cout << "  Thank you for choosing our software!\n";
    cout << "  Please refer to the Documentation for a more detailed explanation about using the program.\n";
    cout << "  Our Team takes no responsibility for misuse of the program.\n\n";
}
//displaying a goodbye message
void showGoodbyeMessage()
{
    cout << "\n  Thank you for using our game Guess The Word!\n\n";
    cout << "  Copyright (c) 2020 team\n";;
} 
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
