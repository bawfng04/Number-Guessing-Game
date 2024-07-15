#ifndef UTILITIES_H
#define UTILITIES_H
#include "libraries.h"
#include "constants.h"

// Random number generator [1, range]
int createRandomNumber(int range)
{
    std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(1, range);
    return distribution(generator);
}
//  Prints
void printBox(string content)
{
    stringstream ss(content);
    string line;
    int maxLength = 0;

    // find the longest line
    while (getline(ss, line, '\n'))
    {
        if (line.length() > maxLength)
        {
            maxLength = line.length();
        }
    }

    int boxWidth = maxLength + 8;
    string horizontalLine(boxWidth, '=');

    cout << horizontalLine << endl;

    ss.clear();
    ss.str(content);

    while (getline(ss, line, '\n'))
    {
        cout << "=   " << left << setw(maxLength) << line << "   =" << endl;
    }

    cout << horizontalLine << endl;
    cout << endl
         << endl;
}

void printInstructions()
{
    string gameModeInstructions = "Please select mode: \n"
                                  "Type 'easy' for easy mode, guess the number between 1 and " +
                                  to_string(easyRandomRange) + ", unlimited attempts and " + to_string(easyHint) + " hint, every second you lost " + to_string(easyTimePenalty) + " points\n"
                                                                                                                                                                                  "Type 'medium' for medium mode, guess the number between 1 and " +
                                  to_string(mediumRandomRange) + ", " + to_string(mediumAttemptsLimit) + " attempts and " + to_string(mediumHint) + " hint, every second you lost " + to_string(mediumTimePenalty) + " points\n"
                                                                                                                                                                                                                     "Type 'hard' for hard mode, guess the number between 1 and " +
                                  to_string(hardRandomRange) + ", " + to_string(hardAttemptsLimit) + " attemps and " + to_string(hardHint) + " hints, every second you lost " + to_string(hardTimePenalty) + " points\n"
                                                                                                                                                                                                             "Type 'extreme' for extreme mode, guess the number between 1 and " +
                                  to_string(extremeRandomRange) + ", " + to_string(extremeAttemptsLimit) + " attemps and " + to_string(extremeHint) + " hints, every second you lost " + to_string(extremeTimePenalty) + " points\n"
                                                                                                                                                                                                                         "Type 'custom' for custom mode, you can decide the range of the random number, the attemps and hints you have and the penalty each guess and each second in this mode\n";

    printBox(gameModeInstructions);
    cout << endl
         << endl;
}

#endif // !UTILITIES_H