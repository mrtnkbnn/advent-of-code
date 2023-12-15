#include <bits/stdc++.h>
using namespace std;
using num = long long;

void rollNorth(vector<string> &dish) {
    for (num col = 0; col < dish[0].length(); ++col) {
        num lastBlocker = -1;
        for (num row = 0; row < dish.size(); ++row) {
            if (dish[row][col] == '#') {
                lastBlocker = row;
            } else if (dish[row][col] == 'O') {
                if (lastBlocker == row - 1) {
                    lastBlocker = row;
                } else {
                    dish[row][col] = '.';
                    dish[lastBlocker + 1][col] = 'O';
                    ++lastBlocker;
                }
            }
        }
    }
}

void rollSouth(vector<string> &dish) {
    for (num col = 0; col < dish[0].length(); ++col) {
        num lastBlocker = dish.size();
        for (num row = dish.size() - 1; row >= 0; --row) {
            if (dish[row][col] == '#') {
                lastBlocker = row;
            } else if (dish[row][col] == 'O') {
                if (lastBlocker == row + 1) {
                    lastBlocker = row;
                } else {
                    dish[row][col] = '.';
                    dish[lastBlocker - 1][col] = 'O';
                    --lastBlocker;
                }
            }
        }
    }
}

void rollWest(vector<string> &dish) {
    for (num row = 0; row < dish.size(); ++row) {
        num lastBlocker = -1;
        for (num col = 0; col < dish[0].length(); ++col) {
            if (dish[row][col] == '#') {
                lastBlocker = col;
            } else if (dish[row][col] == 'O') {
                if (lastBlocker == col - 1) {
                    lastBlocker = col;
                } else {
                    dish[row][col] = '.';
                    dish[row][lastBlocker + 1] = 'O';
                    ++lastBlocker;
                }
            }
        }
    }
}

void rollEast(vector<string> &dish) {
    for (num row = 0; row < dish.size(); ++row) {
        num lastBlocker = dish[0].length();
        for (num col = dish[0].length() - 1; col >= 0; --col) {
            if (dish[row][col] == '#') {
                lastBlocker = col;
            } else if (dish[row][col] == 'O') {
                if (lastBlocker == col + 1) {
                    lastBlocker = col;
                } else {
                    dish[row][col] = '.';
                    dish[row][lastBlocker - 1] = 'O';
                    --lastBlocker;
                }
            }
        }
    }
}

int main() {
    num part1 = 0, part2 = 0, cycleLength, detectedAt;
    string line;
    vector<string> dish;
    map<vector<string>, num> dp;
    while (getline(cin, line)) dish.push_back(line);
    dp[dish] = 0;
    rollNorth(dish);
    for (num row = 0; row < dish.size(); ++row) {
        for (char c : dish[row]) {
            if (c == 'O') part1 += dish.size() - row;
        }
    }
    rollWest(dish);
    rollSouth(dish);
    rollEast(dish);
    dp[dish] = 1;
    for (num cycle = 2; cycle <= 1000000000; ++cycle) {
        rollNorth(dish);
        rollWest(dish);
        rollSouth(dish);
        rollEast(dish);
        if (dp.find(dish) != dp.end()) {
            cycleLength = cycle - dp[dish];
            detectedAt = cycle;
            break;
        }
        dp[dish] = cycle;
    }
    num startAt = ((1000000000 - detectedAt) / cycleLength) * cycleLength + detectedAt;
    num toCycle = 1000000000 - startAt + 1;
    while (--toCycle) {
        rollNorth(dish);
        rollWest(dish);
        rollSouth(dish);
        rollEast(dish);
    }
    for (num row = 0; row < dish.size(); ++row) {
        for (char c : dish[row]) {
            if (c == 'O') part2 += dish.size() - row;
        }
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
