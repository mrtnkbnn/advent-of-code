#include <bits/stdc++.h>
using namespace std;
using num = long long;
using coord = pair<num, num>;
const vector<coord> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

num shortestPath1 = LONG_LONG_MAX, shortestPath2 = LONG_LONG_MAX;
map<pair<coord, set<char>>, num> dp1;
map<pair<vector<coord>, set<char>>, num> dp2;

map<char, num> bfs(coord start, vector<vector<char>> &grid) {
    num rows = grid.size(), cols = grid[0].size();
    map<char, num> found;
    vector<vector<num>> distance(rows, vector<num>(cols, -1));
    queue<coord> q;
    q.push(start);
    distance[start.first][start.second] = 0;
    while (!q.empty()) {
        coord cur = q.front();
        q.pop();
        for (coord dir : dirs) {
            coord next = {cur.first + dir.first, cur.second + dir.second};
            if (grid[next.first][next.second] == '#') continue;
            if (distance[next.first][next.second] != -1) continue;
            if (grid[next.first][next.second] >= 'A' && grid[next.first][next.second] <= 'Z') continue;
            if (grid[next.first][next.second] >= 'a' && grid[next.first][next.second] <= 'z') {
                found[grid[next.first][next.second]] = distance[cur.first][cur.second] + 1;
            } else {
                q.push(next);
                distance[next.first][next.second] = distance[cur.first][cur.second] + 1;
            }
        }
    }
    return found;
}

void part1(coord start, num steps, set<char> collected, vector<vector<char>> grid, map<char, coord> &keys, map<char, coord> &doors) {
    if (dp1.find({start, collected}) != dp1.end()) {
        if (dp1[{start, collected}] <= steps) return;
    }
    dp1[{start, collected}] = steps;
    if (keys.size() == collected.size()) {
        shortestPath1 = min(shortestPath1, steps);
        return;
    }
    map<char, num> found = bfs(start, grid);
    for (auto [key, val] : found) {
        if(steps + val >= shortestPath1) continue;
        vector<vector<char>> nextGrid = grid;
        nextGrid[keys[key].first][keys[key].second] = '.';
        nextGrid[doors[key - 32].first][doors[key - 32].second] = '.';
        set<char> nextCollected = collected;
        nextCollected.insert(key);
        part1(keys[key], steps + val, nextCollected, nextGrid, keys, doors);
    }
}

void part2(vector<coord> start, num steps, set<char> collected, vector<vector<char>> grid, map<char, coord> &keys, map<char, coord> &doors) {
    if (dp2.find({start, collected}) != dp2.end()) {
        if (dp2[{start, collected}] <= steps) return;
    }
    dp2[{start, collected}] = steps;
    if (keys.size() == collected.size()) {
        shortestPath2 = min(shortestPath2, steps);
        return;
    }
    vector<map<char, num>> founds;
    vector<vector<pair<num, char>>> states(4);
    for (coord pos : start) founds.push_back(bfs(pos, grid));
    for (num i = 0; i < founds.size(); ++i) {
        states[i].push_back({0, '.'});
        for (auto [key, val] : founds[i]) {
            states[i].push_back({val, key});
        }
    }
    for (num i = 0; i < states[0].size(); ++i) {
        for (num j = 0; j < states[1].size(); ++j) {
            for (num k = 0; k < states[2].size(); ++k) {
                for (num l = 0; l < states[3].size(); ++l) {
                    if (i == 0 && j == 0 && k == 0 && l == 0) continue;
                    vector<coord> nextStart = start;
                    vector<vector<char>> nextGrid = grid;
                    set<char> nextCollected = collected;
                    num nextSteps = steps;
                    if (states[0][i].first != 0) {
                        char key = states[0][i].second;
                        nextGrid[keys[key].first][keys[key].second] = '.';
                        nextGrid[doors[key - 32].first][doors[key - 32].second] = '.';
                        nextCollected.insert(key);
                        nextSteps += states[0][i].first;
                        nextStart[0] = keys[key];
                    }
                    if (states[1][j].first != 0) {
                        char key = states[1][j].second;
                        nextGrid[keys[key].first][keys[key].second] = '.';
                        nextGrid[doors[key - 32].first][doors[key - 32].second] = '.';
                        nextCollected.insert(key);
                        nextSteps += states[1][j].first;
                        nextStart[1] = keys[key];
                    }
                    if (states[2][k].first != 0) {
                        char key = states[2][k].second;
                        nextGrid[keys[key].first][keys[key].second] = '.';
                        nextGrid[doors[key - 32].first][doors[key - 32].second] = '.';
                        nextCollected.insert(key);
                        nextSteps += states[2][k].first;
                        nextStart[2] = keys[key];
                    }
                    if (states[3][l].first != 0) {
                        char key = states[3][l].second;
                        nextGrid[keys[key].first][keys[key].second] = '.';
                        nextGrid[doors[key - 32].first][doors[key - 32].second] = '.';
                        nextCollected.insert(key);
                        nextSteps += states[3][l].first;
                        nextStart[3] = keys[key];
                    }
                    part2(nextStart, nextSteps, nextCollected, nextGrid, keys, doors);
                }
            }
        }
    }
}

int main() {
    num rows = 0;
    string line;
    vector<vector<char>> grid;
    coord start;
    map<char, coord> keys, doors;
    while (getline(cin, line)) {
        vector<char> row;
        for (num col = 0; col < line.length(); ++col) {
            if (line[col] == '#') row.push_back('#');
            else if (line[col] == '.') row.push_back('.');
            else if (line[col] == '@') {
                start = {rows, col};
                row.push_back('.');
            } else {
                if (line[col] >= 'a' && line[col] <= 'z') {
                    keys[line[col]] = {rows, col};
                } else if (line[col] >= 'A' && line[col] <= 'Z') {
                    doors[line[col]] = {rows, col};
                }
                row.push_back(line[col]);
            }
        }
        grid.push_back(row);
        ++rows;
    }
    vector<vector<char>> grid2 = grid;
    for (coord dir : dirs) grid2[start.first + dir.first][start.second + dir.second] = '#';
    part1(start, 0, {}, grid, keys, doors);
    part2({{start.first - 1, start.second - 1}, {start.first - 1, start.second + 1}, {start.first + 1, start.second - 1},{start.first + 1, start.second + 1}}, 0, {}, grid2, keys, doors);
    cout << "Part 1: " << shortestPath1 << endl;
    cout << "Part 2: " << shortestPath2 << endl;
    return 0;
}
