#include <iostream>
#include <fstream>
#include <string>

/*
    This is the solution for both parts of the second day of the Advent of Code 2023 challenge.

    This solution uses basic string parsing to find if any rows are invalid and then sums the valid ids, 
    and also finds the minimum viable values for each color and multiplies each color's value before summing them up.

    This solution also prints out the invalid values and the minimum viable values for each color, for each round.

    Complexity: O(n), where n=number of characters in the input file
*/

int day2() {
    std::ifstream file("input2.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }

    std::string line;
    int maxred = 12;
    int maxgreen = 13;
    int maxblue = 14;

    int sum = 0;
    int powersum = 0;
    while (std::getline(file, line)) {
        std::cout << line << '\n';
        bool valid = true;
        int minred = 0, mingreen = 0, minblue = 0;
        int currentred, currentgreen, currentblue;
        currentred = currentgreen = currentblue = 0;
        int i = 5; //skip "Game " 
        int numbegin = i;
        while (line[i] != ':') {
            i++;
        }
        int id = std::stoi(line.substr(numbegin, i - numbegin));
        i += 2; //skip ": "
        while (i < line.length()) {
            if (line[i - 2] == ';') {
                currentred = currentgreen = currentblue = 0;
            }
            numbegin = i;
            while (isdigit(line[i])) i++;
            if (line[i + 1] == 'r') {
                currentred = std::stoi(line.substr(numbegin, i - numbegin));
                if (currentred > minred) minred = currentred;
                if (currentred > maxred)
                {
                    std::cout << "anomaly found:" << currentred << " red at position " << i << '\n';
                    valid = false;
                }
                i += 6; //skip "red, "
                continue;
            }
            else if (line[i + 1] == 'g') {
                currentgreen = std::stoi(line.substr(numbegin, i - numbegin));
                if (currentgreen > mingreen) mingreen = currentgreen;
                if (currentgreen > maxgreen)
                {
                    std::cout << "anomaly found:" << currentgreen << " green at position " << i << '\n';
                    valid = false;
                }
                i += 8; //skip "green, "
                continue;
            }
            else if (line[i + 1] == 'b') {
                currentblue = std::stoi(line.substr(numbegin, i - numbegin));
                if (currentblue > minblue) minblue = currentblue;
                if (currentblue > maxblue)
                {
                    std::cout << "anomaly found:" << currentblue << " blue at position " << i << '\n';
                    valid = false;
                }
                i += 7; //skip "blue, "
                continue;
            }

        }
        if (valid) sum += id;
        std::cout << "Minimum viable red: " << minred << ", green: " << mingreen << ", blue: " << minblue << '\n';
        powersum += (minred * mingreen * minblue);



    }

    std::cout << sum << '\n';
    std::cout << powersum << std::endl;

    file.close();
    system("pause");

    return 0;
}