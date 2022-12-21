#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "../constants.h"

using namespace std; 

int findMarker(string inputFile, int numMarkerChars){

    ifstream ifs;
    vector<char> charSeq;
    bool invalidMarker = false;
    bool beginScan = false;
    int readChar{1};
    char c{0};
    
    ifs.open(inputFile);

    while (ifs.get(c)){
        
        if(constants::DEBUG){
            cout << "Reading char # " << readChar << " = " << c << endl;
        }
        invalidMarker = false;
        charSeq.push_back(c);

        if(readChar > numMarkerChars){
            charSeq.erase(charSeq.begin());
            beginScan = true;
        }

        if(beginScan){
            // Figure out if all X chars are of different type, where X is numMarkerChars
            for(size_t i{0}; i < charSeq.size(); i++){
                if(invalidMarker){
                    break;
                }
                for(size_t j{i+1}; j < charSeq.size();j++){
                    if(charSeq[i] == charSeq[j]){
                        invalidMarker = true;
                        break;
                    }
                }
            }
            if(!invalidMarker){
                if(constants::DEBUG){
                    cout << "Found sequence after reading char: " << c << " at position: " << readChar << endl;
                }
                return readChar;
            }
            
        }
        ++readChar;
     
    }
    return 0;   // no sequence found

}

