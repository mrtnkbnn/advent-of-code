#include <bits/stdc++.h>
using namespace std;

enum block { air, rock, sand };

bool dropSandUntilAbyss(int x, int y, int Y, vector<vector<block>>& cave) {
    if (y >= Y) {
        return false;
    }
    if (cave[y + 1][x] == air) {
        return dropSandUntilAbyss(x, y + 1, Y, cave);
    }
    if (cave[y + 1][x - 1] == air) {
        return dropSandUntilAbyss(x - 1, y + 1, Y, cave);
    }
    if (cave[y + 1][x + 1] == air) {
        return dropSandUntilAbyss(x + 1, y + 1, Y, cave);
    }
    cave[y][x] = sand;
    return true;
}

bool dropSandUntilBlocked(int x, int y, vector<vector<block>>& cave) {
    if (cave[y][x] == sand) {
        return false;
    }
    if (cave[y + 1][x] == air) {
        return dropSandUntilBlocked(x, y + 1,cave);
    }
    if (cave[y + 1][x - 1] == air) {
        return dropSandUntilBlocked(x - 1, y + 1, cave);
    }
    if (cave[y + 1][x + 1] == air) {
        return dropSandUntilBlocked(x + 1, y + 1, cave);
    }
    cave[y][x] = sand;
    return true;
}

int main() {
    string line;
    vector<vector<pair<int, int>>> lines;
    int X = INT_MIN, Y = INT_MIN;
    while (getline(cin, line)) {
        stringstream ss;
        replace(line.begin(), line.end(), ',', ' ');
        replace(line.begin(), line.end(), '-', ' ');
        replace(line.begin(), line.end(), '>', ' ');
        ss << line;
        int x, y;
        vector<pair<int, int>> line;
        while (ss >> x >> y) {
            line.push_back({x, y});
            X = max(X, x);
            Y = max(Y, y);
        }
        lines.push_back(line);
    }
    vector<vector<block>> cave(Y + 3, vector<block>(X * 2, air));
    for (vector<pair<int, int>> line : lines) {
        for (int i = 0; i < line.size() - 1; ++i) {
            pair<int, int> p1 = line[i];
            pair<int, int> p2 = line[i + 1];
            if (p1.first == p2.first) {
                for (int y = min(p1.second, p2.second); y <= max(p1.second, p2.second); ++y) {
                    cave[y][p1.first] = rock;
                }
            } else if (p1.second == p2.second)  {
                for (int x = min(p1.first, p2.first); x <= max(p1.first, p2.first); ++x) {
                    cave[p1.second][x] = rock;
                }
            }
        }
    }
    for (int x = 0; x < X * 2; ++x) {
        cave[Y + 2][x] = rock;
    }
    int part1 = 0;
    while (dropSandUntilAbyss(500, 0, Y, cave)) {
        ++part1;
    }
    int part2 = part1;
    while (dropSandUntilBlocked(500, 0, cave)) {
        ++part2;
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
