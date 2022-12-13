#ifndef DAY4_H
#define DAY4_H

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "../constants.h"

using namespace std;

void checkIfContained(int left1, int left2, int right1, int right2, int& totalContained, int& totalOverlap){
    
    bool overlapAccountedFor = false;
    if((right1 >= left1 && right2 <= left2) || (left1 >= right1 && left2 <= right2)){
        ++totalContained;
        ++totalOverlap;
        overlapAccountedFor = true;
    }
    if(!overlapAccountedFor){   // check for overlap if not already accounted for
        if((left1 >= right1 && left1 <= right2) || (left2 >= right1 && left2 <= right2)){
            ++totalOverlap;
        }
    }
}

void processAssignmentList(string inputFile, int& totalContained, int& totalOverlap){
    
    
    ifstream ifs;
    string readLine = "";
    string leftAssign = "";
    string rightAssign = "";
    int commaPos{0};
    int dashPos{0};
    //int totalPairsMatch{0};
    int leftNum1{0};
    int leftNum2{0};
    int rightNum1{0};
    int rightNum2{0};
    bool contained = false;
    bool overlap = false;

    ifs.open(inputFile);
    while (ifs.good()){
        contained = false;
        overlap = false;
        commaPos = 0;
        dashPos = 0;

        // Lines come in format a-b,x-y where comma splits two assignments
        getline(ifs, readLine);

        // split readLine into left and right of comma
        commaPos = readLine.find(",");
        leftAssign = readLine.substr(0, commaPos);
        rightAssign = readLine.substr(commaPos + 1, readLine.length());

        dashPos = leftAssign.find("-");
        leftNum1 = stoi(leftAssign.substr(0, dashPos));
        leftNum2 = stoi(leftAssign.substr(dashPos + 1, leftAssign.length()));
        dashPos = rightAssign.find("-");
        rightNum1 = stoi(rightAssign.substr(0, dashPos));
        rightNum2 = stoi(rightAssign.substr(dashPos + 1, rightAssign.length()));


        checkIfContained(leftNum1, leftNum2, rightNum1, rightNum2, totalContained, totalOverlap);
        //contained = checkIfContained(leftNum1, leftNum2, rightNum1, rightNum2);
        //overlap
        //if(contained){
        //    ++totalContained;
        //}

        
        
    }
    ifs.close();
}


#endif
