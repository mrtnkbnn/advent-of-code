#include <bits/stdc++.h>
using namespace std;
using num = long long;
using state = pair<pair<num, num>, pair<num, num>>;

num light(state start, vector<string> &layout) {
    num rows = layout.size();
    num cols = layout[0].length();
    vector<vector<bool>> energized(rows, vector<bool>(cols, false));
    map<state, bool> dp;
    queue<state> q;
    q.push(start);
    while (!q.empty()) {
        state current = q.front();
        q.pop();
        if (dp[current]) continue;
        dp[current] = true;
        pair<num, num> location = current.first;
        pair<num, num> direction = current.second;
        bool left = direction.first == 0 && direction.second == -1;
        bool right = direction.first == 0 && direction.second == 1;
        bool up = direction.first == -1 && direction.second == 0;
        bool down = direction.first == 1 && direction.second == 0;
        energized[location.first][location.second] = true;
        if (layout[location.first][location.second] == '.') {
            pair<num, num> nextLocation = {location.first + direction.first, location.second + direction.second};
            if (nextLocation.first >= 0 && nextLocation.first < rows && nextLocation.second >= 0 && nextLocation.second < cols) {
                q.push({nextLocation, direction});
            }
        } else if (layout[location.first][location.second] == '|') {
            if (up || down) {
                pair<num, num> nextLocation = {location.first + direction.first, location.second + direction.second};
                if (nextLocation.first >= 0 && nextLocation.first < rows && nextLocation.second >= 0 && nextLocation.second < cols) {
                    q.push({nextLocation, direction});
                }
            } else {
                pair<num, num> nextLocation1 = {location.first - 1, location.second};
                pair<num, num> nextLocation2 = {location.first + 1, location.second};
                if (nextLocation1.first >= 0 && nextLocation1.first < rows && nextLocation1.second >= 0 && nextLocation1.second < cols) {
                    q.push({nextLocation1, {-1, 0}});
                }
                if (nextLocation2.first >= 0 && nextLocation2.first < rows && nextLocation2.second >= 0 && nextLocation2.second < cols) {
                    q.push({nextLocation2, {1, 0}});
                }
            }
        } else if (layout[location.first][location.second] == '-') {
            if (left || right) {
                pair<num, num> nextLocation = {location.first + direction.first, location.second + direction.second};
                if (nextLocation.first >= 0 && nextLocation.first < rows && nextLocation.second >= 0 && nextLocation.second < cols) {
                    q.push({nextLocation, direction});
                }
            } else {
                pair<num, num> nextLocation1 = {location.first, location.second - 1};
                pair<num, num> nextLocation2 = {location.first, location.second + 1};
                if (nextLocation1.first >= 0 && nextLocation1.first < rows && nextLocation1.second >= 0 && nextLocation1.second < cols) {
                    q.push({nextLocation1, {0, -1}});
                }
                if (nextLocation2.first >= 0 && nextLocation2.first < rows && nextLocation2.second >= 0 && nextLocation2.second < cols) {
                    q.push({nextLocation2, {0, 1}});
                }
            }
        } else if (layout[location.first][location.second] == '/') {
            if (left) {
                pair<num, num> nextLocation = {location.first + 1, location.second};
                if (nextLocation.first >= 0 && nextLocation.first < rows && nextLocation.second >= 0 && nextLocation.second < cols) {
                    q.push({nextLocation, {1, 0}});
                }
            } else if (right) {
                pair<num, num> nextLocation = {location.first - 1, location.second};
                if (nextLocation.first >= 0 && nextLocation.first < rows && nextLocation.second >= 0 && nextLocation.second < cols) {
                    q.push({nextLocation, {-1, 0}});
                }
            } else if (up) {
                pair<num, num> nextLocation = {location.first, location.second + 1};
                if (nextLocation.first >= 0 && nextLocation.first < rows && nextLocation.second >= 0 && nextLocation.second < cols) {
                    q.push({nextLocation, {0, 1}});
                }
            } else if (down) {
                pair<num, num> nextLocation = {location.first, location.second - 1};
                if (nextLocation.first >= 0 && nextLocation.first < rows && nextLocation.second >= 0 && nextLocation.second < cols) {
                    q.push({nextLocation, {0, -1}});
                }
            }
        } else if (layout[location.first][location.second] == '\\') {
            if (left) {
                pair<num, num> nextLocation = {location.first - 1, location.second};
                if (nextLocation.first >= 0 && nextLocation.first < rows && nextLocation.second >= 0 && nextLocation.second < cols) {
                    q.push({nextLocation, {-1, 0}});
                }
            } else if (right) {
                pair<num, num> nextLocation = {location.first + 1, location.second};
                if (nextLocation.first >= 0 && nextLocation.first < rows && nextLocation.second >= 0 && nextLocation.second < cols) {
                    q.push({nextLocation, {1, 0}});
                }
            } else if (up) {
                pair<num, num> nextLocation = {location.first, location.second - 1};
                if (nextLocation.first >= 0 && nextLocation.first < rows && nextLocation.second >= 0 && nextLocation.second < cols) {
                    q.push({nextLocation, {0, -1}});
                }
            } else if (down) {
                pair<num, num> nextLocation = {location.first, location.second + 1};
                if (nextLocation.first >= 0 && nextLocation.first < rows && nextLocation.second >= 0 && nextLocation.second < cols) {
                    q.push({nextLocation, {0, 1}});
                }
            }
        }
    }
    num result = 0;
    for (num row = 0; row < rows; ++row) {
        for (num col = 0; col < cols; ++col) {
            if (energized[row][col]) ++result;
        }
    }
    return result;
}

int main() {
    vector<string> layout;
    string line;
    while (getline(cin, line)) layout.push_back(line);
    num part1 = light({{0, 0}, {0, 1}}, layout);
    num part2 = LONG_LONG_MIN;
    num rows = layout.size();
    num cols = layout[0].length();
    for (num col = 0; col < cols; ++col) {
        num down = light({{0, col}, {1, 0}}, layout);
        num up = light({{rows - 1, col}, {-1, 0}}, layout);
        part2 = max(down, max(up, part2));
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
