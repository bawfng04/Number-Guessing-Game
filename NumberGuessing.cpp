#include "components/libraries.h"
#include "components/constants.h"
#include "components/utilities.h"
#include "components/hintsSystem.h"
#include "components/scoresSystem.h"
// cd "d:\Projects\NumberGuessingGame" && g++ NumberGuessing.cpp -o NumberGuessing && ./NumberGuessing

// helper functions
void checkInvalidInput(int &guess, int &attempts, int maxNumber, int hint)
{
    while (!(cin >> guess))
    {
        cout << endl;
        printBox("Invalid input. Please enter an integer.");
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        attempts++;
        cout << endl
             << "Attempt " << attempts << ", "
                                          "guess the number between 1 and "
             << maxNumber << endl;
        if (hint > 0)
            cout << "Or type 'hint' for a hint" << endl;
    }
}

void handleLargerGuess(int remain, int guess)
{
    string messenge = "Guess a LOWER number than " + to_string(guess) + "! Try again... \n";
    if (remain <= 5 && remain != 1)
    {
        messenge += "You have " + to_string(remain) + " attempts left\n";
    }
    else if (remain == 1)
        messenge += "Last guess\n";
    printBox(messenge);
}

void handleSmallerGuess(int remain, int guess)
{
    string messenge = "Guess a HIGHER number than " + to_string(guess) + "! Try again... \n";
    if (remain <= 5 && remain != 1)
    {
        messenge += "You have " + to_string(remain) + " attempts left\n";
    }
    else if (remain == 1)
        messenge += "Last guess\n";
    printBox(messenge);
}

void handleCorrectGuess(int attempts, int randomNumber, string mode, int timeTaken)
{
    if (attempts != 1)
        printBox("Congratulations! You guessed the number with " + to_string(attempts) +
                 " attempts and " + to_string(timeTaken) + " seconds. The correct number was " + to_string(randomNumber) +
                 "\nYour score is " + to_string(calculateScore(attempts, timeTaken, mode)));
    else
        printBox("Congratulations! You guessed the number with 1 attempt and " + to_string(timeTaken) + " seconds. The correct number was " + to_string(randomNumber) +
                 "\nYour score is " + to_string(calculateScore(attempts, timeTaken, mode)));
}

bool outOfLimit(int attempts, int limit, int randomNumber, int timeTaken)
{
    if (attempts == limit)
    {
        printBox("Failed: You have reached the limit of attempts in " + to_string(timeTaken) + " seconds. The correct number was " + to_string(randomNumber) + "\nYour score is 0");
        return true;
    }
    return false;
}

void startNewLoop(int &attempts, int maxNumber, int hint)
{
    cout << endl
         << "Attempt " << attempts << ", "
                                      "guess the number between 1 and "
         << maxNumber << endl;
    if (hint > 0)
        cout << "Or type 'hint' for a hint" << endl;
}

void selectMode(int &randomNumber, int &limit, int &hint, int &maxNumber, string &mode)
{
    cout << "Select mode: ";
    cin >> mode;
    if (mode == "easy")
    {
        randomNumber = createRandomNumber(easyRandomRange);
        limit = easyAttemptsLimit;
        hint = easyHint;
        maxNumber = easyRandomRange;
    }
    else if (mode == "medium")
    {
        randomNumber = createRandomNumber(mediumRandomRange);
        limit = mediumAttemptsLimit;
        hint = mediumHint;
        maxNumber = mediumRandomRange;
    }
    else if (mode == "hard")
    {
        randomNumber = createRandomNumber(hardRandomRange);
        limit = hardAttemptsLimit;
        hint = hardHint;
        maxNumber = hardRandomRange;
    }
    else if (mode == "extreme")
    {
        randomNumber = createRandomNumber(extremeRandomRange);
        limit = extremeAttemptsLimit;
        hint = extremeHint;
        maxNumber = extremeRandomRange;
    }
    else if (mode == "custom")
    {
        int range;
        cout << "Enter the range of the random number: ";
        cin >> range;
        randomNumber = createRandomNumber(range);
        cout << "Enter the limit of attempts: ";
        cin >> limit;
        cout << "Enter the number of hints: ";
        cin >> hint;
        maxNumber = range;
        cout << "Enter the penalty for each wrong guess: ";
        cin >> customGuessPenalty;
        while (cin.fail() || customGuessPenalty < 0)
        {
            cout << "Invalid input. Please enter a positive integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> customGuessPenalty;
        }
        cout << "Enter the penalty for each second: ";
        cin >> customTimePenalty;
        while (cin.fail() || customTimePenalty < 0)
        {
            cout << "Invalid input. Please enter a positive integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> customTimePenalty;
        }
    }
    else
    {
        cout << "Invalid mode. Please try again." << endl;
        guessing();
    }
}


// here is where the game starts
void guessing()
{
    srand(time(0));
    int randomNumber, guess, limit, hint, maxNumber, attempts = 1, timeTaken = 0;
    vector<pair<string, bool>> hints;
    string mode;
    printInstructions();
    selectMode(randomNumber, limit, hint, maxNumber, mode);
    // start timer
    auto start = chrono::high_resolution_clock::now();
    generateHints(hints, randomNumber);
    //test
    //cout << randomNumber << endl;

    do
    {
        // update timer
        auto current = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = current - start;
        timeTaken = static_cast<int>(elapsed.count());
        if (outOfLimit(attempts, limit + 1, randomNumber, timeTaken)){
            combineStore("score/scores.txt", "score/scores.json", 0, mode);
            return;
        }

        startNewLoop(attempts, maxNumber, hint);

        // checkInvalidInput(guess, attempts);
        string input;
        cout << "   >>  ";
        cin >> input;
        if (input == "hint")
        {
            if (hint == 0)
            {
                printBox("You have no hint left");
            }
            else
            {
                getHints(hints);
                hint--;
            }
            continue;
        }
        else
        {
            stringstream ss(input);
            ss >> guess;
            // check if the input is an integer
            if (ss.fail() || !ss.eof())
            {
                printBox("Invalid input. Please enter an integer.");
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                attempts++;
                cout << endl
                     << "Attempt " << attempts << ", "
                                                  "guess the number between 1 and "
                     << maxNumber << endl;
                if (hint > 0)
                    cout << "Or type 'hint' for a hint" << endl;
                continue;
            }
            else
            {
                attempts++;
            }
        }

        timeTaken = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - start).count();
        if (guess > randomNumber)
            handleLargerGuess(limit - attempts + 1, guess);
        else if (guess < randomNumber)
            handleSmallerGuess(limit - attempts + 1, guess);
        else
            handleCorrectGuess(attempts - 1, randomNumber, mode, timeTaken);
    } while (guess != randomNumber);
    //write score to file
    combineStore("score/scores.txt", "score/scores.json", calculateScore(attempts - 1, timeTaken, mode), mode);
    return;
}

int main()
{
    guessing();
    system("pause");
    return 0;
}
