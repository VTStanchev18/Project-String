#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <vector>

using namespace std;

int giveRandomNum() {
    int num = rand() % 4;
    return num;
}

int giveRandomNum(vector<string> vect) {
    int num = rand() % vect.size();
    return num;
}

bool isCorrect() {

    return true;
}

void easyOption(vector<string> vect, vector<string> definitions) {
    vect = { "signal","apple","dog","cat","computer" };

    definitions = {
    "convey information or instructions by means of a gesture, action, or sound.",
    "a round fruit; typically has green or red color",
    "an animal that barks; humans' best friend",
    "an animal that catches mice; hates dogs",
    "a device used for storing and processing data"};

    int index;

    for (int i = 0; i < 4; i++) {
        index = giveRandomNum(vect);
        cout << endl << vect[index] << endl;
        cout << "1. " << definitions[giveRandomNum()] << endl;
        cout << "2. " << definitions[giveRandomNum()] << endl;
        cout << "3. " << definitions[giveRandomNum()] << endl;
        cout << "4. " << definitions[giveRandomNum()] << endl;
        cout << "5. Nothing from above" << endl;

    }
}

void mediumOption() {

}

void advancedOption() {

}

void editMode() {

}

void showInitialGreeting()
{
    cout << "\n                                     Interoperable Console                       \n";
    cout << "  Welcome to our game.\n";
    cout << "  Thank you for choosing our software!\n";
    cout << "  Please refer to the Documentation for a more detailed explanation about using the program.\n";
    cout << "  Our Team takes no responsibility for misuse of the program.\n\n";
}

void showGoodbyeMessage()
{
    cout << "\n  Thank you for using our game!\n\n";
    cout << "  Copyright (c) 2020 team\n";;
}

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
    case 1:easyOption(words,definitions);

        break;
    case 2:mediumOption();
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
    while (doShowMenu());
}
