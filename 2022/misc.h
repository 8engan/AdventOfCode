#ifndef MISC_H
#define MISC_H

#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<string> getStrVector(string strToSplit, char delim){
    
    stringstream sStream(strToSplit);
    vector<string> returnVec;
    string s;

    while(getline(sStream, s, delim)){
        returnVec.push_back(s);
    }

    return returnVec;

}


#endif