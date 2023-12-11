#include <bits/stdc++.h>
using namespace std;
using num = long long;
using pos = pair<num, num>;

bool areConnected(pos pos1, pos pos2, vector<vector<char>> &pipes) {
    map<char, vector<pos>> connects = {
        {'S', {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}},
        {'|', {{1, 0}, {-1, 0}}},
        {'-', {{0, 1}, {0, -1}}},
        {'L', {{-1, 0}, {0, 1}}},
        {'J', {{-1, 0}, {0, -1}}},
        {'7', {{1, 0}, {0, -1}}},
        {'F', {{1, 0}, {0, 1}}},
        {'.', {}}
    };
    bool b1 = false, b2 = false;
    for (pos neighbour : connects[pipes[pos1.first][pos1.second]]) {
        if (pos1.first + neighbour.first == pos2.first && pos1.second + neighbour.second == pos2.second) b1 = true;
    }
    for (pos neighbour : connects[pipes[pos2.first][pos2.second]]) {
        if (pos2.first + neighbour.first == pos1.first && pos2.second + neighbour.second == pos1.second) b2 = true;
    }
    return b1 && b2;
}

bool isInside(pos position, num rows, num cols, vector<vector<bool>> &visited, vector<vector<char>> &pipes) {
    num count = 0;
    for (num i = position.second - 1; i >= 0; --i) {
        char pipe = pipes[position.first][i];
        if (visited[position.first][i] && (pipe == '|' || pipe == 'L' || pipe == 'J' || pipe == 'S')) ++count;
    }
    return count % 2 != 0;
}

int main() {
    vector<vector<char>> pipes;
    pos startingPosition;
    string line;
    num rows = 0, cols = 0, loopSize = 0, inside = 0;
    while (getline(cin, line)) {
        vector<char> row;
        for (num i = 0; i < line.size(); ++i) {
            row.push_back(line[i]);
            if (line[i] == 'S') startingPosition = {rows, i};
        }
        pipes.push_back(row);
        ++rows;
    }
    cols = pipes[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    queue<pos> q;
    q.push(startingPosition);
    while (!q.empty()) {
        pos currentPosition = q.front();
        q.pop();
        visited[currentPosition.first][currentPosition.second] = true;
        ++loopSize;
        vector<pos> neighbours = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
        for (pos neighbour : neighbours) {
            pos next = {currentPosition.first + neighbour.first, currentPosition.second + neighbour.second};
            if (next.first < 0 || next.first >= rows || next.second < 0 || next.second >= cols) continue;
            if (areConnected(currentPosition, next, pipes) && !visited[next.first][next.second]) {
                q.push(next);
                break;
            }
        }
    }
    for (num row = 0; row < rows; ++row) {
        for (num col = 0; col < cols; ++col) {
           if (!visited[row][col] && isInside({row, col}, rows, cols, visited, pipes)) ++inside;
        }
    }
    cout << "Part 1: " << loopSize / 2 << endl;
    cout << "Part 2: " << inside << endl;
    return 0;
}
