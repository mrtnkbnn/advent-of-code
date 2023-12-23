#include <bits/stdc++.h>
using namespace std;
using num = long long;

vector<pair<num, num>> sides = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
map<char, pair<num, num>> slopes = {{'>', {0, 1}}, {'<', {0, -1}}, {'^', {-1, 0}}, {'v', {1, 0}}};

num path(pair<num, num> position, num steps, vector<vector<char>> &grid, vector<vector<bool>> visited, bool hasSlopes) {
    visited[position.first][position.second] = true;
    num rows = grid.size(), cols = grid[0].size();
    if (position.first == rows - 2 && position.second == cols - 2) return steps + 1;
    if (grid[position.first][position.second] == '.' || !hasSlopes) {
        vector<num> paths = {-1};
        for (pair<num, num> side : sides) {
            pair<num, num> nextPosition = {position.first + side.first, position.second + side.second};
            if (nextPosition.first >= 0 && nextPosition.first < rows && nextPosition.second >= 0 && nextPosition.second < cols && !visited[nextPosition.first][nextPosition.second] && grid[nextPosition.first][nextPosition.second] != '#') paths.push_back(path(nextPosition, steps + 1, grid, visited, hasSlopes));
        }
        return *max_element(paths.begin(), paths.end());
    } else {
        pair<num, num> slope = slopes[grid[position.first][position.second]];
        pair<num, num> nextPosition = {position.first + slope.first, position.second + slope.second};
        if (nextPosition.first >= 0 && nextPosition.first < rows && nextPosition.second >= 0 && nextPosition.second < cols && !visited[nextPosition.first][nextPosition.second] && grid[nextPosition.first][nextPosition.second] != '#') return path(nextPosition, steps + 1, grid, visited, hasSlopes);
        else return -1;
    }
    return -1;
}

int main() {
    string line;
    vector<vector<char>> grid;
    while (getline(cin, line)) {
        vector<char> row;
        for (char c : line) row.push_back(c);
        grid.push_back(row);
    }
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
    cout << "Part 1: " << path({0, 1}, 0, grid, visited, true) << endl;
    cout << "Part 2: " << path({0, 1}, 0, grid, visited, false) << endl;
    return 0;
}
