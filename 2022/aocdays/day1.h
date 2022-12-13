#ifndef DAY1_H
#define DAY1_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include "../constants.h"

using namespace std;


int getCalorieCount(vector<int> vec, int entriesToSum){

    int returnVal{0};
    sort(vec.begin(), vec.end(), greater<int>());

    for(int i{0}; i < entriesToSum; i++){
        returnVal += vec[i];
    }

    return returnVal;
}

vector<int> getElvesVector(string inputFile){

    int calorieRead{0};
    int calorieSum{0};
    ifstream ifs;
    string readLine;
    vector<int> elvesVector;
    
    ifs.open(inputFile);

    // read the file and create an array of calories carried by each elf
    if(ifs.is_open()){
        while(ifs){
            getline(ifs, readLine);
            
            // If readLine is empty string then new elf at next line, so add current tally to vector
            if(readLine.empty()){
                elvesVector.push_back(calorieSum);
                calorieSum = 0; // Reset calorie count for new elf
            }else{
                calorieRead = stoi(readLine);
                calorieSum += calorieRead;
            }
        }
    }else{
        cout << "File not open" << endl;
    }
    return elvesVector;
}


#endif