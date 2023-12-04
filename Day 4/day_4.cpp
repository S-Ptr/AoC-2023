#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <vector>

/*
    This is the solution for the first and second part of the fourth day of the Advent of Code 2023 challenge.
    The challenge can be found at https://adventofcode.com/2023/day/4

    This solution uses a bitset to keep track of the numbers in the first part of the series, and then checks if any of the numbers
    in the second series are in the bitset, updating the score accordingly.

    For the second part, a vector keeps updating the amount of cards gained for each winning card.

    Complexity: O(n), where n=number of characters in the input file
*/

int main() {
    std::ifstream file("input4.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }

    std::string line;
    std::bitset<100> numbers{ 0x0 };

    std::vector<long> totalcards;
    int card_id = 0;

    int sum = 0;
    while (std::getline(file, line)) {
        if (card_id == totalcards.size()) {
            totalcards.push_back(1);
        }
        else {
            totalcards[card_id] += 1;
        }
        std::cout << line << '\n';
        int points = 0;
        int bonusindex = card_id + 1;
        int i = 5;
        while (line[i] != ':') i++;//skipping straight to the first number
        i += 2;
        while (line[i] != '|') {
            if (isdigit(line[i])) {
                int numbegin = i;
                while (isdigit(line[i])) i++;
                int num = std::stoi(line.substr(numbegin, i - numbegin));
                numbers.set(num);
            }
            i++;
        }
        i += 2;
        while (i < line.length()) {
            if (isdigit(line[i])) {
                int numbegin = i;
                while (isdigit(line[i])) i++;
                int num = std::stoi(line.substr(numbegin, i - numbegin));
                if (numbers[num] == true) {
                    if (bonusindex == totalcards.size()) {
                        totalcards.push_back(totalcards[card_id]);
                    }
                    else {
                        totalcards[bonusindex] += totalcards[card_id];
                    }
                    bonusindex++;
                    if (points == 0) points = 1;
                    else points *= 2;
                }
            }
            i++;
        }
        sum += points;
        numbers.reset();
        card_id++;
    }


    std::cout << sum << '\n';

    long bonusamount = 0;
    for (long bonus : totalcards) {
        std::cout << bonus << '\n';
        bonusamount += bonus;
    }

    std::cout << totalcards.size() << '\n';
    std::cout << bonusamount << '\n';


    file.close();
    system("pause");

    return 0;
}