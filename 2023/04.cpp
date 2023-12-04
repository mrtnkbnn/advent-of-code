#include <bits/stdc++.h>
using namespace std;

int main() {
    string line;
    int part1 = 0, part2 = 0;
    vector<int> counts = {0}, winAmounts = {0};
    while (getline(cin, line)) {
        int cardNumber = stoi(line.substr(4, line.find(": ")));
        string allNumbers = line.substr(line.find(": ") + 2);
        string winningNumbersString = allNumbers.substr(0, allNumbers.find(" | "));
        string myNumbersString = allNumbers.substr(allNumbers.find(" | ") + 3);
        set<int> winningNumbers;
        stringstream winning(winningNumbersString), my(myNumbersString);
        int n, score = 0, winAmount = 0;
        while (winning >> n) winningNumbers.insert(n);
        while (my >> n) {
            if (winningNumbers.find(n) != winningNumbers.end()) {
                if (score == 0) score = 1;
                else score *= 2;
                ++winAmount;
            }
        }
        part1 += score;
        winAmounts.push_back(winAmount);
        counts.push_back(1);
    }
    int cards = counts.size() - 1;
    for (int i = 1; i <= cards; ++i) {
        part2 += counts[i];
        if (winAmounts[i] > 0) {
            int j = i + 1;
            do {
                if (j > cards) break;
                counts[j] += counts[i];
                ++j;
            } while (--winAmounts[i]);
        }
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
