#include <iostream>
#include <fstream>
#include <string>


/*
    This is the solution for the first part of the first day of the Advent of Code 2023 challenge.
	The challenge can be found at https://adventofcode.com/2023/day/1

    This is a two pointer solution that iterates through the string from both ends to find the first and last digits.

    Complexity: O(n), where n=number of characters in the input file
*/

int day1_1() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }

    std::string line;
    int sum = 0;
    while (std::getline(file, line)) {
        int i = 0, j = line.length() - 1;
        int first = -1, last = -1;
        while (i <= j) {
            if (isdigit(line[i])) {
                first = line[i] - '0';
            }
            if (isdigit(line[j])) {
                last = line[j] - '0';
            }
            if (first != -1 && last != -1) {
                break;
            }
            if (first == -1) i++;
            if (last == -1) j--;
        }
        sum += first * 10 + last;
    }

    std::cout << sum << std::endl;

    file.close();
    system("pause");

    return 0;
}