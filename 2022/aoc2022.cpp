#include <iostream>
#include <iomanip>
#include <vector>
#include "alldays.h"



int main(){

    int dayToRun{0};
    bool choiceLoop = true;

    std::cout << "Welcome to my implementation of Advent of Code 2022!" << std::endl;
    
    while(choiceLoop){
        std::cout << "Please choose what day to run [1-25, 0 to quit]: ";
        std::cin >> dayToRun;
        switch(dayToRun){
            case 1:
            {
                int maxCalorieCount{0};
                int topOne{};
                int topThree{};
                std::vector<int> elvesVector;
                
                // Create vector of calorie counts from input file
                elvesVector = getElvesVector("inputs/day1_input.txt");
                topOne = getCalorieCount(elvesVector, 1);
                topThree = getCalorieCount(elvesVector, 3);

                std::cout << "Day 1 Part 1: Top 1 elf calorie count = " << topOne << std::endl;
                std::cout << "Day 1 Part 2: Top 2 elf calorie count = " << topThree << std::endl;   
                std::cout << std::endl;     
                break;
            }     
            case 2:
            {
                int totalScorePart1{0};
                int totalScorePart2{0};

                totalScorePart1 = processStrategyPart1("inputs/day2_input.txt");
                totalScorePart2 = processStrategyPart2("inputs/day2_input.txt");

                std::cout << "Day 2 Part 1: Total score calculated from file for day2 part 1 of the problem = " << totalScorePart1 << std::endl;
                std::cout << "Day 2 Part 2: Total score calculated from file for day2 part 2 of the problem = " << totalScorePart2 << std::endl;
                std::cout << std::endl;
                break;
            }
            case 3:
            {
                int totalPrio{0};
                processAllRucksacks("inputs/day3_input.txt", totalPrio);
                std::cout << "Day 3 Part 1: Total prio score found when processing rucksacks = " << totalPrio << std::endl;

                totalPrio = 0;  // reset total prio
                processGroupOfThreeRucksacks("inputs/day3_input.txt", totalPrio);
                std::cout << "Day 3 Part 2: Total prio score found when processing rucksacks in groups of three = " << totalPrio << std::endl;
                std::cout << std::endl;
                break;
            }
            case 4:
            {
                int totalContained{0};
                int totalOverlap{0};
                processAssignmentList("inputs/day4_input.txt", totalContained, totalOverlap);
                std::cout << "Day 4 Part 1: Total assignments where one fully contains the other = " << totalContained << std::endl;
                std::cout << "Day 4 Part 1: Total assignments where one overlaps the other = " << totalOverlap << std::endl;
                std::cout << std::endl;
                break;
            }
            case 5:
            {
                break;
            }
            case 6:
            {
                break;
            }
            case 7:
            {
                break;
            }
            case 8:
            {
                break;
            }
            case 9:
            {
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
    
    std::cout << "Exiting program, thanks for playing :)" << std::endl;
    return 0;
    
    

}
