#include <bits/stdc++.h>
using namespace std;
using num = long long;
const vector<pair<num, num>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

num dfs(num row, num col, num rows, num cols, vector<vector<num>> &grid, vector<vector<bool>> &visited) {
    if (visited[row][col]) return 0;
    visited[row][col] = true;
    if (grid[row][col] == 9) return 1;
    num ans = 0;
    for (auto dir : dirs) {
        num newRow = row + dir.first;
        num newCol = col + dir.second;
        if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && grid[row][col] + 1 == grid[newRow][newCol]) {
            ans += dfs(newRow, newCol, rows, cols, grid, visited);
        }
    }
    return ans;
}

num dfs2(num row, num col, num rows, num cols, vector<vector<num>> &grid, vector<vector<int>> &dp) {
    if (dp[row][col] != -1) return dp[row][col];
    if (grid[row][col] == 9) return 1;
    num ans = 0;
    for (auto dir : dirs) {
        num newRow = row + dir.first;
        num newCol = col + dir.second;
        if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && grid[row][col] + 1 == grid[newRow][newCol]) {
            ans += dfs2(newRow, newCol, rows, cols, grid, dp);
        }
    }
    dp[row][col] = ans;
    return ans;
}

int main() {
    num part1 = 0, part2 = 0;
    string line;
    vector<vector<num>> grid;
    while (getline(cin, line)) {
        vector<num> row;
        for (char c : line) row.push_back(c - '0');
        grid.push_back(row);
    }
    num rows = grid.size();
    num cols = grid[0].size();
    for (num row = 0; row < rows; ++row) {
        for (num col = 0; col < cols; ++col) {
            if (grid[row][col] == 0) {
                vector<vector<bool>> visited = vector<vector<bool>>(rows, vector<bool>(cols, false));
                vector<vector<int>> dp = vector<vector<int>>(rows, vector<int>(cols, -1));
                part1 += dfs(row, col, rows, cols, grid, visited);
                part2 += dfs2(row, col, rows, cols, grid, dp);
            }
        }
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
