#include <bits/stdc++.h>
using namespace std;
using num = long long;
using coord = pair<num, num>;
vector<coord> dirs = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

num adj(vector<string> &grid, num row, num col) {
    num r = 0;
    for (coord dir : dirs) {
        coord c = {row + dir.first, col + dir.second};
        if (c.first >= 0 && c.first < grid.size() && c.second >= 0 && c.second < grid[0].length() && grid[c.first][c.second] == '@') ++r;
    }
    return r;
}

int main() {
    num part1 = 0, part2 = 0;
    string line;
    vector<string> grid;
    while (getline(cin, line)) grid.push_back(line);
    for (num row = 0; row < grid.size(); ++row) {
        for (num col = 0; col < grid[0].length(); ++col) {
            if (grid[row][col] == '@' && adj(grid, row, col) < 4) ++part1;
        }
    }
    while (true) {
        bool changed = false;
        for (num row = 0; row < grid.size(); ++row) {
            for (num col = 0; col < grid[0].length(); ++col) {
                if (grid[row][col] == '@' && adj(grid, row, col) < 4) {
                    grid[row][col] = '.';
                    changed = true;
                    ++part2;
                }
            }
        }
        if (!changed) break;
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
