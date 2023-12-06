#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <vector>
#include <windows.h>
#include <set>

/*
    This is the solution for the second part of the fourth day of the Advent of Code 2023 challenge.
    The challenge can be found at https://adventofcode.com/2023/day/6

    In this solution, I reduce the "find all possible times" problem into a quadratic inequation, as shown in the comments below.
    Part two only changes the file processing to weed out bruteforce solutions

    Complexity: O(n), where n=number of characters in the input file
*/



int main() {
    std::ifstream file("input6.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }

    double time = 0;
    double distance = 0;
    std::string line;
    int sum = 1;
    std::getline(file, line);
    int i = line.find(':') + 1;
    //time
    while (i < line.size()) {
        if (isdigit(line[i])) {
            time = time * 10 + (line[i] - '0');
        }
        i++;
    }
    //distance
    std::getline(file, line);
    i = line.find(':') + 1;
    while (i < line.size()) {
        if (isdigit(line[i])) {
            distance = distance * 10 + (line[i] - '0');
        }
        i++;
    }
    //The velocity is represented with the formula v = distance/(time-v); where distance > dMin
    // Simplifying for d, and then replacing d =... with dMin < ... we get v^2 -time*v + distance > 0.
    // We solve for v and get v1 and v2, and calculate the number of integers between them.
    double v1d = (time + sqrt(time * time - 4 * distance)) / 2;
    double v1 = (floor((time + sqrt(time * time - 4 * distance)) / 2));
    double v2 = (floor((time - sqrt(time * time - 4 * distance)) / 2));
    if ((trunc(v1d) == v1d)) {
        std::cout << std::fixed << v1 - v2 - 1 << '\n';
    }
    else {
        std::cout << std::fixed << v1 - v2 << '\n';
    }


    file.close();
    system("pause");

    return 0;
}