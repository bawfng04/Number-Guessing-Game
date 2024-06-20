#include <bits/stdc++.h>
using namespace std;

// cd "d:\Projects\NumberGuessingGame" && g++ NumberGuessing.cpp -o NumberGuessing && ./NumberGuessing

// forward declaration
void guessing();
int calculateScore(int usedAttempts, string mode);
// define constants for easy mode
#define easyRandomRange 100
#define easyAttemptsLimit INT_MAX
#define easyHint 0

// define constants for medium mode
#define mediumRandomRange 200
#define mediumAttemptsLimit 10
#define mediumHint 2

// define constants for hard mode
#define hardRandomRange 500
#define hardAttemptsLimit 9
#define hardHint 3

// define constatns for extreme mode
#define extremeRandomRange 1000
#define extremeAttemptsLimit 8
#define extremeHint 5

// define constants for score
#define maxScore 10000
#define easyPenalty 250
#define mediumPenalty 500
#define hardPenalty 750
#define extremePenalty 1000

// Random number generator
// 1->range
int createRandomNumber(int range)
{
    std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(1, range);
    return distribution(generator);
}

// helper functions
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
                                  to_string(easyRandomRange) + ", unlimited attempts and " + to_string(easyHint) + " hint\n"
                                                                                                                   "Type 'medium' for medium mode, guess the number between 1 and " +
                                  to_string(mediumRandomRange) + ", " + to_string(mediumAttemptsLimit) + " attempts and " + to_string(mediumHint) + " hint\n"
                                                                                                                                                    "Type 'hard' for hard mode, guess the number between 1 and " +
                                  to_string(hardRandomRange) + ", " + to_string(hardAttemptsLimit) + " attemps and " + to_string(hardHint) + " hints \n"
                                                                                                                                             "Type 'extreme' for extreme mode, guess the number between 1 and " +
                                  to_string(extremeRandomRange) + ", " + to_string(extremeAttemptsLimit) + " attemps and " + to_string(extremeHint) + " hints \n";

    printBox(gameModeInstructions);
    cout << endl
         << endl;
}

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

void handleLargerGuess(int remain)
{
    string messenge = "Guess a lower number! Try again... \n";
    if (remain <= 5 && remain != 1)
    {
        messenge += "You have " + to_string(remain) + " attempts left\n";
    }
    else if (remain == 1)
        messenge += "Last guess\n";
    printBox(messenge);
}

void handleSmallerGuess(int remain)
{
    string messenge = "Guess a higher number! Try again... \n";
    if (remain <= 5 && remain != 1)
    {
        messenge += "You have " + to_string(remain) + " attempts left\n";
    }
    else if (remain == 1)
        messenge += "Last guess\n";
    printBox(messenge);
}

void handleCorrectGuess(int attempts, int randomNumber, string mode)
{
    if (attempts != 1)
        printBox("Congratulations! You guessed the number with " + to_string(attempts) +
                 " attempts. The correct number was " + to_string(randomNumber) +
                 "\n Your score is " + to_string(calculateScore(attempts, mode)));
    else
        printBox("Congratulations! You guessed the number with 1 attempt. The correct number was " + to_string(randomNumber) +
                 "\n Your score is " + to_string(calculateScore(attempts, mode)));
}

bool outOfLimit(int attempts, int limit, int randomNumber)
{
    if (attempts == limit)
    {
        printBox("Failed: You have reached the limit of attempts. The correct number was " + to_string(randomNumber) + "\n Your score is 0");
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
    else
    {
        cout << "Invalid mode. Please try again." << endl;
        guessing();
    }
}

// hints
int lastDigit(int n)
{
    return n % 10;
}

bool isPrime(int n)
{
    if (n < 2)
        return false;
    for (int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

bool isEven(int n)
{
    return n % 2 == 0;
}

int sumOfDigits(int n)
{
    int sum = 0;
    while (n > 0)
    {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

bool isPerfectNumber(int n)
{
    int sum = 0;
    for (int i = 1; i < n; i++)
    {
        if (n % i == 0)
            sum += i;
    }
    return sum == n;
}

bool isDevidedBy(int n, int m)
{
    return n % m == 0;
}

bool isPowerOfTwo(int n)
{
    return n && (!(n & (n - 1)));
}

bool isAmstrongNumber(int n)
{
    int sum = 0;
    int temp = n;
    while (temp > 0)
    {
        int lastDigit = temp % 10;
        sum += pow(lastDigit, 3);
        temp /= 10;
    }
    return sum == n;
}

// get hints
void getHints(vector<pair<string, bool>> &v)
{
    int randomIndex = rand() % v.size();
    while (v[randomIndex].second)
        randomIndex = rand() % v.size();
    v[randomIndex].second = true;
    printBox(v[randomIndex].first);
}

void generateHints(vector<pair<string, bool>> &v, int randomNumber)
{
    // prime
    if (isPrime(randomNumber))
        v.push_back(make_pair("The number is a prime number", false));
    else
        v.push_back(make_pair("The number is not a prime number", false));
    // even, odd
    if (isEven(lastDigit(randomNumber)))
        v.push_back(make_pair("The number is end with an even number", false));
    else
        v.push_back(make_pair("The number is end with an odd number", false));
    // sum
    v.push_back(make_pair("The sum of the digits of the number is " + to_string(sumOfDigits(randomNumber)), false));
    // perfect number
    if (isPerfectNumber(randomNumber))
        v.push_back(make_pair("The number is a perfect number", false));
    else
        v.push_back(make_pair("The number is not a perfect number", false));
    // devided by 3
    if (isDevidedBy(randomNumber, 3))
        v.push_back(make_pair("The number is devided by 3", false));
    else
        v.push_back(make_pair("The number is not devided by 3", false));
    // devided by 7
    if (isDevidedBy(randomNumber, 7))
        v.push_back(make_pair("The number is devided by 7", false));
    else
        v.push_back(make_pair("The number is not devided by 7", false));
    // power of 2
    if (isPowerOfTwo(randomNumber))
        v.push_back(make_pair("The number is a power of 2", false));
    else
        v.push_back(make_pair("The number is not a power of 2", false));
    // amstrong number
    if (isAmstrongNumber(randomNumber))
        v.push_back(make_pair("The number is an amstrong number", false));
    else
        v.push_back(make_pair("The number is not an amstrong number", false));
}

// score
int calculateScore(int usedAttempts, string mode)
{
    int penalty;
    if (mode == "easy")
    {
        penalty = easyPenalty;
    }
    else if (mode == "medium")
    {
        penalty = mediumPenalty;
    }
    else if (mode == "hard")
    {
        penalty = hardPenalty;
    }
    else if (mode == "extreme")
    {
        penalty = extremePenalty;
    }
    return max(0, maxScore - usedAttempts * penalty);
}

// here is where the game starts
void guessing()
{
    srand(time(0));
    int randomNumber, guess, limit, hint, maxNumber, attempts = 1;
    vector<pair<string, bool>> hints;
    string mode;
    printInstructions();
    selectMode(randomNumber, limit, hint, maxNumber, mode);
    generateHints(hints, randomNumber);

    do
    {
        if (outOfLimit(attempts, limit + 1, randomNumber))
            return;

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
        if (guess > randomNumber)
            handleLargerGuess(limit - attempts + 1);
        else if (guess < randomNumber)
            handleSmallerGuess(limit - attempts + 1);
        else
            handleCorrectGuess(attempts - 1, randomNumber, mode);

    } while (guess != randomNumber);

    return;
}

int main()
{
    guessing();
    return 0;
}