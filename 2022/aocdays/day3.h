#ifndef DAY3_H
#define DAY3_H

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "../constants.h"

using namespace std;

int checkRucksack(string& rucksack1, string& rucksack2){

    char error{0};
    int priority{0};
    int lowerCaseOffSet{96};
    int upperCaseOffSet{38};

    for(size_t i{0}; i < rucksack1.length(); i++){
        for(size_t j{0}; j < rucksack2.length(); j++){
            if(rucksack1[i] == rucksack2[j]){   // Found an error
                error = rucksack1[i];
                break;
            }
        }
    }

    if(error == 0){
        priority = 0;
    }else if(error >= 97){
        priority = error - lowerCaseOffSet;
    }else{
        priority = error - upperCaseOffSet;
    }

    if(constants::DEBUG){
        if(error > 0){
            cout << setw(40) << left << "Found error in rucksack = " << error << "  with priority = " << priority << endl;
        }else{
            cout << setw(40) << left << "No error found in rucksack" << priority << endl;
        }
        
    }
    return priority;
}

void processAllRucksacks(string inputFile, int& totalPrio){
    
    
    ifstream ifs;
    string readRucksack;
    string rucksack1;
    string rucksack2;


    ifs.open(inputFile);
    while (ifs.good()){

        getline(ifs, readRucksack);
        rucksack1 = readRucksack.substr(0,(readRucksack.length()/2));
        rucksack2 = readRucksack.substr((readRucksack.length()/2),readRucksack.length());

        if(constants::DEBUG){
            cout << setw(40) << left << "readRucksack = " << readRucksack << endl;
            cout << setw(40) << left << "rucksack1 = " << rucksack1 << endl;
            cout << setw(40) << left << "rucksack2 = " << rucksack2 << endl;
            cout << endl;
        }

        totalPrio += checkRucksack(rucksack1, rucksack2);
        
    }
    ifs.close();

}

void processGroupOfThreeRucksacks(string inputFile, int& totalPrio){
    
    
    ifstream ifs;
    string rucksack1;
    string rucksack2;
    string rucksack3;
    char badgeItem{0};
    bool badgeFound = false;
    int lowerCaseOffSet{96};
    int upperCaseOffSet{38};
    int priority{0};
    int groupNum{0};

    ifs.open(inputFile);
    while (ifs.good()){
        badgeFound = false;
        badgeItem = 0;
        ++groupNum;

        if(constants::DEBUG){
            cout << "Processing group " << groupNum << endl;
        }
        getline(ifs, rucksack1);
        getline(ifs, rucksack2);
        getline(ifs, rucksack3);

        for(size_t i{0}; i < rucksack1.length(); i++){
            for(size_t j{0}; j < rucksack2.length(); j++){
                if(rucksack1[i] == rucksack2[j]){   // Rucksack 1 and 2 has a common item, check rucksack3
                    badgeItem = rucksack1[i];
                    for(size_t k{0}; k < rucksack3.length(); k++){

                        if(rucksack3[k] == badgeItem){
                            badgeFound = true;
                            break;
                        }
                    }
                }
                
                if(badgeFound){
                    break;
                }
            }
            if(badgeFound){
                break;
            }
        }
        // rudimentary check for error in file, i.e. group of three does not share item
        if(!badgeFound){
            cout << "No common badgeitem found, check input file. Exiting program." << endl;
            exit(1);
        }

        if(badgeItem == 0){
            priority = 0;
        }else if(badgeItem >= 97){
            priority = badgeItem - lowerCaseOffSet;
        }else{
            priority = badgeItem- upperCaseOffSet;
        }
        
        
        totalPrio += priority;
        if(constants::DEBUG){
            cout << "Found common item " << badgeItem << " with priority " << priority << ". Total prio now = " << totalPrio << endl;
            cout << endl;
        }
        
    }
    ifs.close();

}

#endif
