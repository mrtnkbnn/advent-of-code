#include <bits/stdc++.h>
using namespace std;

int main() {
    map<string, string> numbers = {
        {"one", "1"},
        {"two", "2"},
        {"three", "3"},
        {"four", "4"},
        {"five", "5"},
        {"six", "6"},
        {"seven", "7"},
        {"eight", "8"},
        {"nine", "9"}
    };
    string line;
    int part1 = 0, part2 = 0;
    while (cin >> line) {
        int firstDigitIndex = line.find_first_of("0123456789");
        int lastDigitIndex = line.find_last_of("0123456789");
        int firstWordIndex = INT_MAX, lastWordIndex = INT_MIN;
        string firstWord, lastWord;
        for (auto [word, num] : numbers) {
            int firstIndex = line.find(word);
            int lastIndex = line.rfind(word);
            if (firstIndex != -1 && firstIndex < firstWordIndex) {
                firstWordIndex = firstIndex;
                firstWord = numbers[word];
            }
            if (lastIndex != -1 && lastIndex > lastWordIndex) {
                lastWordIndex = lastIndex;
                lastWord = numbers[word];
            }
        }
        if (firstDigitIndex != -1 && lastDigitIndex != -1) {
            part1 += stoi(string() + line[firstDigitIndex] + line[lastDigitIndex]);
        }
        firstDigitIndex = firstDigitIndex == -1 ? INT_MAX : firstDigitIndex;
        lastDigitIndex = lastDigitIndex == -1 ? INT_MIN : lastDigitIndex;
        string number;
        if (firstDigitIndex < firstWordIndex) {
            number += line[firstDigitIndex];
        } else {
            number += firstWord;
        }
        if (lastDigitIndex > lastWordIndex) {
            number += line[lastDigitIndex];
        } else {
            number += lastWord;
        }
        part2 += stoi(number);
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
