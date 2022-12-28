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
            y = head.y;
        }else if((head.x - x) < -1){
            x--;
            y = head.y;
        }
        //check y
        if((head.y - y) > 1){
            y++;
            x = head.x;
        }else if((head.y - y) < -1){
            y--;
            x = head.x;
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

void moveHeadTail(vector<string>& tailVisitedCells, string moveDir, int moveSteps, position& head, position& tail, bool fillTailVisited = false){

    string visitedPosition;
    if(moveDir == "U"){
        if(constants::DEBUG && fillTailVisited){
            cout << "Moving " << moveSteps << " up" << endl;
        }
        for(int step{1}; step <= moveSteps; step++){
            head.y += 1;
            if(head.y - tail.y == 2){
                tail.x = head.x;
            }
            tail.setRelativePosition(head);
            if(fillTailVisited){tailVisitedCells.push_back(tail.getPosition());}
        }
    }else if(moveDir == "D"){
        if(constants::DEBUG && fillTailVisited){
            cout << "Moving " << moveSteps << " down" << endl;
        }
        for(int step{1}; step <= moveSteps; step++){
            head.y -= 1;
            if(head.y - tail.y == -2){
                tail.x = head.x;
            }
            tail.setRelativePosition(head);
            if(fillTailVisited){tailVisitedCells.push_back(tail.getPosition());}
        }
    }else if(moveDir == "L"){
        if(constants::DEBUG && fillTailVisited){
            cout << "Moving " << moveSteps << " left" << endl;
        }
        for(int step{1}; step <= moveSteps; step++){
            head.x -= 1;
            if(head.x - tail.x == -2){
                tail.y = head.y;
            }
            tail.setRelativePosition(head);
            if(fillTailVisited){tailVisitedCells.push_back(tail.getPosition());}
        }
        
    }else if(moveDir == "R"){
        if(constants::DEBUG && fillTailVisited){
            cout << "Moving " << moveSteps << " right" << endl;
        }
        for(int step{1}; step <= moveSteps; step++){
            head.x += 1;
            if(head.x - tail.x == 2){
                tail.y = head.y;
            }
            tail.setRelativePosition(head);
            if(fillTailVisited){tailVisitedCells.push_back(tail.getPosition());}
        }
    }
}

void moveHeadOneStep(string moveDir, position& head, position& tail){

    string visitedPosition;
    
    if(moveDir == "U"){
        head.y += 1;
        /*if(head.y - tail.y == 2){
            tail.x = head.x;
        }*/
        //tail.setRelativePosition(head);
    
    }else if(moveDir == "D"){
        head.y -= 1;
        /*if(head.y - tail.y == -2){
            tail.x = head.x;
        }*/
        //tail.setRelativePosition(head);    
    }else if(moveDir == "L"){
        head.x -= 1;
        /*if(head.x - tail.x == -2){
            tail.y = head.y;
        }*/
        //tail.setRelativePosition(head);
    }else if(moveDir == "R"){
        head.x += 1;
        /*if(head.x - tail.x == 2){
            tail.y = head.y;
        }*/
        //tail.setRelativePosition(head);
    }
    tail.setRelativePosition(head);
}

/*void checkRelativeMovementAndMove(vector<string>& tailVisitedCells, position& head, position& tail){
    string moveDir;
    bool headMovedRelativeToTail = false;

    
    // Figure out direction of move on head relative tail (step > 2 = direction)
    if(head.y > tail.y + 1 && head.x > tail.x){     // diagonal move
        moveDir = "UR"; // UP RIGHT DIAGONAL
        tail.y += 1;
        head.x += 1;
    }
    else if((head.y < tail.y - 1 && head.x > tail.x)){
        moveDir == "DR";    // DOWN RIGHT DIAGONAL
        tail.y -= 1;
        head.x += 1;
    }
    else if(head.y > tail.y + 1 && head.x < tail.x){
        moveDir == "UL";    // UP LEFT DIAGONAL
        tail.y += 1;
        head.x -= 1;
    }
    else if(head.y < tail.y - 1 && head.x < tail.x){
        moveDir == "DL";    // DOWN LEFT DIAGONAL
        tail.y -= 1;
        head.x -= 1;
    }
    else if(head.y > tail.y + 1){
        moveDir = "U";
        tail.y += 1;
    }else if(head.y < tail.y - 1){
        moveDir = "D";
        tail.y -= 1;
    } else if(head.x < tail.x - 1){
        moveDir = "L";
        tail.x -= 1;
    } else if(head.x > tail.x + 1){
        moveDir = "R";
        tail.x += 1;
    }*/

    /*if(headMovedRelativeToTail){
        moveHeadTailOneStep(moveDir, head, tail);
        
    }

    tail.setRelativePosition(head);
    if(fillTailVisited){
        cout << "moveDir = " << moveDir << " Tail visited " << tail.getPosition() << endl;
        tailVisitedCells.push_back(tail.getPosition()); 
    }
}*/

void processPart2Vec(vector<position>& part2Vec, vector<string>& tailVisitedCells, string moveDir, int moveSteps){
    tailVisitedCells.push_back(part2Vec.back().getPosition());
    //cout << "Moving " << moveSteps << " in direction: " << moveDir << endl;
    for(int step{1}; step <= moveSteps; step++){  // For every step to move
        // Move head one step
        //cout << "Moving knot 0 & 1 step " << step << endl;
        moveHeadOneStep(moveDir, part2Vec[0], part2Vec[1]);     // Move head of rope 1 step

        // process rest of knots and move relative to respecitve head (knot 3 has 2 as head, knot 4 has 3, etc.)
        
        for(int knot{2}; knot < part2Vec.size(); knot++){     // For every knot on rope, starting with knot 3 on rope as 1-2 has been moved already
            //cout << "Processing knot " << knot << endl;
            /*if(knot == 6){
                cout << "" << endl;
            }*/
            //if(knot > part2Vec.size()-2){   // do not process last knot since it has no further tail
            //    break;
            //}
            if(part2Vec[knot].getPosition() == part2Vec[knot-1].getPosition()){ // compare knot with its head
                //cout << "Breaking out from knot loop as knot " << knot << " and knot " << knot - 1 << " are in the same position " << endl;
                break;  // break out to next step as there are no more knots needed to be moved relative to its head
            }
            part2Vec[knot].setRelativePosition(part2Vec[knot-1]);
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