#include <bits/stdc++.h>
using namespace std;

int main() {
    set<pair<int, int>> elves;
    string line;
    int row = 0;
    while (getline(cin, line)) {
        for (int col = 0; col < line.length(); ++col) {
            if (line[col] == '#') {
                elves.insert({row, col});
            }
        }
        ++row;
    }
    vector<pair<int, int>> allPositions = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
    deque<vector<pair<int, int>>> allDirections = {{{-1, 0}, {-1, 1}, {-1, -1}}, {{1, 0}, {1, 1}, {1, -1}}, {{0, -1}, {-1, -1}, {1, -1}}, {{0, 1}, {1, 1}, {-1, 1}}};
    int round = 1;
    while (true) {
        set<pair<int, int>> newElves;
        map<pair<int, int>, vector<pair<int, int>>> proposals;
        for (auto elf : elves) {
            bool hasAdjacentElves = false;
            for (pair<int, int> position : allPositions) {
                if (elves.find({elf.first + position.first, elf.second + position.second}) != elves.end()) {
                    hasAdjacentElves = true;
                    break;
                }
            }
            if (hasAdjacentElves) {
                bool didPropose = false;
                for (vector<pair<int, int>> directions : allDirections) {
                    bool canMove = true;
                    for (pair<int, int> direction : directions) {
                        if (elves.find({elf.first + direction.first, elf.second + direction.second}) != elves.end()) {
                            canMove = false;
                            break;
                        }
                    }
                    if (canMove) {
                        pair<int, int> newPosition = {elf.first + directions[0].first, elf.second + directions[0].second};
                        if (proposals.find(newPosition) == proposals.end()) {
                            proposals[newPosition] = {elf};
                        } else {
                            proposals[newPosition].push_back(elf);
                        }
                        didPropose = true;
                        break;
                    }
                }
                if (!didPropose) {
                    newElves.insert(elf);
                }
            } else {
                newElves.insert(elf);
            }
        }
        if (proposals.empty()) {
            cout << "Part 2: " << round << endl;
            break;
        }
        for (auto [position, elvesToMove] : proposals) {
            if (elvesToMove.size() == 1) {
                newElves.insert(position);
            } else {
                for (auto elf : elvesToMove) {
                    newElves.insert(elf);
                }
            }
        }
        elves = newElves;
        vector<pair<int, int>> direction = allDirections.front();
        allDirections.pop_front();
        allDirections.push_back(direction);
        if (round == 10) {
            int minRow = INT_MAX, maxRow = INT_MIN, minCol = INT_MAX, maxCol = INT_MIN;
            for (pair<int, int> position : elves) {
                minRow = min(minRow, position.first);
                maxRow = max(maxRow, position.first);
                minCol = min(minCol, position.second);
                maxCol = max(maxCol, position.second);
            }
            int part1 = 0;
            for (int row = minRow; row <= maxRow; ++row) {
                for (int col = minCol; col <= maxCol; ++col) {
                    if (elves.find({row, col}) == elves.end()) {
                        ++part1;
                    }
                }
            }
            cout << "Part 1: " << part1 << endl;
        }
        ++round;
    }
    return 0;
}
