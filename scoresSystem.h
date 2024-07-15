#ifndef SCORESSYSTEM_H
#define SCORESSYSTEM_H
#include "libraries.h"
#include "constants.h"

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

// score store
void scoreStore(std::string filePath, int score, std::string mode)
{
    ifstream fileIn(filePath);
    vector<std::string> lines;
    string line;

    // read
    while (getline(fileIn, line))
    {
        istringstream iss(line);
        string currentMode;
        iss >> currentMode;
        transform(currentMode.begin(), currentMode.end(), currentMode.begin(), ::tolower);
        // find the row and pushback score
        if (currentMode == mode + ":")
        {
            line += " " + to_string(score) + " |";
        }
        lines.push_back(line);
    }
    fileIn.close();
    // write
    ofstream fileOut(filePath);
    for (const auto &updatedLine : lines)
    {
        fileOut << updatedLine << std::endl;
    }
    fileOut.close();
}

#endif // !SCORESSYSTEM_H