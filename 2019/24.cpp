#include <bits/stdc++.h>
using namespace std;
using num = long long;
const vector<pair<num, num>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void simulate1(vector<vector<bool>> &grid) {
    vector<vector<bool>> newGrid(5, vector<bool>(5, false));
    for (num row = 0; row < 5; ++row) {
        for (num col = 0; col < 5; ++col) {
            num adj = 0;
            for (auto dir : dirs) {
                num nextRow = row + dir.first;
                num nextCol = col + dir.second;
                if (nextRow < 0 || nextRow > 4 || nextCol < 0 || nextCol > 4) continue;
                if (grid[nextRow][nextCol]) ++adj;
            }
            if (grid[row][col] && adj != 1) newGrid[row][col] = false;
            else if (!grid[row][col] && (adj == 1 || adj == 2)) newGrid[row][col] = true;
            else newGrid[row][col] = grid[row][col];
        }
    }
    grid = newGrid;
}

num part1(vector<vector<bool>> grid) {
    set<vector<vector<bool>>> mem = {grid};
    while (true) {
        simulate1(grid);
        num prev = mem.size();
        mem.insert(grid);
        if (prev == mem.size()) break;
    }
    num ans = 0;
    num pointer = 0;
    for (num row = 0; row < 5; ++row) {
        for (num col = 0; col < 5; ++col) {
            if (grid[row][col]) ans += 1 << pointer;
            ++pointer;
        }
    }
    return ans;
}

void simulate2(map<num, vector<vector<bool>>> &levels) {
    map<num, vector<vector<bool>>> newLevels;
    num curMin = LONG_LONG_MAX, curMax = LONG_LONG_MIN;
    for (auto [depth, grid] : levels) {
        curMin = min(curMin, depth);
        curMax = max(curMax, depth);
    }
    levels[curMin - 1] = vector<vector<bool>>(5, vector<bool>(5, false));
    levels[curMax + 1] = vector<vector<bool>>(5, vector<bool>(5, false));
    for (num i = curMin -1; i <= curMax + 1; ++i) newLevels[i] = vector<vector<bool>>(5, vector<bool>(5, false));
    for (auto [depth, grid] : levels) {
        for (num row = 0; row < 5; ++row) {
            for (num col = 0; col < 5; ++col) {
                if (row == 2 && col == 2) continue;
                num adj = 0;
                for (auto dir : dirs) {
                    num nextRow = row + dir.first;
                    num nextCol = col + dir.second;
                    if (nextRow == 2 && nextCol == 2) {
                        num nextDepth = depth + 1;
                        if (nextDepth > curMax + 1) continue;
                        if (row == 1) {
                            for (num c = 0; c < 5; ++c) {
                                if (levels[nextDepth][0][c]) ++adj;
                            }
                        } else if (row == 3) {
                            for (num c = 0; c < 5; ++c) {
                                if (levels[nextDepth][4][c]) ++adj;
                            }
                        } else if (col == 1) {
                            for (num r = 0; r < 5; ++r) {
                                if (levels[nextDepth][r][0]) ++adj;
                            }
                        } else if (col == 3) {
                            for (num r = 0; r < 5; ++r) {
                                if (levels[nextDepth][r][4]) ++adj;
                            }
                        }
                    } else if (nextRow < 0) {
                        num nextDepth = depth - 1;
                        if (nextDepth < curMin - 1) continue;
                        if (levels[nextDepth][1][2]) ++adj;
                    } else if (nextRow > 4) {
                        num nextDepth = depth - 1;
                        if (nextDepth < curMin - 1) continue;
                        if (levels[nextDepth][3][2]) ++adj;
                    } else if (nextCol < 0) {
                        num nextDepth = depth - 1;
                        if (nextDepth < curMin - 1) continue;
                        if (levels[nextDepth][2][1]) ++adj;
                    } else if (nextCol > 4) {
                        num nextDepth = depth - 1;
                        if (nextDepth < curMin - 1) continue;
                        if (levels[nextDepth][2][3]) ++adj;
                    } else {
                        if (grid[nextRow][nextCol]) ++adj;
                    }
                }
                if (grid[row][col] && adj != 1) newLevels[depth][row][col] = false;
                else if (!grid[row][col] && (adj == 1 || adj == 2)) newLevels[depth][row][col] = true;
                else newLevels[depth][row][col] = grid[row][col];
            }
        }
    }
    levels = newLevels;
}

num part2(vector<vector<bool>> grid) {
    map<num, vector<vector<bool>>> levels;
    levels[0] = grid;
    for (num i = 0; i < 200; ++i) simulate2(levels);
    num ans = 0;
    for (auto [depth, grid] : levels) {
        for (num row = 0; row < 5; ++row) {
            for (num col = 0; col < 5; ++col) {
                if (grid[row][col]) ++ans;
            }
        }
    }
    return ans;
}

int main() {
    num row = 0;
    vector<vector<bool>> grid(5, vector<bool>(5, false));
    string line;
    while (getline(cin, line)) {
        for (num col = 0; col < 5; ++col) {
            if (line[col] == '#') grid[row][col] = true;
        }
        ++row;
    }
    cout << "Part 1: " << part1(grid) << endl;
    cout << "Part 2: " << part2(grid) << endl;
    return 0;
}
