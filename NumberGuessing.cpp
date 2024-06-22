#include <bits/stdc++.h>
using namespace std;

// cd "d:\Projects\NumberGuessingGame" && g++ NumberGuessing.cpp -o NumberGuessing && ./NumberGuessing

// forward declaration
int customGuessPenalty, customTimePenalty;
void guessing();
int calculateScore(int usedAttempts, int timeTaken, string mode);
// define constants for easy mode
#define easyRandomRange 100
#define easyAttemptsLimit INT_MAX
#define easyHint 0
#define easyGuessPenalty 250
#define easyTimePenalty 0

// define constants for medium mode
#define mediumRandomRange 200
#define mediumAttemptsLimit 10
#define mediumHint 2
#define mediumGuessPenalty 500
#define mediumTimePenalty 5

// define constants for hard mode
#define hardRandomRange 500
#define hardAttemptsLimit 9
#define hardHint 3
#define hardGuessPenalty 750
#define hardTimePenalty 10

// define constatns for extreme mode
#define extremeRandomRange 1000
#define extremeAttemptsLimit 8
#define extremeHint 5
#define extremeGuessPenalty 1000
#define extremeTimePenalty 15

// define constants for score
#define maxScore 10000

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

void handleCorrectGuess(int attempts, int randomNumber, string mode, int timeTaken)
{
    if (attempts != 1)
        printBox("Congratulations! You guessed the number with " + to_string(attempts) +
                 " attempts and " + to_string(timeTaken) + " second. The correct number was " + to_string(randomNumber) +
                 "\n Your score is " + to_string(calculateScore(attempts, timeTaken, mode)));
    else
        printBox("Congratulations! You guessed the number with 1 attempt and " + to_string(timeTaken) + " second. The correct number was " + to_string(randomNumber) +
                 "\n Your score is " + to_string(calculateScore(attempts, timeTaken, mode)));
}

bool outOfLimit(int attempts, int limit, int randomNumber, int timeTaken)
{
    if (attempts == limit)
    {
        printBox("Failed: You have reached the limit of attempts in " + to_string(timeTaken) + " second. The correct number was " + to_string(randomNumber) + "\n Your score is 0");
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

int maxNumber(int number)
{
    int maxNum = 0;
    while (number > 0)
    {
        int lastDigit = number % 10;
        maxNum = max(maxNum, lastDigit);
        number /= 10;
    }
    return maxNum;
}

int minNumber(int number)
{
    int minNum = INT_MAX;
    while (number > 0)
    {
        int lastDigit = number % 10;
        minNum = min(minNum, lastDigit);
        number /= 10;
    }
    return minNum;
}

// get hints
bool allHintsUsed(const vector<pair<string, bool>> &v)
{
    for (auto hint : v)
    {
        if (!hint.second)
            return false;
    }
    return true;
}

void getHints(vector<pair<string, bool>> &v)
{
    if (allHintsUsed(v))
    {
        printBox("The system has no more hints for you.");
        return;
    }
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
    // maxNumber
    v.push_back(make_pair("The max digit of the number is " + to_string(maxNumber(randomNumber)), false));
    // minNumber
    v.push_back(make_pair("The min digit of the number is " + to_string(minNumber(randomNumber)), false));
}

// score
int calculateScore(int usedAttempts, int timeTaken, string mode)
{
    int guessPenalty, timePenalty;
    if (mode == "easy")
    {
        guessPenalty = easyGuessPenalty;
        timePenalty = easyTimePenalty;
    }
    else if (mode == "medium")
    {
        guessPenalty = mediumGuessPenalty;
        timePenalty = mediumTimePenalty;
    }
    else if (mode == "hard")
    {
        guessPenalty = hardGuessPenalty;
        timePenalty = hardTimePenalty;
    }
    else if (mode == "extreme")
    {
        guessPenalty = extremeGuessPenalty;
        timePenalty = extremeTimePenalty;
    }
    else if (mode == "custom")
    {
        guessPenalty = customGuessPenalty;
        timePenalty = customTimePenalty;
    }
    else
    {
        guessPenalty = 0;
        timePenalty = 0;
    }
    return max(0, maxScore - (usedAttempts - 1) * guessPenalty - timePenalty * timeTaken);
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

    do
    {
        // update timer
        auto current = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = current - start;
        timeTaken = static_cast<int>(elapsed.count());
        if (outOfLimit(attempts, limit + 1, randomNumber, timeTaken))
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

        timeTaken = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - start).count();
        if (guess > randomNumber)
            handleLargerGuess(limit - attempts + 1);
        else if (guess < randomNumber)
            handleSmallerGuess(limit - attempts + 1);
        else
            handleCorrectGuess(attempts - 1, randomNumber, mode, timeTaken);
    } while (guess != randomNumber);
    return;
}

int main()
{
    guessing();
    return 0;
}
