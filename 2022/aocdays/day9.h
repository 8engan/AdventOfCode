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
        int xMove{0};
        int yMove{0};
        if((head.x - x) > 1 || (abs(head.y-y ) > 1 && head.x > x)){
            xMove++;
            
        }else if((head.x - x) < -1 || (abs(head.y-y ) > 1 && head.x < x)){
            xMove--;
        }
        // check Y
        if((head.y - y) > 1 || (abs(head.x-x ) > 1 && head.y > y)){
            yMove++;   
        }else if((head.y - y) < -1 || (abs(head.x-x ) > 1 && head.y < y)){
            yMove--;
        }
        x += xMove;
        y += yMove;
    }
    string getPosition(){
        return to_string(x) + to_string(y);
    }
};

void moveHeadOneStep(string moveDir, position& head){

    string visitedPosition;
    
    if(moveDir == "U"){
        head.y += 1;
    }else if(moveDir == "D"){
        head.y -= 1;
    }else if(moveDir == "L"){
        head.x -= 1;
    }else if(moveDir == "R"){
        head.x += 1;
    }
}

void moveHeadTail(vector<string>& tailVisitedCells, string moveDir, int moveSteps, position& head, position& tail, bool fillTailVisited = false){
    for(int step{0}; step < moveSteps; step++){
        moveHeadOneStep(moveDir, head);
        tail.setRelativePosition(head);
        if(fillTailVisited){
            tailVisitedCells.push_back(tail.getPosition());
        }
    }
}

void processPart2Vec(vector<position>& part2Vec, vector<string>& tailVisitedCells, string moveDir, int moveSteps){
    tailVisitedCells.push_back(part2Vec.back().getPosition());
    
    for(int step{1}; step <= moveSteps; step++){  // For every step to move
        if(constants::DEBUG){
            cout << "Step #" << step << " in direction " << moveDir << endl;
        }
        moveHeadOneStep(moveDir, part2Vec[0]);     // Move head of rope 1 step

        if(constants::DEBUG){
            cout << "knot[0] in position " << part2Vec[0].x << ":" << part2Vec[0].y << endl;
        }
        // process rest of knots and move relative to respecitve head (knot 3 has 2 as head, knot 4 has 3, etc.)    
        for(int knot{1}; knot < part2Vec.size(); knot++){     // For every knot on rope, starting with knot 3 on rope as 1-2 has been moved already
            if(part2Vec[knot].getPosition() == part2Vec[knot-1].getPosition()){ // compare knot with its head
                break;  // break out to next step as there are no more knots needed to be moved relative to its head
            }
            part2Vec[knot].setRelativePosition(part2Vec[knot-1]);
            if(constants::DEBUG){
                cout << "knot[" << knot << "] in position " << part2Vec[knot].x << ":" << part2Vec[knot].y << endl;
            }
            if(knot == part2Vec.size()-1){   // keep track of positions visited for last knot = tail of snake only 
                tailVisitedCells.push_back(part2Vec[knot].getPosition()); 
                continue;   // done processing this knot
            }
        }
    }
}

void processMoveInput(int& part1Answer, int& part2Answer, string inputFile){
    ifstream ifs;
    string moveCommand;
    vector<string> moveVec;
    vector<string> tailVisitedCellsPart1, tailVisitedCellsPart2;
    vector<position> part2Vec(10);
    string moveDir;
    int moveSteps{0};
    position head, tail;

    
    ifs.open(inputFile);

    while (ifs.good()){
        getline(ifs, moveCommand);
        moveVec = getStrVector(moveCommand, ' ');
        moveDir = moveVec[0];
        moveSteps = stoi(moveVec[1]);
        moveHeadTail(tailVisitedCellsPart1, moveDir, moveSteps, head, tail, true);    // part 1
        processPart2Vec(part2Vec, tailVisitedCellsPart2, moveDir, moveSteps);   // part 2
        
    }      
    // remove duplicates from tailVisitedCells Part 1 and Part 2
    sort(tailVisitedCellsPart1.begin(), tailVisitedCellsPart1.end());
    tailVisitedCellsPart1.erase(unique(tailVisitedCellsPart1.begin(), tailVisitedCellsPart1.end()), tailVisitedCellsPart1.end());
    sort(tailVisitedCellsPart2.begin(), tailVisitedCellsPart2.end());
    tailVisitedCellsPart2.erase(unique(tailVisitedCellsPart2.begin(), tailVisitedCellsPart2.end()), tailVisitedCellsPart2.end());

    part1Answer = tailVisitedCellsPart1.size();
    part2Answer = tailVisitedCellsPart2.size();

}