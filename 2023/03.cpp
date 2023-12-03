#include <bits/stdc++.h>
using namespace std;

struct Result {
    char symbol;
    int row, col;

    Result(char s, int r, int c) {
        symbol = s;
        row = r;
        col = c;
    }
};

bool isNumber(char c) {
    return c >= '0' && c <= '9';
}

bool isSymbol(char c) {
    return c != '.' && !isNumber(c);
}

vector<Result> findAdjacentSymbols(int row, int col, int maxRow, int maxCol, vector<vector<char>> &engine) {
    vector<Result> adjacentSymbols;
    vector<pair<int, int>> sides = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};
    for (auto &side : sides) {
        int newRow = row + side.first;
        int newCol = col + side.second;
        if (newRow >= 0 && newRow <= maxRow && newCol >= 0 && newCol <= maxCol && isSymbol(engine[newRow][newCol])) {
            adjacentSymbols.push_back(Result(engine[newRow][newCol], newRow, newCol));
        }
    }
    return adjacentSymbols;
}

int main() {
    string line;
    vector<vector<char>> engine;
    int maxRow, maxCol, part1 = 0, part2 = 0;
    while (cin >> line) {
        maxCol = line.length() - 1;
        vector<char> row;
        for (char &c : line) row.push_back(c);
        engine.push_back(row);
    }
    maxRow = engine.size() - 1;
    map<pair<int, int>, vector<int>> possibleGears;
    for (int row = 0; row <= maxRow; ++row) {
        string number = "";
        bool isOk = false;
        vector<Result> results;
        for (int col = 0; col <= maxCol; ++col) {
            char c = engine[row][col];
            vector<Result> adjacentSymbols = findAdjacentSymbols(row, col, maxRow, maxCol, engine);
            bool touchesSymbol = adjacentSymbols.size() > 0;
            if (isNumber(c)) {
                number += c;
                for (Result &r : adjacentSymbols) results.push_back(r);
                if (touchesSymbol) isOk = true;
            }
            if (c == '.' || isSymbol(c)) {
                if (number != "" && isOk) {
                    part1 += stoi(number);
                    map<pair<int, int>, bool> alreadyMarked;
                    for (Result &r : results) {
                        if (!alreadyMarked[{r.row, r.col}]) {
                            possibleGears[{r.row, r.col}].push_back(stoi(number));
                            alreadyMarked[{r.row, r.col}] = true;
                        }
                    }
                }
                number = "";
                isOk = false;
                results = {};
            }
        }
        if (number != "" && isOk) {
            part1 += stoi(number);
            map<pair<int, int>, bool> alreadyMarked;
            for (Result &r : results) {
                if (!alreadyMarked[{r.row, r.col}]) {
                    possibleGears[{r.row, r.col}].push_back(stoi(number));
                    alreadyMarked[{r.row, r.col}] = true;
                }
            }
        }
    }
    for (auto [key, val] : possibleGears) {
        if (val.size() == 2 && engine[key.first][key.second] == '*') {
            part2 += val[0] * val[1];
        }
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
