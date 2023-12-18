#include <bits/stdc++.h>
using namespace std;
using num = long long;

struct State {
    num heatLoss;
    num directionCount;
    string direction;
    bool used;

    State(num _heatLoss, num _directionCount, string _direction) {
        heatLoss = _heatLoss;
        directionCount = _directionCount;
        direction = _direction;
        used = false;
    };
};

pair<pair<num, num>, State> find(vector<vector<vector<State>>> &dp) {
    num minHeatLoss = LONG_LONG_MAX;
    pair<num, num> bestLocation;
    State bestState = State(-1, -1, "N");
    for (num row = 0; row < dp.size(); ++row) {
        for (num col = 0; col < dp[0].size(); ++col) {
            vector<State> states = dp[row][col];
            if (!states.empty()) {
                for (State &s : states) {
                    if (!s.used) {
                        if (s.heatLoss < minHeatLoss) {
                            minHeatLoss = s.heatLoss;
                            bestLocation = {row, col};
                            bestState = s;
                        }
                    }
                }
            }
        }
    }
    if (minHeatLoss != LONG_LONG_MAX) {
        bestState.used = true;
        for (auto &s : dp[bestLocation.first][bestLocation.second]) {
            if (s.direction == bestState.direction && s.heatLoss == bestState.heatLoss && s.directionCount == bestState.directionCount) s.used = true;
        }
        return {bestLocation, bestState};
    }
    return {{-1, -1}, State(-1, -1, "N")};
}

num part1(vector<vector<num>> &grid) {
    num part1 = LONG_LONG_MAX, rows = grid.size(), cols = grid[0].size();
    vector<vector<vector<State>>> dp(rows, vector<vector<State>>(cols, vector<State>(1, State(LONG_LONG_MAX, LONG_LONG_MAX, "N"))));
    dp[0][0].push_back(State(0, 0, "N"));
    num historyLimit = 6;
    while (true) {
        pair<pair<num, num>, State> current = find(dp);
        if (current.first.first == -1 || current.first.second == -1) break;
        pair<num, num> currentLocation = current.first;
        State currentState = current.second;
        num currentHeatLoss = currentState.heatLoss;
        num currentDirectionCount = currentState.directionCount;
        string currentDirection = currentState.direction;
        if (currentLocation.first == rows - 1 && currentLocation.second == cols - 1) {
            part1 = min(part1, currentHeatLoss);
            continue;
        }
        if (currentHeatLoss >= part1) continue;

        // Right
        if (currentDirection != "L" && !(currentDirection == "R" && currentDirectionCount == 3) && currentLocation.second + 1 < cols) {
            pair<num, num> newLocation = {currentLocation.first, currentLocation.second + 1};
            num newHeatLoss = currentHeatLoss + grid[newLocation.first][newLocation.second];
            string newDirection = "R";
            num newDirectionCount = currentDirection == newDirection ? currentDirectionCount + 1 : 1;
            bool addNew = true;
            num count = 0;
            for (State &s : dp[newLocation.first][newLocation.second]) {
                if (s.direction == newDirection && s.directionCount == newDirectionCount) addNew = false;
            }
            if (addNew) dp[newLocation.first][newLocation.second].push_back(State(newHeatLoss, newDirectionCount, newDirection));
        }

        // Down
        if (currentDirection != "U" && !(currentDirection == "D" && currentDirectionCount == 3) && currentLocation.first + 1 < rows) {
            pair<num, num> newLocation = {currentLocation.first + 1, currentLocation.second};
            num newHeatLoss = currentHeatLoss + grid[newLocation.first][newLocation.second];
            string newDirection = "D";
            num newDirectionCount = currentDirection == newDirection ? currentDirectionCount + 1 : 1;
            bool addNew = true;
            num count = 0;
            for (State &s : dp[newLocation.first][newLocation.second]) {
                if (s.direction == newDirection && s.directionCount == newDirectionCount) addNew = false;
            }
            if (addNew) dp[newLocation.first][newLocation.second].push_back(State(newHeatLoss, newDirectionCount, newDirection));
        }

        // Left
        if (currentDirection != "R" && !(currentDirection == "L" && currentDirectionCount == 3) && currentLocation.second - 1 >= 0) {
            pair<num, num> newLocation = {currentLocation.first, currentLocation.second - 1};
            num newHeatLoss = currentHeatLoss + grid[newLocation.first][newLocation.second];
            string newDirection = "L";
            num newDirectionCount = currentDirection == newDirection ? currentDirectionCount + 1 : 1;
            bool addNew = true;
            num count = 0;
            for (State &s : dp[newLocation.first][newLocation.second]) {
                if (s.direction == newDirection && s.directionCount == newDirectionCount) addNew = false;
            }
            if (addNew) dp[newLocation.first][newLocation.second].push_back(State(newHeatLoss, newDirectionCount, newDirection));
        }

        // Up
        if (currentDirection != "D" && !(currentDirection == "U" && currentDirectionCount == 3) && currentLocation.first - 1 >= 0) {
            pair<num, num> newLocation = {currentLocation.first - 1, currentLocation.second};
            num newHeatLoss = currentHeatLoss + grid[newLocation.first][newLocation.second];
            string newDirection = "U";
            num newDirectionCount = currentDirection == newDirection ? currentDirectionCount + 1 : 1;
            bool addNew = true;
            num count = 0;
            for (State &s : dp[newLocation.first][newLocation.second]) {
                if (s.direction == newDirection && s.directionCount == newDirectionCount) addNew = false;
            }
            if (addNew) dp[newLocation.first][newLocation.second].push_back(State(newHeatLoss, newDirectionCount, newDirection));
        }
    }
    return part1;
}

num part2(vector<vector<num>> &grid) {
    num part2 = LONG_LONG_MAX, rows = grid.size(), cols = grid[0].size();
    vector<vector<vector<State>>> dp(rows, vector<vector<State>>(cols, vector<State>(1, State(LONG_LONG_MAX, LONG_LONG_MAX, "N"))));
    dp[0][0].push_back(State(0, 0, "N"));
    num historyLimit = 2;
    while (true) {
        pair<pair<num, num>, State> current = find(dp);
        if (current.first.first == -1 || current.first.second == -1) break;
        pair<num, num> currentLocation = current.first;
        State currentState = current.second;
        num currentHeatLoss = currentState.heatLoss;
        num currentDirectionCount = currentState.directionCount;
        string currentDirection = currentState.direction;
        if (currentLocation.first == rows - 1 && currentLocation.second == cols - 1 && currentDirectionCount >= 4) {
            part2 = min(part2, currentHeatLoss);
            continue;
        }
        if (currentHeatLoss >= part2) continue;

        // Right
        if (currentDirection != "L" && !(currentDirection == "R" && currentDirectionCount == 10) && currentLocation.second + 1 < cols) {
            if (currentDirection == "N" || currentDirection == "R" || (currentDirection != "R" && currentDirectionCount >= 4)) {
                pair<num, num> newLocation = {currentLocation.first, currentLocation.second + 1};
                num newHeatLoss = currentHeatLoss + grid[newLocation.first][newLocation.second];
                string newDirection = "R";
                num newDirectionCount = currentDirection == newDirection ? currentDirectionCount + 1 : 1;
                bool addNew = true;
                num count = 0;
                for (State &s : dp[newLocation.first][newLocation.second]) {
                    if (s.direction == newDirection && s.directionCount == newDirectionCount) addNew = false;
                }
                if (addNew) dp[newLocation.first][newLocation.second].push_back(State(newHeatLoss, newDirectionCount, newDirection));
            }
        }

        // Down
        if (currentDirection != "U" && !(currentDirection == "D" && currentDirectionCount == 10) && currentLocation.first + 1 < rows) {
            if (currentDirection == "N" || currentDirection == "D" || (currentDirection != "D" && currentDirectionCount >= 4)) {
                pair<num, num> newLocation = {currentLocation.first + 1, currentLocation.second};
                num newHeatLoss = currentHeatLoss + grid[newLocation.first][newLocation.second];
                string newDirection = "D";
                num newDirectionCount = currentDirection == newDirection ? currentDirectionCount + 1 : 1;
                bool addNew = true;
                num count = 0;
                for (State &s : dp[newLocation.first][newLocation.second]) {
                    if (s.direction == newDirection && s.directionCount == newDirectionCount) addNew = false;
                }
                if (addNew) dp[newLocation.first][newLocation.second].push_back(State(newHeatLoss, newDirectionCount, newDirection));
            }
        }

        // Left
        if (currentDirection != "R" && !(currentDirection == "L" && currentDirectionCount == 10) && currentLocation.second - 1 >= 0) {
            if (currentDirection == "N" || currentDirection == "L" || (currentDirection != "L" && currentDirectionCount >= 4)) {
                pair<num, num> newLocation = {currentLocation.first, currentLocation.second - 1};
                num newHeatLoss = currentHeatLoss + grid[newLocation.first][newLocation.second];
                string newDirection = "L";
                num newDirectionCount = currentDirection == newDirection ? currentDirectionCount + 1 : 1;
                bool addNew = true;
                num count = 0;
                for (State &s : dp[newLocation.first][newLocation.second]) {
                    if (s.direction == newDirection && s.directionCount == newDirectionCount) addNew = false;
                }
                if (addNew) dp[newLocation.first][newLocation.second].push_back(State(newHeatLoss, newDirectionCount, newDirection));
            }
        }

        // Up
        if (currentDirection != "D" && !(currentDirection == "U" && currentDirectionCount == 10) && currentLocation.first - 1 >= 0) {
            if (currentDirection == "N" || currentDirection == "U" || (currentDirection != "U" && currentDirectionCount >= 4)) {
                pair<num, num> newLocation = {currentLocation.first - 1, currentLocation.second};
                num newHeatLoss = currentHeatLoss + grid[newLocation.first][newLocation.second];
                string newDirection = "U";
                num newDirectionCount = currentDirection == newDirection ? currentDirectionCount + 1 : 1;
                bool addNew = true;
                num count = 0;
                for (State &s : dp[newLocation.first][newLocation.second]) {
                    if (s.direction == newDirection && s.directionCount == newDirectionCount) addNew = false;
                }
                if (addNew) dp[newLocation.first][newLocation.second].push_back(State(newHeatLoss, newDirectionCount, newDirection));
            }
        }
    }
    return part2;
}

int main() {
    string line;
    vector<vector<num>> grid;
    while (getline(cin, line)) {
        vector<num> row;
        for (char c : line) row.push_back(c - '0');
        grid.push_back(row);
    }
    cout << "Part 1: " << part1(grid) << endl;
    cout << "Part 2: " << part2(grid) << endl;
    return 0;
}
