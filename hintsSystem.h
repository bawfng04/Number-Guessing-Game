#ifndef HINTSSYSTEM_H
#define HINTSSYSTEM_H
#include "libraries.h"
#include "utilities.h"

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

#endif // !HINTSSYSTEM_H