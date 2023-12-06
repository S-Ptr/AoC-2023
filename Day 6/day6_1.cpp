#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <vector>
#include <windows.h>
#include <set>

/*
    This is the solution for the first part of the sixth day of the Advent of Code 2023 challenge.
    The challenge can be found at https://adventofcode.com/2023/day/6

    In this solution, I reduce the "find all possible times" problem into a quadratic inequation, as shown in the comments below.

    Complexity: O(n), where n=number of characters in the input file
*/


int day6_1() {
    std::ifstream file("input6.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }

    std::vector<double> times(0);
    std::vector<double> distances(0);
    std::string line;
    int sum = 1;
    std::getline(file, line);
    int i = line.find(':') + 1;
    //times
    while (i < line.size()) {
        if (isdigit(line[i])) {
            double num = 0;
            while (i < line.size() && line[i] != ' ') {
                num = num * 10 + (line[i] - '0');
                i++;
            }
            times.push_back(num);
        }
        i++;
    }
    //distances
    std::getline(file, line);
    i = line.find(':') + 1;
    while (i < line.size()) {
        if (isdigit(line[i])) {
            double num = 0;
            while (i < line.size() && line[i] != ' ') {
                num = num * 10 + (line[i] - '0');
                i++;
            }
            distances.push_back(num);
        }
        i++;
    }
    for (int i = 0; i < times.size(); i++) {
        //The velocity is represented with the formula v = distance/(time-v); where distance > dMin
        // Simplifying for d, and then replacing d =... with dMin < ... we get v^2 -time*v + distance > 0.
        // We solve for v and get v1 and v2, and calculate the number of integers between them.
        double v1d = (times[i] + sqrt(times[i] * times[i] - 4 * distances[i])) / 2;
        int v1 = (int)(floor((times[i] + sqrt(times[i] * times[i] - 4 * distances[i])) / 2));
        int v2 = (int)(floor((times[i] - sqrt(times[i] * times[i] - 4 * distances[i])) / 2));
        if ((trunc(v1d) == v1d)) {
            std::cout << v1 - v2 - 1 << '\n';
            sum *= v1 - v2 - 1;
        }
        else {
            std::cout << v1 - v2 << '\n';
            sum *= v1 - v2;
        }
    }

    std::cout << sum << std::endl;

    file.close();
    system("pause");

    return 0;
}