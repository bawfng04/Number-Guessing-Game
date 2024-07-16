#ifndef HINTSSYSTEM_H
#define HINTSSYSTEM_H
#include "libraries.h"
#include "utilities.h"

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

//=========================================================================START HINTS
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

bool isPalindrome(int n)
{
    int reversed = 0;
    int temp = n;
    while (temp > 0)
    {
        int lastDigit = temp % 10;
        reversed = reversed * 10 + lastDigit;
        temp /= 10;
    }
    return reversed == n;
}

bool isFibonacci(int n)
{
    int a = 0;
    int b = 1;
    if (n == a || n == b)
        return true;
    int c = a + b;
    while (c <= n)
    {
        if (c == n)
            return true;
        a = b;
        b = c;
        c = a + b;
    }
    return false;
}

bool isPerfectSquare(int n)
{
    int root = sqrt(n);
    return root * root == n;
}

bool isPerfectCube(int n)
{
    int root = cbrt(n);
    return root * root * root == n;
}

bool isHarshadNumber(int n)
{
    int sum = 0, temp = n;
    while (temp > 0)
    {
        sum += temp % 10;
        temp /= 10;
    }
    return n % sum == 0;
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

int nearestPrimeNumber(int number){
    int smaller = number - 1;
    int larger = number + 1;
    while (true)
    {
        if (isPrime(smaller))
            return smaller;
        if (isPrime(larger))
            return larger;
        smaller--;
        larger++;
    }
    return -1;
}

int nearestFibonacciNumber(int number){
    int smaller = number - 1;
    int larger = number + 1;
    while (true)
    {
        if (isFibonacci(smaller))
            return smaller;
        if (isFibonacci(larger))
            return larger;
        smaller--;
        larger++;
    }
    return -1;
}

int numberOfNumbers(int n)
{
    int count = 0;
    while (n > 0)
    {
        count++;
        n /= 10;
    }
    return count;
}

string toHex(int n){
    stringstream ss;
    ss << hex << n;
    return ss.str();
}

//=========================================================================END HINTS

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
    // palindrome
    if (isPalindrome(randomNumber))
        v.push_back(make_pair("The number is a palindrome number", false));
    else
        v.push_back(make_pair("The number is not a palindrome number", false));
    // fibonacci
    if (isFibonacci(randomNumber))
        v.push_back(make_pair("The number is a fibonacci number", false));
    else
        v.push_back(make_pair("The number is not a fibonacci number", false));
    // perfect square
    if (isPerfectSquare(randomNumber))
        v.push_back(make_pair("The number is a perfect square", false));
    else
        v.push_back(make_pair("The number is not a perfect square", false));
    // perfect cube
    if (isPerfectCube(randomNumber))
        v.push_back(make_pair("The number is a perfect cube", false));
    else
        v.push_back(make_pair("The number is not a perfect cube", false));
    // harshad number
    if (isHarshadNumber(randomNumber))
        v.push_back(make_pair("The number is a harshad number", false));
    else
        v.push_back(make_pair("The number is not a harshad number", false));
    // nearest prime number
    v.push_back(make_pair("The nearest prime number is " + to_string(nearestPrimeNumber(randomNumber)), false));
    // nearest fibonacci number
    v.push_back(make_pair("The nearest fibonacci number is " + to_string(nearestFibonacciNumber(randomNumber)), false));
    // number of digits
    v.push_back(make_pair("The number has " + to_string(numberOfNumbers(randomNumber)) + " digits", false));
    // to hex
    v.push_back(make_pair("The number in hex is " + toHex(randomNumber), false));
}

#endif // !HINTSSYSTEM_H