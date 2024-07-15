#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "libraries.h"

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

#endif // !CONSTANTS_H