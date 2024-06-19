#include <bits/stdc++.h>
using namespace std;

// cd "d:\Projects\NumberGuessingGame" && g++ NumberGuessing.cpp -o NumberGuessing && ./NumberGuessing

void printBox(string content)
{
    int length = content.length() + 8;
    string horizontalLine(length, '=');

    cout << horizontalLine << endl;
    cout << "=" << setw(length - 1) << "=" << endl;
    cout << "=   " << content << "   =" << endl;
    cout << "=" << setw(length - 1) << "=" << endl;
    cout << horizontalLine << endl;
}

void guessing()
{
    srand(time(0));
    int randomNumber = rand() % 100 + 1;
    int guess;
    int attempts = 0;
    do
    {
        attempts++;
        cout << endl
             << "Attempt " << attempts << ", "
                                          "guess the number between 1 and 100: ";
        while (!(cin >> guess))
        {
            cout << endl;
            printBox("Invalid input. Please enter an integer.");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            attempts++;
            cout << endl
                 << "Attempt " << attempts << ", "
                                              "guess the number between 1 and 100: ";
        }
        if (guess > randomNumber)
        {
            // cout << "Guess a lower number! Try again..." << endl;
            printBox("Guess a lower number! Try again...");
        }
        else if (guess < randomNumber)
        {
            // cout << "Guess a higher number! Try again..." << endl;
            printBox("Guess a higher number! Try again...");
        }
        else
        {
            /*
            cout << "Congratulations! You guessed the number with ";
            if (attempts == 1)
                cout << "1 attempt." << endl;
            else
                cout << attempts << " attempts." << endl;
            cout << "The correct number was: " << randomNumber << endl;*/
            if (attempts != 1)
                printBox("Congratulations! You guessed the number with " + to_string(attempts) + " attempts. The correct number was " + to_string(randomNumber));
            else
                printBox("Congratulations! You guessed the number with 1 attempt. The correct number was " + to_string(randomNumber));
        }
    } while (guess != randomNumber);

    return;
}

int main()
{
    guessing();
    return 0;
}