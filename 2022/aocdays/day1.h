#ifndef DAY1_H
#define DAY1_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include "../constants.h"



int getCalorieCount(std::vector<int> vec, int entriesToSum){

    int returnVal{0};
    std::sort(vec.begin(), vec.end(), std::greater<int>());

    for(int i{0}; i < entriesToSum; i++){
        returnVal += vec[i];
    }

    return returnVal;
}

std::vector<int> getElvesVector(std::string inputFile){

    int calorieRead{0};
    int calorieSum{0};
    std::ifstream ifs;
    std::string readLine;
    std::vector<int> elvesVector;
    
    ifs.open(inputFile);

    // read the file and create an array of calories carried by each elf
    if(ifs.is_open()){
        while(ifs){
            std::getline(ifs, readLine);
            
            // If readLine is empty string then new elf at next line, so add current tally to vector
            if(readLine.empty()){
                elvesVector.push_back(calorieSum);
                calorieSum = 0; // Reset calorie count for new elf
            }else{
                calorieRead = std::stoi(readLine);
                calorieSum += calorieRead;
            }
        }
    }else{
        std::cout << "File not open" << std::endl;
    }
    return elvesVector;
}


#endif