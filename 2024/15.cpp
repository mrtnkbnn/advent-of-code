#include <bits/stdc++.h>
using namespace std;
using num = long long;
using coord = pair<num, num>;
const map<char, coord> dirs = {{'^', {-1, 0}}, {'v', {1, 0}}, {'<', {0, -1}}, {'>', {0, 1}}};
const map<coord, coord> opposites = {{{{-1, 0}, {1, 0}}, {{1, 0}, {-1, 0}}, {{0, 1}, {0, -1}}, {{0, -1}, {0, 1}}}};

coord move(coord pos, char dir, vector<string> &grid) {
    coord delta = dirs.at(dir);
    coord nextPos = {pos.first + delta.first, pos.second + delta.second};
    if (grid[nextPos.first][nextPos.second] == '#') return pos;
    else if (grid[nextPos.first][nextPos.second] == '.') {
        grid[pos.first][pos.second] = '.';
        grid[nextPos.first][nextPos.second] = '@';
        return nextPos;
    }
    else {
        num count = 0;
        coord cur = nextPos;
        while (true) {
            if (grid[cur.first][cur.second] == 'O') {
                cur = {cur.first + delta.first, cur.second + delta.second};
                ++count;
            } else if (grid[cur.first][cur.second] == '#') {
                return pos;
            } else {
                coord opposite = opposites.at(delta);
                while (count--) {
                    grid[cur.first][cur.second] = 'O';
                    cur = {cur.first + opposite.first, cur.second + opposite.second};
                }
                grid[nextPos.first][nextPos.second] = '@';
                grid[pos.first][pos.second] = '.';
                return nextPos;
            }
        }
    }
}

coord move2(coord pos, char dir, vector<string> &grid) {
    coord delta = dirs.at(dir);
    coord nextPos = {pos.first + delta.first, pos.second + delta.second};
    if (grid[nextPos.first][nextPos.second] == '#') return pos;
    else if (grid[nextPos.first][nextPos.second] == '.') {
        grid[pos.first][pos.second] = '.';
        grid[nextPos.first][nextPos.second] = '@';
        return nextPos;
    }
    else {
        if (dir == '<' || dir == '>') {
            num count = 0;
            coord cur = nextPos;
            while (true) {
                if (grid[cur.first][cur.second] == '[' || grid[cur.first][cur.second] == ']') {
                    cur = {cur.first + delta.first, cur.second + delta.second};
                    ++count;
                } else if (grid[cur.first][cur.second] == '#') {
                    return pos;
                } else {
                    coord opposite = opposites.at(delta);
                    while (count--) {
                        grid[cur.first][cur.second] = grid[cur.first + opposite.first][cur.second + opposite.second];
                        cur = {cur.first + opposite.first, cur.second + opposite.second};
                    }
                    grid[nextPos.first][nextPos.second] = '@';
                    grid[pos.first][pos.second] = '.';
                    return nextPos;
                }
            }
        } else {
            vector<coord> toMove;
            vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
            queue<coord> q;
            q.push(nextPos);
            visited[nextPos.first][nextPos.second] = true;
            while (!q.empty()) {
                coord cur = q.front();
                q.pop();
                if (grid[cur.first][cur.second] == '[') {
                    toMove.push_back(cur);
                    if (!visited[cur.first][cur.second + 1]) {
                        q.push({cur.first, cur.second + 1});
                        visited[cur.first][cur.second + 1] = true;
                    }
                    if (!visited[cur.first + delta.first][cur.second]) {
                        q.push({cur.first + delta.first, cur.second});
                        visited[cur.first + delta.first][cur.second] = true;
                    }
                } else if (grid[cur.first][cur.second] == ']') {
                    toMove.push_back(cur);
                    if (!visited[cur.first][cur.second - 1]) {
                        q.push({cur.first, cur.second - 1});
                        visited[cur.first][cur.second - 1] = true;
                    }
                    if (!visited[cur.first + delta.first][cur.second]) {
                        q.push({cur.first + delta.first, cur.second});
                        visited[cur.first + delta.first][cur.second] = true;
                    }
                } else if (grid[cur.first][cur.second] == '#') {
                    return pos;
                }
            }
            if (dir == '^') sort(toMove.begin(), toMove.end());
            else if (dir == 'v') sort(toMove.rbegin(), toMove.rend());
            for (coord move : toMove) {
                grid[move.first + delta.first][move.second + delta.second] = grid[move.first][move.second];
                grid[move.first][move.second] = '.';
            }
            grid[nextPos.first][nextPos.second] = '@';
            grid[pos.first][pos.second] = '.';
            return nextPos;
        }
    }
}

int main() {
    num part1 = 0, part2 = 0, rows = 0;
    string line;
    coord pos;
    vector<string> original, moves, grid1, grid2;
    while (getline(cin, line) && line != "") {
        for (int col = 0; col < line.size(); ++col) {
            if (line[col] == '@') {
                pos = {rows, col};
                break;
            }
        }
        original.push_back(line);
        ++rows;
    }
    num cols = original[0].size();
    grid1 = original;
    while (getline(cin, line)) {
        moves.push_back(line);
        for (char dir : line) pos = move(pos, dir, grid1);
    }
    for (num row = 0; row < rows; ++row) {
        for (num col = 0; col < cols; ++col) {
            if (grid1[row][col] == 'O') part1 += 100 * row + col;
        }
    }
    for (num row = 0; row < rows; ++row) {
        string expanded = "";
        for (num col = 0; col < cols; ++col) {
            if (original[row][col] == '#') expanded += "##";
            else if (original[row][col] == 'O') expanded += "[]";
            else if (original[row][col] == '.') expanded += "..";
            else expanded += "@.";
        }
        grid2.push_back(expanded);
    }
    cols *= 2;
    for (num row = 0; row < rows; ++row) {
        for (num col = 0; col < cols; ++col) {
            if (grid2[row][col] == '@') pos = {row, col};
        }
    }
    for (string s : moves) {
        for (char dir : s) pos = move2(pos, dir, grid2);
    }
    for (num row = 0; row < rows; ++row) {
        for (num col = 0; col < cols; ++col) {
            if (grid2[row][col] == '[') part2 += 100 * row + col;
        }
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
