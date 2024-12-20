#include <bits/stdc++.h>
using namespace std;
using num = long long;
using coord = pair<num, num>;
const vector<coord> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int main() {
    num part1 = 0, part2 = 0, rows = 0;
    coord start, end;
    string line;
    vector<string> grid;
    while (getline(cin, line)) {
        grid.push_back(line);
        for (num col = 0; col < line.length(); ++col) {
            if (line[col] == 'S') start = {rows, col};
            else if (line[col] == 'E') end = {rows, col};
        }
        ++rows;
    }
    vector<vector<num>> distance(rows, vector<num>(grid[0].size(), -1));
    vector<coord> path;
    queue<coord> q;
    q.push(start);
    distance[start.first][start.second] = 0;
    while (!q.empty()) {
        coord cur = q.front();
        q.pop();
        path.push_back(cur);
        for (coord dir : dirs) {
            coord next = {cur.first + dir.first, cur.second + dir.second};
            if (grid[next.first][next.second] == '#') continue;
            if (distance[next.first][next.second] == -1) {
                q.push(next);
                distance[next.first][next.second] = distance[cur.first][cur.second] + 1;
            }
        }
    }
    num initial = distance[end.first][end.second];
    for (num i = 0; i < path.size(); ++i) {
        for (num j = i + 1; j < path.size(); ++j) {
            num cheat = abs(path[i].first - path[j].first) + abs(path[i].second - path[j].second);
            num cheated = distance[path[i].first][path[i].second] + cheat + (distance[end.first][end.second] - distance[path[j].first][path[j].second]);
            if (cheat == 2 && distance[end.first][end.second] - cheated >= 100) ++part1;
            if (cheat <= 20 && distance[end.first][end.second] - cheated >= 100) ++part2;
        }
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
