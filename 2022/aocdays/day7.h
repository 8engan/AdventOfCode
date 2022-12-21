#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <ranges>
#include <vector>
#include "../constants.h"
#include "../misc.h"



using namespace std; 

struct file{
    string name;
    int fileSize{0};
};

struct directory{
    string name;
    directory* parentDir;
    vector<directory> subDirectories;
    vector<file> dirFiles;

    int getSize(){
        int size{0};
        for(file f : dirFiles){
            size += f.fileSize;
        }
        for(directory d : subDirectories){
            size += d.getSize();
        }
        return size;
    }
};

bool checkDirExist(vector<directory>* subDirs, string dirToCheck){
    for(directory d : *subDirs){
        if(d.name == dirToCheck){
            return true;
        }
    }

    return false;
}

//directory returnNavigateToDir(directory& currDir, string navDir){
directory* returnNavigateToDir(directory* currDir, string navDir){

    for(int i{0}; i < currDir->subDirectories.size(); i++){
        if(currDir->subDirectories[i].name == navDir){
            return &currDir->subDirectories[i];
        }
    }

    return NULL;
}


int getSumDirsBelowSize(directory& dirToCheck, int sizeToCheck){

    int dirSize{0};
    int returnVal{0};
    
    
    // Calculate for dirToCheck
    dirSize = dirToCheck.getSize();
    if(dirSize < sizeToCheck){
        returnVal += dirSize;
    }
        
    for(directory d : dirToCheck.subDirectories){
        returnVal += getSumDirsBelowSize(d, sizeToCheck);
    }
    return returnVal;    
}

vector<int> findDirSizesAboveThreshold(directory& dirToCheck, int threshold){
    int dirSize{0};
    vector<int> dirSizeVec;

    dirSize = dirToCheck.getSize();
    if(dirSize > threshold){
        dirSizeVec.push_back(dirSize);
    }
    for(directory d : dirToCheck.subDirectories){
        vector<int> tmpVec;
        tmpVec = findDirSizesAboveThreshold(d, threshold);
        dirSizeVec.insert(end(dirSizeVec), begin(tmpVec), end(tmpVec));
    }

    return dirSizeVec;
}


int findDirSize(directory& dirToCheck, int fileSystemSpace=70000000, int threshold = 30000000){
    int totalUsed = dirToCheck.getSize();
    int totalAvailable = fileSystemSpace - totalUsed;
    int spaceToRemove = threshold - totalAvailable;

    vector<int> dirSizeVec = findDirSizesAboveThreshold(dirToCheck, spaceToRemove);

    return *min_element(begin(dirSizeVec), end(dirSizeVec));
}

void processDay7Output(directory& rootDir,string inputFile){
    ifstream ifs;
    vector<char> charSeq;
    vector<string> commandVec;
    vector<string> outputVec;
    directory tmpDir;
    directory* currDir;
    string outputLine;
    string command;
    bool initDone = false;
    int lineNum{0};
    
    ifs.open(inputFile);

    while (ifs.good()){
       
        getline(ifs, outputLine);
        if(initDone){
            if(constants::DEBUG){
                cout << "outputline y = " << outputLine << " currDir = " << currDir->name << endl;
            }
        }

        if(outputLine[0] == '$'){     // command
            // parse command
            commandVec = getStrVector(outputLine, ' ');
            
            if(lineNum == 0){
                if(commandVec[1] != "cd" && commandVec[2] != "/"){
                    cout << "1st line of input is non valid, exiting processOutput" << endl;
                    //return nullptr;
                }else{      // create root level node
                    tmpDir = directory();
                    rootDir = tmpDir;
                    currDir = &rootDir;
                    currDir->parentDir = NULL;
                    
                    currDir->name = "/";
                    initDone = true;
                } 
            }else{
                command = commandVec[1];
                if(command == "cd"){
                    string navDir = commandVec[2];
                    if(navDir == ".."){  // move up one
                        currDir = currDir->parentDir;
                    }else{  
                        // only executes if navigating to folder not previously shown in ls command
                        if(!checkDirExist(&currDir->subDirectories, navDir)){
                            currDir->subDirectories.push_back(directory());
                            currDir->subDirectories.back().name = navDir;
                            currDir->subDirectories.back().parentDir = currDir;
                            currDir = &currDir->subDirectories.back();
                        }else{
                            currDir = returnNavigateToDir(currDir, navDir);
                        }
                    }
                }
            }
        }else{  // command output
            if(command == "ls"){
                outputVec = getStrVector(outputLine, ' ');
                if(outputVec[0] == "dir"){
                    if(!checkDirExist(&currDir->subDirectories, outputVec[1])){
                        currDir->subDirectories.push_back(directory());
                        currDir->subDirectories.back().name = outputVec[1];
                        currDir->subDirectories.back().parentDir = currDir;
                    }
                }else{  // file
                    currDir->dirFiles.push_back(file());
                    currDir->dirFiles.back().fileSize = stoi(outputVec[0]);
                    currDir->dirFiles.back().name = outputVec[1];
                }
            }
        }
        lineNum++;
    }
}