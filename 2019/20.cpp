#include <bits/stdc++.h>
using namespace std;
using num = long long;
using coord = pair<num, num>;
const vector<coord> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
const vector<pair<coord, coord>> portalDirs = {{{1, 0}, {2, 0}}, {{-2, 0}, {-1, 0}}, {{0, -2}, {0, -1}}, {{0, 1}, {0, 2}}};

num part1(coord start, coord end, vector<string> &grid, map<coord, coord> &portals) {
    vector<vector<num>> distance(grid.size(), vector<num>(grid[0].length(), -1));
    queue<coord> q;
    q.push(start);
    distance[start.first][start.second] = 0;
    while (!q.empty()) {
        coord cur = q.front();
        q.pop();
        if (portals.find(cur) != portals.end()) {
            coord next = portals[cur];
            if (distance[next.first][next.second] == -1) {
                q.push(next);
                distance[next.first][next.second] = distance[cur.first][cur.second] + 1;
            }
        }
        for (coord dir : dirs) {
            coord next = {cur.first + dir.first, cur.second + dir.second};
            if (grid[next.first][next.second] == '.' && distance[next.first][next.second] == -1) {
                q.push(next);
                distance[next.first][next.second] = distance[cur.first][cur.second] + 1;
            }
        }
    }
    return distance[end.first][end.second];
}

num part2(coord start, coord end, vector<string> &grid, map<coord, coord> &portals, map<coord, bool> &outer) {
    vector<vector<vector<num>>> distance(grid.size(), vector<vector<num>>(grid[0].length(), vector<num>(200, -1)));
    queue<pair<coord, num>> q;
    q.push({start, 0});
    distance[start.first][start.second][0] = 0;
    while (!q.empty()) {
        auto front = q.front();
        q.pop();
        coord cur = front.first;
        num curLevel = front.second;
        if (portals.find(cur) != portals.end()) {
            coord next = portals[cur];
            bool isOuter = outer[cur];
            if (!isOuter || !curLevel == 0) {
                num nextLevel = outer[cur] ? curLevel - 1 : curLevel + 1;
                if (distance[next.first][next.second][nextLevel] == -1) {
                    q.push({next, nextLevel});
                    distance[next.first][next.second][nextLevel] = distance[cur.first][cur.second][curLevel] + 1;
                }
            }
        }
        for (coord dir : dirs) {
            coord next = {cur.first + dir.first, cur.second + dir.second};
            if (grid[next.first][next.second] == '.' && distance[next.first][next.second][curLevel] == -1) {
                q.push({next, curLevel});
                distance[next.first][next.second][curLevel] = distance[cur.first][cur.second][curLevel] + 1;
                if (next == end && curLevel == 0) return distance[end.first][end.second][0];
            }
        }
    }
    return distance[end.first][end.second][0];
}

int main() {
    string line;
    vector<string> grid;
    while (getline(cin, line)) grid.push_back(line);
    coord start, end;
    map<string, vector<coord>> portalLocations;
    map<coord, bool> outer;
    num rows = grid.size(), cols = grid[0].length();
    for (num row = 0; row < rows; ++row) {
        for (num col = 0; col < cols; ++col) {
            if (grid[row][col] == '.') {
                for (auto p : portalDirs) {
                    coord first = {row + p.first.first, col + p.first.second};
                    coord second = {row + p.second.first, col + p.second.second};
                    if (first.first < 0 || first.first >= rows || first.second < 0 || first.second >= cols) continue;
                    if (second.first < 0 || second.first >= rows || second.second < 0 || second.second >= cols) continue;
                    char a = grid[first.first][first.second];
                    char b = grid[second.first][second.second];
                    if (a >= 'A' && a <= 'Z' && b >= 'A' && b <= 'Z') {
                        string portal = "";
                        portal += a;
                        portal += b;
                        if (portal == "AA") start = {row, col};
                        else if (portal == "ZZ") end = {row, col};
                        else {
                            portalLocations[portal].push_back({row, col});
                            if (row - 2 == 0 || row + 3 == rows || col - 2 == 0 || col + 3 == cols) {
                                outer[{row, col}] = true;
                            }
                        }
                    }
                }
            }
        }
    }
    map<coord, coord> portals;
    for (auto [key, val] : portalLocations) {
        portals[val[0]] = val[1];
        portals[val[1]] = val[0];
    }
    cout << "Part 1: " << part1(start, end, grid, portals) << endl;
    cout << "Part 2: " << part2(start, end, grid, portals, outer) << endl;
    return 0;
}
