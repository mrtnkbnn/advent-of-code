#include <bits/stdc++.h>
using namespace std;
using num = long long;
using coord = pair<num, num>;
const vector<coord> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int main() {
    num part1 = LONG_LONG_MAX, part2 = 0;
    string line;
    vector<string> grid;
    while (getline(cin, line)) grid.push_back(line);
    num rows = grid.size(), cols = grid[0].length();
    priority_queue<tuple<num, coord, coord, set<coord>>, vector<tuple<num, coord, coord, set<coord>>>, greater<tuple<num, coord, coord, set<coord>>>> q;
    vector<vector<map<coord, num>>> distance(rows, vector<map<coord, num>>(cols, {{{1, 0}, LONG_LONG_MAX}, {{-1, 0}, LONG_LONG_MAX}, {{0, 1}, LONG_LONG_MAX}, {{0, -1}, LONG_LONG_MAX}}));
    vector<vector<map<coord, set<coord>>>> path(rows, vector<map<coord, set<coord>>>(cols, {{{1, 0}, {}}, {{-1, 0}, {}}, {{0, 1}, {}}, {{0, -1}, {}}}));
    q.push({0, {rows - 2, 1}, {0, 1}, {{rows - 2, 1}}});
    distance[rows - 2][1][{0, 1}] = 0;
    while (!q.empty()) {
        auto top = q.top();
        q.pop();
        num curDist = get<0>(top);
        coord cur = get<1>(top);
        coord curDir = get<2>(top);
        set<coord> curPath = get<3>(top);
        for (coord dir : dirs) {
            if ((curDir.first == dir.first && curDir.second != dir.second) || (curDir.second == dir.second && curDir.first != dir.first)) continue;
            num rotate = dir == curDir ? 0 : 1000;
            coord nextPos = {cur.first + dir.first, cur.second + dir.second};
            if (grid[nextPos.first][nextPos.second] == '#') continue;
            if (distance[nextPos.first][nextPos.second][dir] > distance[cur.first][cur.second][curDir] + 1 + rotate) {
                distance[nextPos.first][nextPos.second][dir] = distance[cur.first][cur.second][curDir] + 1 + rotate;
                path[nextPos.first][nextPos.second][dir] = path[cur.first][cur.second][curDir];
                path[nextPos.first][nextPos.second][dir].insert(cur);
                path[nextPos.first][nextPos.second][dir].insert(nextPos);
                q.push({distance[nextPos.first][nextPos.second][dir], nextPos, dir, path[nextPos.first][nextPos.second][dir]});
            } else if (distance[nextPos.first][nextPos.second][dir] == distance[cur.first][cur.second][curDir] + 1 + rotate) {
                for (coord p : path[cur.first][cur.second][curDir]) path[nextPos.first][nextPos.second][dir].insert(p);
            }
        }
    }
    for (auto [key, val] : distance[1][cols - 2]) {
        if (val < part1) {
            part1 = val;
            part2 = path[1][cols - 2][key].size();
        }
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
