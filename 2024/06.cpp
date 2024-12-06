#include <bits/stdc++.h>
using namespace std;
using num = long long;

bool loops(vector<vector<char>> map, pair<num, num> &start, pair<num, num> &pos, num rows, num cols) {
    map[pos.first][pos.second] = '#';
    set<pair<num, num>> seen;
    set<tuple<num, num, num>> mem;
    vector<pair<num, num>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    num dir = 0;
    queue<pair<num, num>> q;
    q.push(start);
    while (!q.empty()) {
        pair<num, num> cur = q.front();
        q.pop();
        if (mem.find({cur.first, cur.second, dir}) != mem.end()) return true;
        seen.insert(cur);
        mem.insert({cur.first, cur.second, dir});
        pair<num, num> next = {cur.first + dirs[dir].first, cur.second + dirs[dir].second};
        if (next.first < 0 || next.second < 0 || next.first >= rows || next.second >= cols) {
            return false;
        } else if (map[next.first][next.second] == '#') {
            ++dir;
            if (dir == 4) dir = 0;
            q.push(cur);
        } else {
            q.push(next);
        }
    }
    return false;
}

int main() {
    num part1 = 0, part2 = 0, r = 0;
    string line;
    vector<vector<char>> map;
    pair<num, num> start;
    while (getline(cin, line)) {
        vector<char> row;
        for (num i = 0; i < line.length(); ++i) {
            row.push_back(line[i]);
            if (line[i] != '.' && line[i] != '#') start = {r, i};
        }
        map.push_back(row);
        ++r;
    }
    num rows = map.size();
    num cols = map[0].size();
    set<pair<num, num>> seen;
    vector<pair<num, num>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    num dir = 0;
    queue<pair<num, num>> q;
    q.push(start);
    while (!q.empty()) {
        pair<num, num> cur = q.front();
        q.pop();
        seen.insert(cur);
        pair<num, num> next = {cur.first + dirs[dir].first, cur.second + dirs[dir].second};
        if (next.first < 0 || next.second < 0 || next.first >= rows || next.second >= cols) {
            break;
        } else if (map[next.first][next.second] == '#') {
            ++dir;
            if (dir == 4) dir = 0;
            q.push(cur);
        } else {
            q.push(next);
        }
    }
    part1 = seen.size();
    for (auto pos : seen) {
        if (loops(map, start, pos, rows, cols)) ++part2;
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
