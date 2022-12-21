#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstring>
#include <regex>
#include <fstream>
#include <algorithm>
#include "../constants.h"
#include "../misc.h"

using namespace std; 

string processStackchart(string inputFile, int craneModel=9000){
    
    ifstream ifs;
    string rowString = "";
    string topCrates = "";
    string moveMultiCrates = "";
    vector<string> stackRowVec; 
    vector<string> stackVec;
    vector<string> moveVec;
    bool crateRow = true;
    int numStacks{0};
    int processedRows{0};
    int numMoves{0};
    int fromStack{0};
    int toStack{0};
    char crate{0};
    char removeChars[]{"[] "};
    string fourSpaces = "    ";
    string fiveSpaces = "     ";
    size_t pos{0};

    
    ifs.open(inputFile);
    while (ifs.good()){
       
        getline(ifs, rowString);

        if(rowString[1] == '1'){  // Ugly way of checking if we are on input row telling how many stacks we have
            // check to see how many stack rows
            // remove all spaces from string
            rowString.erase(remove(rowString.begin(), rowString.end(), ' '), rowString.end());
            numStacks = int(rowString[rowString.length()-1]-'0');
            crateRow = false;

            // Create a vector of strings to represent the stacks
            //char stackCrates= new char [numStacks][processedRows];
            stackVec.resize(numStacks,"");
            for(int i{numStacks - 1}; i >= 0; i--){   // work through each stack
                
                for(int j{int(stackRowVec.size())-1}; j >= 0; j--){
                
                    if(stackRowVec[j][i] == '.'){    // nothing to add
                        continue;
                    }
                    stackVec[i].push_back(stackRowVec[j][i]);
                }
            }


            continue;   // move on to the "crate moves"
        }

        if(crateRow){
            ++processedRows;
            // Replace "    " (4 spaces) and "     " (5 spaces) with '.', which tells us it is an empty entry on the stack.
            rowString = regex_replace(rowString, regex(fourSpaces), ".");
            rowString = regex_replace(rowString, regex(fiveSpaces), ".");

            for(size_t i{0}; i < strlen(removeChars); i++){
                rowString.erase(remove(rowString.begin(), rowString.end(), removeChars[i]), rowString.end());
            }
            stackRowVec.push_back(rowString);
        }else if(rowString == ""){
            continue;
        }
        else{  // The lines will not be of type "Move X from Y to Z"
            moveVec = getStrVector(rowString, ' ');
            numMoves = stoi(moveVec[1]);
            fromStack = stoi(moveVec[3]);
            toStack = stoi(moveVec[5]);
            
            if(craneModel == 9000){
                for(int i{0}; i < numMoves; i++){
                    crate = stackVec[fromStack-1][stackVec[fromStack-1].length()-1];
                    stackVec[fromStack-1].pop_back();
                    stackVec[toStack-1].push_back(crate);
                }    
            }else if(craneModel == 9001){   // Move multiple crates while preserving order
                int x{0};
                moveMultiCrates = stackVec[fromStack-1].substr(stackVec[fromStack-1].length()-numMoves, stackVec[fromStack-1].length());
                if(constants::DEBUG){
                    cout << "---------------" << endl;
                    cout << "rowString = " << rowString << endl;
                    cout << "stackVeck[" << (fromStack-1) << "] = " << stackVec[fromStack-1] << endl;
                    cout << "Move " << numMoves << " from " << fromStack << " to " << toStack << endl;
                    cout << "moveMultiCrates = " << moveMultiCrates << endl;
                }
                
                stackVec[fromStack-1].erase(stackVec[fromStack-1].length()-numMoves, stackVec[fromStack-1].length());
                stackVec[toStack-1] += moveMultiCrates;

            }
            
        }
      
        if(constants::DEBUG){
            cout << "crateRowString = " << rowString << endl;
        }
              
    }
    ifs.close();

    // figure out string representing crates that end up on top of each stack
    for(int i{0};i < stackVec.size(); i++){
        topCrates.push_back(stackVec[i][stackVec[i].length()-1]);

    }
    return topCrates;
}


