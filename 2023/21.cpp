#include <bits/stdc++.h>
using namespace std;
using num = long long;

int main() {
    num rows = 0, part1 = 0, part2 = 0;
    string line;
    pair<num, num> startPosition;
    vector<vector<char>> garden;
    while (getline(cin, line)) {
        vector<char> row;
        for (num col = 0; col < line.length(); ++col) {
            if (line[col] == 'S') {
                row.push_back('.');
                startPosition = {rows, col};
            } else {
                row.push_back(line[col]);
            }
        }
        garden.push_back(row);
        ++rows;
    }
    num cols = garden[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    visited[startPosition.first][startPosition.second] = true;
    vector<pair<num, num>> sides = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    queue<pair<pair<num, num>, num>> q;
    q.push({startPosition, 0});
    num stepsLimit = 64;
    while (!q.empty()) {
        pair<pair<num, num>, num> current = q.front();
        q.pop();
        if (current.second <= stepsLimit && current.second % 2 == stepsLimit % 2) ++part1;
        if (current.second > stepsLimit) continue;
        pair<num, num> position = current.first;
        for (pair<num, num> &side : sides) {
            pair<num, num> next = {position.first + side.first, position.second + side.second};
            if (next.first >= 0 && next.first < rows && next.second >= 0 && next.second < cols && !visited[next.first][next.second] && garden[next.first][next.second] == '.') {
                q.push({next, current.second + 1});
                visited[next.first][next.second] = true;
            }
        }
    }
    cout << "Part 1: " << part1 << endl;
    return 0;
}
