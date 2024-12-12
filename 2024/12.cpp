#include <bits/stdc++.h>
using namespace std;
using num = long long;
using coord = pair<num, num>;
const vector<coord> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

num sides(vector<pair<coord, coord>> &perimeters) {
    sort(perimeters.begin(), perimeters.end());
    vector<vector<pair<coord, coord>>> groups;
    for (auto &perimeter : perimeters) {
        coord cur = perimeter.first;
        coord dir = perimeter.second;
        bool matches = false;
        for (auto &group : groups) {
            for (auto next : group) {
                coord nextCur = next.first;
                coord nextDir = next.second;
                if (nextDir == dir && abs(nextCur.first - cur.first) < 2 && abs(nextCur.second - cur.second) < 2 && (nextCur.first == cur.first || nextCur.second == cur.second)) {
                    matches = true;
                    break;
                }
            }
            if (matches) {
                group.push_back(perimeter);
                break;
            }
        }
        if (!matches) {
            groups.push_back({perimeter});
        }
    }
    return groups.size();
}

int main() {
    num part1 = 0, part2 = 0, rows = 0, cols;
    string line;
    vector<string> grid;
    while (getline(cin, line)) {
        grid.push_back(line);
        ++rows;
    }
    cols = grid[0].length();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    for (num row = 0; row < rows; ++row) {
        for (num col = 0; col < cols; ++col) {
            if (visited[row][col]) continue;
            num area = 0, perimeter = 0;
            vector<pair<coord, coord>> perimeters;
            char plant = grid[row][col];
            visited[row][col] = true;
            queue<coord> q;
            q.push({row, col});
            while (!q.empty()) {
                coord cur = q.front();
                q.pop();
                ++area;
                for (coord dir : dirs) {
                    num nextRow = cur.first + dir.first;
                    num nextCol = cur.second + dir.second;
                    if (nextRow < 0 || nextRow >= rows || nextCol < 0 || nextCol >= cols) {
                        ++perimeter;
                        perimeters.push_back({cur, dir});
                    } else if (grid[nextRow][nextCol] != plant) {
                        ++perimeter;
                        perimeters.push_back({cur, dir});
                    } else if (!visited[nextRow][nextCol]) {
                        q.push({nextRow, nextCol});
                        visited[nextRow][nextCol] = true;
                    }
                }
            }
            part1 += area * perimeter;
            part2 += area * sides(perimeters);
        }
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
