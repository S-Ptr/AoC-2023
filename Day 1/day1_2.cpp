#include <iostream>
#include <fstream>
#include <string>

/*
	This is the solution for the second part of the first day of the Advent of Code 2023 challenge.
    The challenge can be found at https://adventofcode.com/2023/day/1
        
    This solution build a trie from the names of the digits and then searches for the names in it, returning the appropriate digit when found.

    Complexity: O(n), where n=number of characters in the input file
*/

struct TrieNode {
    TrieNode* children[26];//could've optimized the alphabet size, but not worth it
    int value;
    TrieNode() {
        value = -1;
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

int checkfordigits(std::string string, TrieNode* trie) {
    TrieNode* temp = trie;
    for (int i = 0; i < string.length(); i++) {
        int index = string[i] - 'a';
        if (index < 0 || index > 25) return -1;
        if (!temp->children[index]) {
            return -1;
        }
        temp = temp->children[index];
        if (temp->value != -1) {
            return temp->value;
        }
    }
    return -1;
}

int day1_2() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }
    TrieNode* root = new TrieNode();
    std::string digits[10] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
    for (int i = 0; i < 10; i++) {
        TrieNode* temp = root;
        for (int j = 0; j < digits[i].length(); j++) {
            int index = digits[i][j] - 'a';
            if (!temp->children[index]) {
                temp->children[index] = new TrieNode();
            }
            temp = temp->children[index];
        }
        temp->value = i;
    }

    std::string line;
    int sum = 0;

    while (std::getline(file, line)) {
        int first = -1, last = -1;
        for (int i = 0; i < line.length(); i++) {
            if (isdigit(line[i])) {
                if (first == -1) first = line[i] - '0';
                last = line[i] - '0';
                continue;
            }
            int size = ((line.length() - i) > 5) ? 5 : (line.length() - i);
            int value = checkfordigits(line.substr(i, size), root);
            if (value != -1) {
                if (first == -1) first = value;
                last = value;
            }
        }
        sum += first * 10 + last;

    }

    std::cout << sum << std::endl;

    file.close();
    system("pause");

    return 0;
}