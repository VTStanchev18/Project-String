#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

//question-answer pair
struct QA_PAIR {
    string question, answer;
};

// function for checking whether is correct
bool isCorrect(vector <string> answerPool, QA_PAIR currentQuestion, int answer) {

}
// function for the easy words of our program
void easyOption()
{
    vector <string> words;
    vector <QA_PAIR> questionAnswerPairs;
    vector <string> answerPool;

    auto rng = default_random_engine(time(0));
    int j;
    words = { "signal","apple","dog","cat","computer" };

    questionAnswerPairs = {
        {"signal", "convey information or instructions by means of a gesture, action, or sound."},
        {"apple", "a round fruit; typically has green or red color"},
        {"dog", "an animal that barks; humans' best friend"},
        {"cat", "an animal that catches mice; hates dogs"},
        {"computer", "a device used for storing and processing data"}
    };

    shuffle(questionAnswerPairs.begin(), questionAnswerPairs.end(), rng);
    for (int i = 0; i < 4; i++) {
        shuffle(words.begin(), words.end(), rng);

        answerPool.clear();

        for (int j = 0; j < 4; j++) {
            answerPool.push_back(words[j]);
        }
        shuffle(answerPool.begin(), answerPool.end(), rng);

        cout << endl << questionAnswerPairs[i].answer << endl;
        for (j = 0; j < 4; j++) {
            cout << j + 1 << ". " << answerPool[j] << endl;
        }
        cout << j + 1 << ". " << "None of the above\n";
    }
}

void mediumOption(vector<string> vect, vector<string> definitions) {

}

void advancedOption() {

}

void editMode() {

}
// function for displaying greetings
void showInitialGreeting()
{
    cout << "\n                                     Interoperable Console- Wordie                      \n";
    cout << "  Welcome to our game called Wordie.\n";
    cout << "  Thank you for choosing our software!\n";
    cout << "  Please refer to the Documentation for a more detailed explanation about using the program.\n";
    cout << "  Our Team takes no responsibility for misuse of the program.\n\n";
}
// function for displaying goodbye message
void showGoodbyeMessage()
{
    cout << "\n  Thank you for using our game Wordie!\n\n";
    cout << "  Copyright (c) 2020 team\n";;
}
// function for our menu from which the player can chose difficulty, see his score or exit the program 
bool doShowMenu()
{
    vector<string> words;
    vector<string> definitions;
    int userInput;

    cout << "\n------- Main Menu -------\n";
    cout << "\n1. Easy" << endl;
    cout << "2. Medium" << endl;
    cout << "3. Advanced" << endl;
    cout << "4. Edit" << endl;
    cout << "5. Quit" << endl;
    cout << "Enter option from the menu by typing a number: ";
    cin >> userInput;

    switch (userInput)
    {
    case 1:easyOption();

        break;
    //case 2:mediumOption();
        break;
    case 3:advancedOption();
        break;
    case 4:editMode();
        break;
    case 5: {
        showGoodbyeMessage();
        return 0;
        }
        break;
   
    default: cout << "\nPlease enter a valid number!\n"; break;
    }
    return true;
}

int main()
{
    srand(time(NULL));
    showInitialGreeting();
    while (doShowMenu()); // loop for the menu
}
