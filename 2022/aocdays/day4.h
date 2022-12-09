#ifndef DAY4_H
#define DAY4_H

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "../constants.h"

bool checkIfContained(int left1, int left2, int right1, int right2){
    if((right1 >= left1 && right2 <= left2) || (left1 >= right1 && left2 <=right2)){
        return true;
    }
    return false;
}

int processAssignmentList(std::string inputFile){
    
    
    std::ifstream ifs;
    std::string readLine = "";
    std::string leftAssign = "";
    std::string rightAssign = "";
    int commaPos{0};
    int dashPos{0};
    int totalPairsMatch{0};
    int leftNum1{0};
    int leftNum2{0};
    int rightNum1{0};
    int rightNum2{0};
    bool contained = false;

    ifs.open(inputFile);
    while (ifs.good()){
        contained = false;
        commaPos = 0;
        dashPos = 0;

        // Lines come in format a-b,x-y where comma splits two assignments
        std::getline(ifs, readLine);

        // split readLine into left and right of comma
        commaPos = readLine.find(",");
        leftAssign = readLine.substr(0, commaPos);
        rightAssign = readLine.substr(commaPos + 1, readLine.length());

        dashPos = leftAssign.find("-");
        leftNum1 = std::stoi(leftAssign.substr(0, dashPos));
        leftNum2 = std::stoi(leftAssign.substr(dashPos + 1, leftAssign.length()));
        dashPos = rightAssign.find("-");
        rightNum1 = std::stoi(rightAssign.substr(0, dashPos));
        rightNum2 = std::stoi(rightAssign.substr(dashPos + 1, rightAssign.length()));

        contained = checkIfContained(leftNum1, leftNum2, rightNum1, rightNum2);
        if(contained){
            ++totalPairsMatch;
        }
        
        
    }
    ifs.close();
    return totalPairsMatch;
}


#endif
