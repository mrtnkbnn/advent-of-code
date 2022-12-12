#include <bits/stdc++.h>
using namespace std;

struct pos {
    int row, col, dist;

    pos(int _row, int _col, int _dist) {
        row = _row;
        col = _col;
        dist = _dist;
    }
};

struct comparator {
    bool operator ()(pos* pos1, pos* pos2) {
        return pos1->dist > pos2->dist || (pos1->dist == pos2->dist && (pos1->row > pos2->row || (pos1->row == pos2->row && pos1->col > pos2->col)));
    }
};

int main() {
    string line;
    int ROWS, COLS, startRow, startCol, endRow, endCol;
    vector<vector<char>> hill;
    int i = 0;
    while (getline(cin, line)) {
        COLS = line.length();
        vector<char> col;
        for (int j = 0; j < line.length(); ++j) {
            char c = line[j];
            if (c == 'S') {
                startRow = i;
                startCol = j;
                col.push_back('a');
            } else if (c == 'E') {
                endRow = i;
                endCol = j;
                col.push_back('z');
            } else {
                col.push_back(c);
            }
        }
        hill.push_back(col);
        ++i;
    }
    ROWS = hill.size();
    vector<vector<int>> dist(ROWS, vector<int>(COLS, INT_MAX));
    vector<vector<bool>> visited(ROWS, vector<bool>(COLS));
    priority_queue<pos*, vector<pos*>, comparator> Q;
    dist[endRow][endCol] = 0;
    Q.push(new pos(endRow, endCol, 0));
    while (!Q.empty()) {
        pos* curPos = Q.top();
        Q.pop();
        int curRow = curPos->row;
        int curCol = curPos->col;
        char current = hill[curRow][curCol];
        if (curRow - 1 >= 0 && !visited[curRow - 1][curCol] && hill[curRow - 1][curCol] >= current - 1 && dist[curRow][curCol] + 1 < dist[curRow - 1][curCol]) {
            dist[curRow - 1][curCol] = dist[curRow][curCol] + 1;
            Q.push(new pos(curRow - 1, curCol, dist[curRow][curCol] + 1));
        }
        if (curRow + 1 < ROWS && !visited[curRow + 1][curCol] && hill[curRow + 1][curCol] >= current - 1 && dist[curRow][curCol] + 1 < dist[curRow + 1][curCol]) {
            dist[curRow + 1][curCol] = dist[curRow][curCol] + 1;
            Q.push(new pos(curRow + 1, curCol, dist[curRow][curCol] + 1));
        }
        if (curCol - 1 >= 0 && !visited[curRow][curCol - 1] && hill[curRow][curCol - 1] >= current - 1 && dist[curRow][curCol] + 1 < dist[curRow][curCol - 1]) {
            dist[curRow][curCol - 1] = dist[curRow][curCol] + 1;
            Q.push(new pos(curRow, curCol - 1, dist[curRow][curCol] + 1));
        }
        if (curCol + 1 < COLS && !visited[curRow][curCol + 1] && hill[curRow][curCol + 1] >= current - 1 && dist[curRow][curCol] + 1 < dist[curRow][curCol + 1]) {
            dist[curRow][curCol + 1] = dist[curRow][curCol] + 1;
            Q.push(new pos(curRow, curCol + 1, dist[curRow][curCol] + 1));
        }
        visited[curRow][curCol] = true;
    }
    int part2 = INT_MAX;
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            if (hill[row][col] == 'a') {
                part2 = min(part2, dist[row][col]);
            }
        }
    }
    cout << "Part 1: " << dist[startRow][startCol] << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
