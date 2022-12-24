#include <bits/stdc++.h>
using namespace std;

int ROWS = 0, COLS = 0;

map<pair<int, int>, vector<char>> moveBlizzards(map<pair<int, int>, vector<char>>& valley) {
    map<pair<int, int>, vector<char>> newValley;
    for (auto [pos, items] : valley) {
        if (items.size() == 1 && items[0] == '#') {
            newValley[pos] = {items[0]};
        } else if (items[0] != '#' && items[0] != '.') {
            for (char item : items) {
                pair<int, int> newPos;
                if (item == '<') {
                    if (pos.second - 1 == 0) {
                        newPos = {pos.first, COLS - 2};
                    } else {
                        newPos = {pos.first, pos.second - 1};
                    }
                } else if (item == '>') {
                    if (pos.second + 1 == COLS - 1) {
                        newPos = {pos.first, 1};
                    } else {
                        newPos = {pos.first, pos.second + 1};
                    }
                } else if (item == 'v') {
                    if (pos.first + 1 == ROWS - 1) {
                        newPos = {1, pos.second};
                    } else {
                        newPos = {pos.first + 1, pos.second};
                    }
                } else {
                    if (pos.first - 1 == 0) {
                        newPos = {ROWS - 2, pos.second};
                    } else {
                        newPos = {pos.first - 1, pos.second};
                    }
                }
                if (newValley.find(newPos) == newValley.end()) {
                    newValley[newPos] = {item};
                } else {
                    newValley[newPos].push_back(item);
                }
            }
        }
    }
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            if (newValley.find({row, col}) == newValley.end()) {
                newValley[{row, col}] = {'.'};
            }
        }
    }
    return newValley;
}

vector<vector<char>> toVector(map<pair<int, int>, vector<char>>& valley) {
    vector<vector<char>> result;
    for (int row = 0; row < ROWS; ++row) {
        vector<char> rowVector;
        for (int col = 0; col < COLS; ++col) {
            if (valley[{row, col}].size() > 1) {
                rowVector.push_back(valley[{row, col}].size() + '0');
            } else {
                rowVector.push_back(valley[{row, col}][0]);
            }
        }
        result.push_back(rowVector);
    }
    return result;
}

int best = INT_MAX;
map<tuple<int, int, int>, int> MEM;

int findMinPath(vector<vector<vector<char>>>& blizzardPositions, int currentRow, int currentCol, int endRow, int endCol, int minute, int blizzardPosition) {
    if (minute - 1 >= best || minute > 300) {
        return INT_MAX;
    }
    if (currentRow == endRow && currentCol == endCol) {
        best = min(best, minute - 1);
        return minute - 1;
    }
    int mod = blizzardPositions.size();
    tuple<int, int, int> state = {blizzardPosition % mod, currentRow, currentCol};
    if (MEM.find(state) == MEM.end()) {
        MEM.insert({state, minute});
    } else {
        if (minute >= MEM[state]) {
            return INT_MAX;
        }
    }
    vector<vector<char>> valley = blizzardPositions[blizzardPosition % mod];
    vector<int> results;
    if (currentRow + 1 < ROWS && valley[currentRow + 1][currentCol] == '.') {
        results.push_back(findMinPath(blizzardPositions, currentRow + 1, currentCol, endRow, endCol, minute + 1, blizzardPosition + 1));
    }
    if (currentCol + 1 < COLS && valley[currentRow][currentCol + 1] == '.') {
        results.push_back(findMinPath(blizzardPositions, currentRow, currentCol + 1, endRow, endCol, minute + 1, blizzardPosition + 1));
    }
    if (currentRow - 1 >= 0 && valley[currentRow - 1][currentCol] == '.') {
        results.push_back(findMinPath(blizzardPositions, currentRow - 1, currentCol, endRow, endCol, minute + 1, blizzardPosition + 1));
    }
    if (currentCol - 1 >= 0 && valley[currentRow][currentCol - 1] == '.') {
        results.push_back(findMinPath(blizzardPositions, currentRow, currentCol - 1, endRow, endCol, minute + 1, blizzardPosition + 1));
    }
    if (valley[currentRow][currentCol] == '.') {
        results.push_back(findMinPath(blizzardPositions, currentRow, currentCol, endRow, endCol, minute + 1, blizzardPosition + 1));
    }
    int result = INT_MAX;
    for (int r : results) {
        result = min(r, result);
    }
    return result;
}

int main() {
    string line;
    map<pair<int, int>, vector<char>> valley;
    while (getline(cin, line)) {
        for (int col = 0; col < line.size(); ++col) {
            valley[{ROWS, col}] = {line[col]};
        }
        COLS = line.size();
        ++ROWS;
    }
    int startRow = 0, startCol, endRow = ROWS - 1, endCol;
    for (int col = 0; col < COLS; ++col) {
        if (valley[{startRow, col}][0] == '.') {
            startCol = col;
        }
        if (valley[{endRow, col}][0] == '.') {
            endCol = col;
        }
    }
    map<pair<int, int>, vector<char>> current = valley;
    vector<vector<vector<char>>> blizzardPositions;
    blizzardPositions.push_back(toVector(current));
    while (true) {
        map<pair<int, int>, vector<char>> next = moveBlizzards(current);
        if (next == valley) {
            break;
        } else {
            blizzardPositions.push_back(toVector(next));
            current = next;
        }
    }
    int part1 = findMinPath(blizzardPositions, startRow, startCol, endRow, endCol, 1, 1);
    cout << "Part 1: " << part1 << endl;
    best = INT_MAX;
    MEM.clear();
    int toSnacks = findMinPath(blizzardPositions, endRow, endCol, startRow, startCol, 1, part1 + 1);
    best = INT_MAX;
    MEM.clear();
    int toGoal = findMinPath(blizzardPositions, startRow, startCol, endRow, endCol, 1, part1 + toSnacks + 1);
    int part2 = part1 + toSnacks + toGoal;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
