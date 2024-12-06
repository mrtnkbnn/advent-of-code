#include <bits/stdc++.h>
using namespace std;
using num = long long;
using coord = pair<num, num>;
vector<coord> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

bool loops(vector<vector<char>> grid, set<tuple<num, num, num>> mem, coord cur, num dir, coord next, num rows, num cols) {
    grid[next.first][next.second] = '#';
    mem.erase({cur.first, cur.second, dir});
    while (true) {
        if (mem.find({cur.first, cur.second, dir}) != mem.end()) return true;
        mem.insert({cur.first, cur.second, dir});
        coord next = {cur.first + dirs[dir].first, cur.second + dirs[dir].second};
        if (next.first < 0 || next.second < 0 || next.first >= rows || next.second >= cols) return false;
        else if (grid[next.first][next.second] == '#') {
            ++dir;
            if (dir == 4) dir = 0;
        } else {
            cur = next;
        }
    }
    return false;
}

int main() {
    num part2 = 0, r = 0;
    string line;
    vector<vector<char>> grid;
    coord start;
    while (getline(cin, line)) {
        vector<char> row;
        for (num i = 0; i < line.length(); ++i) {
            row.push_back(line[i]);
            if (line[i] != '.' && line[i] != '#') start = {r, i};
        }
        grid.push_back(row);
        ++r;
    }
    num rows = grid.size();
    num cols = grid[0].size();
    set<coord> seen;
    set<tuple<num, num, num>> mem;
    num dir = 0;
    coord cur = start;
    while (true) {
        seen.insert(cur);
        coord next = {cur.first + dirs[dir].first, cur.second + dirs[dir].second};
        if (next.first < 0 || next.second < 0 || next.first >= rows || next.second >= cols) break;
        else if (grid[next.first][next.second] == '#') {
            ++dir;
            if (dir == 4) dir = 0;
        } else {
            if (seen.find(next) == seen.end() && loops(grid, mem, cur, dir, next, rows, cols)) ++part2;
            cur = next;
        }
    }
    cout << "Part 1: " << seen.size() << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
