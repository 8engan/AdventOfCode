#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <functional>
#include "../constants.h"

using namespace std;


/**
 * Processes a round of paper, rock, scissors and adds score to totalScore
 * @param debugStringHands String used for debug purpouses
 * @param debugStringPoints String used for debug purpouses
 * @param totalScore Total score passed by reference
 * @param oppHand Char representing what hand the opponent plays (A Paper, B Rock, C Scissors)
 * @param myHand Char representing what hand I play (X Paper, Y Rock, Z Scissors)
 */
void processRound(string& debugStringHands, string& debugStringPoints, int& totalScore, char oppHand, char myHand){
    // Figure out what hand wins
    if (oppHand == 'A'){ // Opponent plays Rock
        if (myHand == 'X')
        { // Draw
            debugStringHands += " : Rock vs. Rock: ";
            debugStringPoints += " 1 + 3 = 4 points";
            totalScore += 3;
        }
        else if (myHand == 'Y')
        { // Paper beats rock
            debugStringHands += " : Rock vs. Paper: ";
            debugStringPoints += " 2 + 6 = 8 points";
            totalScore += 6;
        }
        else
        {
            debugStringHands += " : Rock vs. Scissors: ";
            debugStringPoints += " 3 + 0 = 3 points";
        }
    }
    else if (oppHand == 'B')
    { // Opponent plays Paper
        if (myHand == 'Y')
        { // Draw
            debugStringHands += " : Paper vs. Paper: ";
            debugStringPoints += " 2 + 3 = 5 points";
            totalScore += 3;
        }
        else if (myHand == 'Z')
        { // Scissors beats Paper
            debugStringHands += " : Paper vs. Scissors: ";
            debugStringPoints += " 3 + 6 = 9 points";
            totalScore += 6;
        }
        else
        {
            debugStringHands += " : Paper vs. Rock: ";
            debugStringPoints += " 1 + 0 = 1 points";
        }
    }
    else if (oppHand == 'C')
    { // Opponent plays Scissors
        if (myHand == 'Z')
        { // Draw
            debugStringHands += " : Scissors vs. Scissors: ";
            debugStringPoints += " 3 + 3 = 6 points";
            totalScore += 3;
        }
        else if (myHand == 'X')
        { // Rock beats scissors
            debugStringHands += " : Scissors vs. Rock: ";
            debugStringPoints += " 1 + 6 = 7 points";
            totalScore += 6;
        }
        else
        {
            debugStringHands += " : Scissors vs. Paper: ";
            debugStringPoints += " 2 + 0 = 2 points";
        }
    }
}

int processStrategyPart1(string inputFile)
{

    int totalScore{0};
    int charReduce{87};
    int myHandScore{0};

    char oppHand{0};
    char myHand{0};

    ifstream ifs;
    string readLine;
    string debugStringHands;
    string debugStringPoints;

    ifs.open(inputFile);

    // read the file and split into hands
    if (ifs.is_open())
    {
        while (ifs.good())
        {
            getline(ifs, readLine);
            debugStringHands = readLine;
            debugStringPoints = "";

            // split into two hands
            oppHand = readLine[0];
            myHand = readLine[2];
            myHandScore = myHand - charReduce; // Reduce ASCII value with charReduce to get X=1, Y=2, Z=3
            totalScore += myHandScore;
            
            processRound(debugStringHands, debugStringHands, totalScore, oppHand, myHand);
            if(constants::DEBUG){
                cout << "Part1: " << setw(50) << left << debugStringHands << debugStringPoints << " - totalScore = " << totalScore << endl;
            }
        }
    }
    else
    {
        cout << "File not open" << endl;
    }
    ifs.close();
    return totalScore;
}

int processStrategyPart2(string inputFile)
{

    int totalScore{0};
    int charReduce{87};
    int charAdd{23};
    int myHandScore{0};

    char oppHand{0};
    char myHand{0};
    char roundResult{0};

    ifstream ifs;
    string readLine;
    string debugStringHands;
    string debugStringPoints;

    ifs.open(inputFile);

    // read the file and split into hands
    if (ifs.is_open())
    {
        while (ifs.good())
        {
            getline(ifs, readLine);
            debugStringHands = readLine;
            debugStringPoints = "";

            // split into opponent hand and desired end result
            oppHand = readLine[0];
            roundResult = readLine[2];

            // Figure out what hand to play to reach desired end result
            if (roundResult == 'X')
            { // My hand needs to loose
                if (oppHand == 'A')
                { // Need scissors to loose
                    myHand = 'Z';
                }
                else if (oppHand == 'B')
                { // Need rock to loose
                    myHand = 'X';
                }
                else if (oppHand == 'C')
                { // Need Paper to loose
                    myHand = 'Y';
                }
            }
            else if (roundResult == 'Y')
            {                               // Need a draw
                myHand = oppHand + charAdd; // Add charAdd to transform A->X,B->Y,C->Z
            }
            else if (roundResult == 'Z')
            { // My hand needs to win
                if (oppHand == 'A')
                { // Need paper to win
                    myHand = 'Y';
                }
                else if (oppHand == 'B')
                { // Need Paper to win
                    myHand = 'Z';
                }
                else if (oppHand == 'C')
                { // Need Rock to win
                    myHand = 'X';
                }
            }

            myHandScore = myHand - charReduce; // Reduce ASCII value with charReduce to get X=1, Y=2, Z=3
            totalScore += myHandScore;

            processRound(debugStringHands, debugStringHands, totalScore, oppHand, myHand);
            if(constants::DEBUG){
                cout << "Part2:" << setw(50) << left << debugStringHands << debugStringPoints << " - totalScore = " << totalScore << endl;
            }
            
        }
    }
    else
    {
        cout << "File not open" << endl;
    }
    ifs.close();
    return totalScore;
}


