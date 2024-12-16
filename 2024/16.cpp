#include <bits/stdc++.h>
using namespace std;
using num = long long;
using coord = pair<num, num>;
const vector<coord> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

vector<vector<num>> dijkstra(coord start, coord end, coord startDir, vector<string> &grid) {
    num rows = grid.size(), cols = grid[0].length();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<vector<num>> distance(rows, vector<num>(cols, LONG_LONG_MAX));
    vector<vector<coord>> dir(rows, vector<coord>(cols, {0, 0}));
    priority_queue<pair<num, coord>, vector<pair<num, coord>>, greater<pair<num, coord>>> q;
    q.push({0, start});
    distance[start.first][start.second] = 0;
    dir[start.first][start.second] = startDir;
    while (!q.empty()) {
        coord cur = q.top().second;
        q.pop();
        if (visited[cur.first][cur.second]) continue;
        visited[cur.first][cur.second] = true;
        for (coord delta : dirs) {
            coord curDir = dir[cur.first][cur.second];
            if ((curDir.first == delta.first && curDir.second != delta.second) || (curDir.second == delta.second && curDir.first != delta.first)) continue;
            coord next = {cur.first + delta.first, cur.second + delta.second};
            if (grid[next.first][next.second] == '#') continue;
            num rotate = delta == curDir ? 0 : 1000;
            if (distance[next.first][next.second] > distance[cur.first][cur.second] + 1 + rotate) {
                distance[next.first][next.second] = distance[cur.first][cur.second] + 1 + rotate;
                dir[next.first][next.second] = delta;
                if (next != end) q.push({distance[cur.first][cur.second] + 1 + rotate, next});
            }
        }
    }
    return distance;
}

int main() {
    num part1 = 0, part2 = 0;
    string line;
    vector<string> grid;
    while (getline(cin, line)) grid.push_back(line);
    num rows = grid.size(), cols = grid[0].length();
    auto distance1 = dijkstra({rows - 2, 1}, {1, cols - 2}, {0, 1}, grid);
    auto distance2 = dijkstra({1, cols - 2}, {rows - 2, 1}, {0, -1}, grid);
    auto distance3 = dijkstra({1, cols - 2}, {rows - 2, 1}, {1, 0}, grid);
    for (num row = 0; row < rows; ++row) {
        for (num col = 0; col < cols; ++col) {
            if (distance1[row][col] + distance2[row][col] == distance1[1][cols - 2]) ++part2;
            else if (distance1[row][col] + distance3[row][col] == distance1[1][cols - 2]) ++part2;
        }
    }
    cout << "Part 1: " << distance1[1][cols - 2] << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
