#include <bits/stdc++.h>
using namespace std;
using num = long long;
using coord = pair<num, num>;

num part1 = 0;

num paths(vector<string> &grid, map<coord, num> &dp, coord pos) {
    if (dp.find(pos) != dp.end()) {
        return dp[pos];
    }
    coord next = {pos.first + 1, pos.second};
    if (next.first == grid.size()) {
        return 1;
    } else if (grid[next.first][next.second] == '.') {
        num res = paths(grid, dp, next);
        dp[next] = res;
        return res;
    } else {
        ++part1;
        coord left = {next.first, pos.second - 1};
        coord right = {next.first, pos.second + 1};
        return paths(grid, dp, left) + paths(grid, dp, right);
    }
}

int main() {
    num part2 = 0;
    string line;
    vector<string> grid;
    while (getline(cin, line)) grid.push_back(line);
    coord start;
    for (num col = 0; col < grid[0].length(); ++col) {
        if (grid[0][col] == 'S') {
            start = {0, col};
            break;
        }
    }
    map<coord, num> dp;
    part2 = paths(grid, dp, start);
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
