#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "../constants.h"
#include "../misc.h"

using namespace std; 

bool treeIsVisible(vector<vector<int>>& treeVec, int row, int col){

    int treeHeight{treeVec[row][col]};
    bool treeIsVisible = false;
    

    // Outer "rim" always visible
    if(row == 0 || col == 0 || col == (treeVec[row].size()-1) || row == (treeVec.size()-1)){
        treeIsVisible = true;
        if(constants::DEBUG){
            if(treeIsVisible){
                cout << "treeVec[" << row << "][" << col << "] with height: " << treeHeight << " is on the rim and therefor visible" << endl;
            }
        }
        return true;
    }

    // Move up
    for(int i{row-1}; i >= 0; i--){
        if(treeVec[i][col] >= treeHeight){   // can not be seen
            treeIsVisible = false;
            break;
        }else{
            treeIsVisible = true;
        }
    }
    
    if(treeIsVisible){
        if(constants::DEBUG){
            cout << "treeVec[" << row << "][" << col << "] with height: " << treeHeight << " is visible upwards" << endl;
        }
        return treeIsVisible;
    }
    
    treeIsVisible = false;
    
    
    // Move down
    for(int i{row+1}; i < treeVec.size(); i++){
        if(treeVec[i][col] >= treeHeight){   // can not be seen
            treeIsVisible = false;
            break;
        }else{
            treeIsVisible = true;
        }
    }
    if(treeIsVisible){
        if(constants::DEBUG){
            cout << "treeVec[" << row << "][" << col << "] with height: " << treeHeight << " is visible downwards" << endl;
        }
        return treeIsVisible;
    }
    
    treeIsVisible = false;

    // Move left
    for(int j{col-1}; j >= 0; j--){
        if(treeVec[row][j] >= treeHeight){   // can not be seen
            treeIsVisible = false;
            break;
        }else{
            treeIsVisible = true;
        }
    }
    if(treeIsVisible){
        if(constants::DEBUG){
            cout << "treeVec[" << row << "][" << col << "] with height: " << treeHeight << " is visible leftwards" << endl;
        }
        return treeIsVisible;
    }
    
    // Move right
    for(int j{col+1}; j < treeVec[row].size(); j++){
        if(treeVec[row][j] >= treeHeight){   // can not be seen
            treeIsVisible = false;
            break;
        }else{
            treeIsVisible = true;
        }
    }
    if(treeIsVisible){
        if(constants::DEBUG){
            cout << "treeVec[" << row << "][" << col << "] with height: " << treeHeight << " is visible rightwards" << endl;
        }
        return treeIsVisible;
    }
    
    return treeIsVisible;

}

int calcScenicScore(vector<vector<int>>& treeVec, int row, int col){
    int treeHeight{treeVec[row][col]};
    int tmpMultipler{0};
    int multiplierUp{0};
    int multiplierDown{0};
    int multiplierLeft{0};
    int multiplierRight{0};
    int scenicScore{0};

    // Outer "rim" always with 0 scenic score
    if(row == 0 || col == 0 || col == (treeVec[row].size()-1) || row == (treeVec.size()-1)){
        
        if(constants::DEBUG){
            if(treeIsVisible){
                cout << "treeVec[" << row << "][" << col << "] with height: " << treeHeight << " is on the rim, with scenic score 0" << endl;
            }
        }
        return 0;
    }

    // Move up and get multiplier
    for(int i{row-1}; i >= 0; i--){
        if(treeVec[i][col] <= treeHeight){  
            tmpMultipler++;
            if(treeVec[i][col] == treeHeight){
                break;    
            }
        }else{
            break;
        }
    }
    multiplierUp = tmpMultipler;
    tmpMultipler = 0;
    // Move down and get multiplier
    for(int i{row+1}; i < treeVec.size(); i++){
        if(treeVec[i][col] <= treeHeight){   
            tmpMultipler++;
            if(treeVec[i][col] == treeHeight){
                break;    
            }
        }else{
            break;
        }
    }
    multiplierDown = tmpMultipler;
    tmpMultipler = 0;
    // Move left and get multiplier
    for(int j{col-1}; j >= 0; j--){
        if(treeVec[row][j] <= treeHeight){
            tmpMultipler++;
            if(treeVec[row][j] == treeHeight){
                break;    
            }
        }else{
            break;
        }
    }
    multiplierLeft = tmpMultipler;
    tmpMultipler = 0;
    // Move right and get multiplier
    for(int j{col+1}; j < treeVec[row].size(); j++){
        if(treeVec[row][j] <= treeHeight){
            tmpMultipler++;
            if(treeVec[row][j] == treeHeight){
                break;    
            }
        }else{
            break;
        }
    }
    multiplierRight = tmpMultipler;
    
    scenicScore = multiplierUp * multiplierDown * multiplierLeft * multiplierRight; 

    if(constants::DEBUG){
        cout << "treeVec[" << row << "][" << col << "] with height: " << treeHeight << " has Scenic score = " << scenicScore;
        cout << setw(5) << left << "    " << multiplierUp << " * " << multiplierDown << " * " << multiplierLeft << " * " << multiplierRight << endl;
    }
    
    
    return scenicScore;

}

void getAnswers(vector<vector<int>>& treeVec, int& visibleTrees, int& scenicScore){

    //int visibleTrees{0};
    int checkTree{0};
    int tmpScenicScore{0};

    // Step through each entry in the treeVec and decide if visible
    for(int i{0}; i < treeVec.size(); i++){
        for(int j{0}; j < treeVec[i].size(); j++){
            
            visibleTrees += treeIsVisible(treeVec, i, j) ? 1 : 0;
            tmpScenicScore = calcScenicScore(treeVec, i, j);
            scenicScore = tmpScenicScore > scenicScore ? tmpScenicScore : scenicScore;
            checkTree++;
        }
    }
    if(constants::DEBUG){
        cout << "Total trees checked : " << checkTree << endl;
    }
    
    
}





void processTreeInput(string inputFile, int& visibleTrees, int& scenicScore){
    ifstream ifs;
    string treeLine;
    int lineNum{0};
    const int numAsciiOffset{48};
    vector<vector<int>> treeVec;
    vector<int> horizontalVec;
    
    ifs.open(inputFile);

    while (ifs.good()){
        getline(ifs, treeLine);
        for(size_t i{0}; i < treeLine.length(); i++){
            horizontalVec.push_back(treeLine[i] - numAsciiOffset);
        }
        treeVec.push_back(horizontalVec);
        horizontalVec.clear();
        lineNum++;
    }
    
    getAnswers(treeVec, visibleTrees, scenicScore);
    

}