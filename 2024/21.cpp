#include <bits/stdc++.h>
using namespace std;
using num = long long;
using coord = pair<num, num>;
const vector<coord> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
const vector<vector<char>> doorPad = {{'7', '8', '9'}, {'4', '5', '6'}, {'1', '2', '3'}, {'#', '0', 'A'}};
const vector<vector<char>> robotPad = {{'#', '^', 'A'}, {'<', 'v', '>'}};
const map<char, coord> buttons = {{'^', {-1, 0}}, {'v', {1, 0}}, {'<', {0, -1}}, {'>', {0, 1}}};

char pressA(num pad, vector<coord> &positions) {
    coord curPos = positions[pad];
    if (pad == positions.size() - 1) {
        char button = doorPad[curPos.first][curPos.second];
        return button;
    }
    char button = robotPad[curPos.first][curPos.second];
    if (button == 'A') {
        return pressA(pad + 1, positions);
    } else {
        coord delta = buttons.at(button);
        positions[pad + 1].first += delta.first;
        positions[pad + 1].second += delta.second;
        if (pad + 1 == positions.size() - 1) {
            if (positions[pad + 1].first < 0 || positions[pad + 1].first > 3 || positions[pad + 1].second < 0 || positions[pad + 1].second > 2) return '-';
            else if (positions[pad + 1].first == 3 && positions[pad + 1].second == 0) return '-';
            else return '+';
        } else {
            if (positions[pad + 1].first < 0 || positions[pad + 1].first > 1 || positions[pad + 1].second < 0 || positions[pad + 1].second > 2) return '-';
            else if (positions[pad + 1].first == 0 && positions[pad + 1].second == 0) return '-';
            else return '+';
        }
    }
}

num solve(string input, num robots) {
    map<pair<string, vector<coord>>, bool> visited;
    queue<tuple<num, string, vector<coord>>> q;
    vector<coord> initial;
    while (robots--) initial.push_back({0, 2});
    initial.push_back({3, 2});
    q.push({0, input, initial});
    visited[{input, initial}] = true;
    while (!q.empty()) {
        auto top = q.front();
        q.pop();
        num presses = get<0>(top);
        string toSolve = get<1>(top);
        vector<coord> positions = get<2>(top);
        vector<coord> aPressPositions = positions;
        char a = pressA(0, aPressPositions);
        if (a == '-') {
            // do nothing
        } else if (a == '+') {
            if (!visited[{toSolve, aPressPositions}]) {
                q.push({presses + 1, toSolve, aPressPositions});
                visited[{toSolve, aPressPositions}] = true;
            }
        } else {
            if (a != toSolve[0]) {
                // do nothing
            } else if (toSolve.length() == 1) {
                return presses + 1;
            } else {
                if (!visited[{toSolve.substr(1), aPressPositions}]) {
                    q.push({presses + 1, toSolve.substr(1), aPressPositions});
                    visited[{toSolve.substr(1), aPressPositions}] = true;
                }
            }
        }
        for (coord dir : dirs) {
            coord next = {positions[0].first + dir.first, positions[0].second + dir.second};
            if (next.first < 0 || next.first > 1 || next.second < 0 || next.second > 2) continue;
            if (next.first == 0 && next.second == 0) continue;
            vector<coord> newPositions = positions;
            newPositions[0].first = next.first;
            newPositions[0].second = next.second;
            if (!visited[{toSolve, newPositions}]) {
                q.push({presses + 1, toSolve, newPositions});
                visited[{toSolve, newPositions}] = true;
            }
        }
    }
    return 0;
}

int main() {
    num part1 = 0, part2 = 0;
    string line;
    while (getline(cin, line)) {
        part1 += solve(line, 2) * stoll(line.substr(0, line.length() - 1));
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
