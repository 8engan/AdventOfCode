#include <iostream>
#include <iomanip>
#include <vector>
#include "alldays.h"

using namespace std;


int main(){

    int dayToRun{0};
    bool choiceLoop = true;
    string crateString;

    cout << "*** Welcome to my implementation of Advent of Code 2022! ***" << endl;
    
    while(choiceLoop){
        cout << "Please choose what day to run [1-25, 0 to quit]: ";
        cin >> dayToRun;
        switch(dayToRun){
            case 1:
            {
                int maxCalorieCount{0};
                int topOne{};
                int topThree{};
                vector<int> elvesVector;
                
                // Create vector of calorie counts from input file
                elvesVector = getElvesVector("inputs/day1_input.txt");
                topOne = getCalorieCount(elvesVector, 1);
                topThree = getCalorieCount(elvesVector, 3);

                cout << "Day 1 Part 1: Top 1 elf calorie count = " << topOne << endl;
                cout << "Day 1 Part 2: Top 2 elf calorie count = " << topThree << endl;   
                cout << endl;     
                break;
            }     
            case 2:
            {
                int totalScorePart1{0};
                int totalScorePart2{0};

                totalScorePart1 = processStrategyPart1("inputs/day2_input.txt");
                totalScorePart2 = processStrategyPart2("inputs/day2_input.txt");

                cout << "Day 2 Part 1: Total score calculated from file for day2 part 1 of the problem = " << totalScorePart1 << endl;
                cout << "Day 2 Part 2: Total score calculated from file for day2 part 2 of the problem = " << totalScorePart2 << endl;
                cout << endl;
                break;
            }
            case 3:
            {
                int totalPrio{0};
                processAllRucksacks("inputs/day3_input.txt", totalPrio);
                cout << "Day 3 Part 1: Total prio score found when processing rucksacks = " << totalPrio << endl;

                totalPrio = 0;  // reset total prio
                processGroupOfThreeRucksacks("inputs/day3_input.txt", totalPrio);
                cout << "Day 3 Part 2: Total prio score found when processing rucksacks in groups of three = " << totalPrio << endl;
                cout << endl;
                break;
            }
            case 4:
            {
                int totalContained{0};
                int totalOverlap{0};
                processAssignmentList("inputs/day4_input.txt", totalContained, totalOverlap);
                cout << "Day 4 Part 1: Total assignments where one fully contains the other = " << totalContained << endl;
                cout << "Day 4 Part 1: Total assignments where one overlaps the other = " << totalOverlap << endl;
                cout << endl;
                break;
            }
            case 5:
            {
                crateString = processStackchart("inputs/day5_input.txt");
                cout << "Day 5 Part 1: String representing crates on top of each stack when using crane 9000 = " << crateString << endl;
                crateString = processStackchart("inputs/day5_input.txt", 9001);
                cout << "Day 5 Part 2: String representing crates on top of each stack when using crane 9001 = " << crateString << endl;

                break;
            }
            case 6:
            {
                int pos = findMarker("inputs/day6_input.txt", 4);
                cout << "Day 6 Part 1: Start-of-packet sequence found at position: " << pos << endl;
                pos = findMarker("inputs/day6_input.txt", 14);
                cout << "Day 6 Part 2: Start-of-packet sequence found at position: " << pos << endl;

                break;
            }
            case 7:
            {
                int totalSize{0};
                directory rootDir;
                vector<int> dirSizeVec;
                processDay7Output(rootDir, "inputs/day7_input.txt");
                totalSize = getSumDirsBelowSize(rootDir, 100000);
                cout << "Day 7 Part 1: Sum of all directories below size of 10000 is: " << totalSize << endl;
                totalSize = findDirSize(rootDir);
                cout << "Day 7 Part 2: Total size of directory to delete to free up space = " << totalSize << endl;
                break;
            }
            case 8:
            {
                int visibleTrees{0};
                int scenicScore{0};

                processTreeInput("inputs/day8_input.txt", visibleTrees, scenicScore);
                cout << "Day 8 Part 1: Number of trees visible from the grid : " << visibleTrees << endl;
                cout << "Day 8 Part 2: Scenic score given input : " << scenicScore << endl;
                break;
            }
            case 9:
            {
                int cellsVisited{0};
                cellsVisited = processMoveInput("inputs/day9_input.txt");
                cout << "Day 9 Part 1: Positions visited at least once : " << cellsVisited << endl;
                break;
            }
            case 10:
            {
                break;
            }
            case 11:
            {
                break;
            }
            case 12:
            {
                break;
            }
            case 13:
            {
                break;
            }
            case 14:
            {
                break;
            }
            case 15:
            {
                break;
            }
            case 16:
            {
                break;
            }
            case 17:
            {
                break;
            }
            case 18:
            {
                break;
            }
            case 19:
            {
                break;
            }
            case 20:
            {
                break;
            }
            case 21:
            {
                break;
            }
            case 22:
            {
                break;
            }
            case 23:
            {
                break;
            }
            case 24:
            {
                break;
            }
            case 25:
            {
                break;
            }
            case 0:
                choiceLoop = false;
                break;
        }
    }
    
    cout << "Exiting program, thanks for playing :)" << endl;
    return 0;
    
    

}
