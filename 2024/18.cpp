#include <bits/stdc++.h>
using namespace std;
using num = long long;
using coord = pair<num, num>;
const vector<coord> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

num bfs(vector<vector<char>> &grid, num n) {
    vector<vector<num>> distance(n, vector<num>(n, -1));
    queue<coord> q;
    q.push({0, 0});
    distance[0][0] = 0;
    while (!q.empty()) {
        coord cur = q.front();
        q.pop();
        for (coord dir : dirs) {
            coord next = {cur.first + dir.first, cur.second + dir.second};
            if (next.first < 0 || next.first >= n || next.second < 0 || next.second >= n) continue;
            if (grid[next.first][next.second] == '#') continue;
            if (distance[next.first][next.second] == -1) {
                q.push(next);
                distance[next.first][next.second] = distance[cur.first][cur.second] + 1;
            }
        }
    }
    return distance[n - 1][n - 1];
}

int main() {
    num part1 = 0, part2 = 0, n = 71, m = 1024;
    string line;
    vector<coord> kbs;
    while (getline(cin, line)) {
        num col = stoll(line.substr(0, line.find(",")));
        num row = stoll(line.substr(line.find(",") + 1));
        kbs.push_back({row, col});
    }
    vector<vector<char>> grid(n, vector<char>(n, '.'));
    for (num i = 0; i < m; ++i) {
        grid[kbs[i].first][kbs[i].second] = '#';
    }
    cout << "Part 1: " << bfs(grid, n) << endl;
    for (num i = m; i < kbs.size(); ++i) {
        grid[kbs[i].first][kbs[i].second] = '#';
        if (bfs(grid, n) == -1) {
            cout << "Part 2: " << kbs[i].second << "," << kbs[i].first << endl;
            break;
        }
    }
    return 0;
}
