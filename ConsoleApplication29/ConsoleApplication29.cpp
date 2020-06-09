#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <vector>

using namespace std;

int giveRandomNum() {
    int num = rand() % 5;
    return num;
}

void easyOption(vector<string>& vect) {
    vect = { "signal","apple","dog","cat","computer" };
    cout << vect[giveRandomNum()];

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
    vector<string> vect;
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
    case 1:easyOption(vect);

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
   
    default: cout << "\nPlease enter a valid option!\n"; break;
    }
    return true;
}

int main()
{
    srand(time(NULL));
    showInitialGreeting();
    while (doShowMenu());
}
