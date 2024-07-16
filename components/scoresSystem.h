#ifndef SCORESSYSTEM_H
#define SCORESSYSTEM_H
#include "libraries.h"
#include "constants.h"
#include "json.hpp"

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
void scoreStore(string filePath, int score, std::string mode)
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

void scoreStoreJson(string filePath, int score, string mode)
{
    //Read the existing JSON file
    ifstream fileIn(filePath);
    nlohmann::json scoresJson;
    if (fileIn)
    {
        fileIn >> scoresJson;
    }
    fileIn.close();

    std::transform(mode.begin(), mode.end(), mode.begin(), ::tolower);

    // Update JSON 
    scoresJson[mode].push_back(score);

    //Write back
    ofstream fileOut(filePath);
    fileOut << setw(4) << scoresJson << std::endl;
    fileOut.close();
}

void combineStore(string pathTxt, string pathJson, int score, string mode){
    scoreStore(pathTxt, score, mode);
    scoreStoreJson(pathJson, score, mode);
}

#endif // !SCORESSYSTEM_H