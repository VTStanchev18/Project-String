// ConsoleApplication29.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;
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
    int userInput;

    cout << "\n------- Main Menu -------\n";
    cout << "\n1. Easy" << endl;
    cout << "2. Medium" << endl;
    cout << "3. Hard" << endl;
    cout << "4. Add word or a definition for a word" << endl;
    cout << "5. Quit" << endl;
    cout << "Enter option from the menu by typing a number: ";
    cin >> userInput;

    switch (userInput)
    {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        return 0; showGoodbyeMessage();
        break;
   
    default: cout << "\nPlease enter a valid option!\n"; break;
    }
    return true;
}
int main()
{
    showInitialGreeting();
    while (doShowMenu());
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
