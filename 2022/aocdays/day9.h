#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "../constants.h"
#include "../misc.h"

using namespace std; 

struct position{
    int x{0};
    int y{0};

    void setRelativePosition(position& head){
        //check X
        if((head.x - x) > 1){
            x++;
        }else if((head.x - x) < -1){
            x--;
        }
        //check y
        if((head.y - y) > 1){
            y++;
        }else if((head.y - y) < -1){
            y--;
        }

        if(constants::DEBUG){
            cout << "setRelativePosition -   Head position [" << head.x << "][" << head.y << "]";
            cout << "    Tail position [" << x << "][" << y << "]" << endl;
        }
    }
    string getPosition(){
        return to_string(x) + to_string(y);
    }
};

string moveHeadTail(string moveDir, int moveSteps, position& head, position& tail){

    string visitedPosition;
    if(moveDir == "U"){
            if(constants::DEBUG){
                cout << "Moving " << moveSteps << " up" << endl;
            }
            for(int step{1}; step <= moveSteps; step++){
                head.y += 1;
                if(head.y - tail.y == 2){
                    tail.x = head.x;
                }
                tail.setRelativePosition(head);
                //tailVisitedCells.push_back(tail.getPosition());
                

            }
        }else if(moveDir == "D"){
            if(constants::DEBUG){
                cout << "Moving " << moveSteps << " down" << endl;
            }
            for(int step{1}; step <= moveSteps; step++){
                head.y -= 1;
                if(head.y - tail.y == -2){
                    tail.x = head.x;
                }
                tail.setRelativePosition(head);
                //tailVisitedCells.push_back(tail.getPosition());
            }

        }else if(moveDir == "L"){
            if(constants::DEBUG){
                cout << "Moving " << moveSteps << " left" << endl;
            }
            for(int step{1}; step <= moveSteps; step++){
                head.x -= 1;
                if(head.x - tail.x == -2){
                    tail.y = head.y;
                }
                tail.setRelativePosition(head);
                //tailVisitedCells.push_back(tail.getPosition());
            }
            
        }else if(moveDir == "R"){
            if(constants::DEBUG){
                cout << "Moving " << moveSteps << " right" << endl;
            }
            for(int step{1}; step <= moveSteps; step++){
                head.x += 1;
                if(head.x - tail.x == 2){
                    tail.y = head.y;
                }
                tail.setRelativePosition(head);
                //tailVisitedCells.push_back(tail.getPosition());
            }
        }
    return tail.getPosition();
}

int processMoveInput(string inputFile){
    ifstream ifs;
    string moveCommand;
    vector<string> moveVec;
    vector<string> tailVisitedCells;
    string moveDir;
    int moveSteps{0};
    position head, tail;

    
    ifs.open(inputFile);

    while (ifs.good()){
        getline(ifs, moveCommand);
        moveVec = getStrVector(moveCommand, ' ');
        moveDir = moveVec[0];
        moveSteps = stoi(moveVec[1]);
        if(moveDir == "U"){
            if(constants::DEBUG){
                cout << "Moving " << moveSteps << " up" << endl;
            }
            for(int step{1}; step <= moveSteps; step++){
                head.y += 1;
                if(head.y - tail.y == 2){
                    tail.x = head.x;
                }
                tail.setRelativePosition(head);
                tailVisitedCells.push_back(tail.getPosition());
            }
        }else if(moveDir == "D"){
            if(constants::DEBUG){
                cout << "Moving " << moveSteps << " down" << endl;
            }
            for(int step{1}; step <= moveSteps; step++){
                head.y -= 1;
                if(head.y - tail.y == -2){
                    tail.x = head.x;
                }
                tail.setRelativePosition(head);
                tailVisitedCells.push_back(tail.getPosition());
            }

        }else if(moveDir == "L"){
            if(constants::DEBUG){
                cout << "Moving " << moveSteps << " left" << endl;
            }
            for(int step{1}; step <= moveSteps; step++){
                head.x -= 1;
                if(head.x - tail.x == -2){
                    tail.y = head.y;
                }
                tail.setRelativePosition(head);
                tailVisitedCells.push_back(tail.getPosition());
            }
            
        }else if(moveDir == "R"){
            if(constants::DEBUG){
                cout << "Moving " << moveSteps << " right" << endl;
            }
            for(int step{1}; step <= moveSteps; step++){
                head.x += 1;
                if(head.x - tail.x == 2){
                    tail.y = head.y;
                }
                tail.setRelativePosition(head);
                tailVisitedCells.push_back(tail.getPosition());
            }
        }
        
    }  
    
    // remove duplicates from tailVisitedCells
    sort(tailVisitedCells.begin(), tailVisitedCells.end());
    tailVisitedCells.erase(unique(tailVisitedCells.begin(), tailVisitedCells.end()), tailVisitedCells.end());


    return tailVisitedCells.size();   

}