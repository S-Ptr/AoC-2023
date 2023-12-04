#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

/*
    This is the solution for the first part of the third day of the Advent of Code 2023 challenge.
    The challenge can be found at https://adventofcode.com/2023/day/3

    This is a soluton which keeps track of the symbols and numbers in the previous row to check if there are any vertical or diagonal adjacencies.
    Numbers aren't always kept in the previous row, or even initially added, so as to prevent multiple additions of the same number.

    Complexity: O(n), where n=number of characters in the input file
*/

int day3_1() {
    std::ifstream file("input3.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }

    std::string line;
    std::string symbols = "!\"@#$%^&*()_-+={[}]:;'<,>?/|\\~+-";
    int sum = 0;
    std::getline(file, line);
    std::vector<bool> prevRowSymbols(line.length(), false);
    std::vector<int> prevRowNumbers(line.length(), 0);
    do {
        std::cout << line << '\n';
        int i = 0;
        std::vector<bool> currRowSymbols(line.length(), false);
        std::vector<int> currRowNumbers(line.length(), 0);
        while (i < line.length()) {

            int numbegin;
            if (line[i] == '.') {
                i++;
            }
            else if (symbols.find(line[i]) != -1) {
                currRowSymbols[i] = true;
                if (prevRowNumbers[i] != 0) {
                    std::cout << "added number " << prevRowNumbers[i] << " because of the symbol below it" << '\n';
                    sum += prevRowNumbers[i];
                    for (int j = i; j < prevRowNumbers.size() && prevRowNumbers[j] != 0; j++) {
                        prevRowNumbers[j] = 0;
                    }
                }
                else {
                    sum += prevRowNumbers[i - 1];
                    sum += prevRowNumbers[i + 1];
                    for (int j = i + 1; j < prevRowNumbers.size() && prevRowNumbers[j] != 0; j++) {
                        prevRowNumbers[j] = 0;
                    }
                    std::cout << "added numbers " << prevRowNumbers[i - 1] << " and " << prevRowNumbers[i + 1] << " because of the symbol diagonally below them" << '\n';
                }
                i++;
            }
            else if (isdigit(line[i])) {
                bool alreadyAdded = false;
                numbegin = i;
                while (isdigit(line[i])) i++;
                int num = std::stoi(line.substr(numbegin, i - numbegin));
                if (numbegin != 0) {
                    if (symbols.find(line[numbegin - 1]) != -1) {
                        std::cout << "added number " << num << " because of the symbol on its' left" << '\n';
                        sum += num;
                        continue;
                    }
                    else if (prevRowSymbols[numbegin - 1]) {
                        std::cout << "added number " << num << " because of the symbol on its' top left corner" << '\n';
                        sum += num;
                        continue;
                    }
                }
                if (i != line.length())
                {
                    if (symbols.find(line[i]) != -1) {
                        std::cout << "added number " << num << " because of the symbol on its' right" << '\n';
                        sum += num;
                        continue;
                    }
                    else if (prevRowSymbols[i]) {
                        std::cout << "added number " << num << " because of the symbol on its' top right corner" << '\n';
                        sum += num;
                        continue;
                    }
                }
                for (int j = numbegin; j < i; j++) {
                    if (prevRowSymbols[j]) {
                        std::cout << "added number " << num << " because of the symbol above it" << '\n';
                        sum += num;
                        alreadyAdded = true;
                        break;
                    }
                }
                if (alreadyAdded) continue;
                for (int j = numbegin; j < i; j++)
                {
                    currRowNumbers[j] = num;
                }

            }

        }
        prevRowSymbols = currRowSymbols;
        prevRowNumbers = currRowNumbers;
    } while (std::getline(file, line));

    std::cout << sum << '\n';

    file.close();
    system("pause");

    return 0;
}