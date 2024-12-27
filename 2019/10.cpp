#include <bits/stdc++.h>
using namespace std;
using num = long long;
using coord = pair<num, num>;

coord best;

bool compare(coord left, coord right) {
    double leftAngle = 90.0 - (atan2((left.first - best.first) * -1, left.second - best.second) * 180.0 / M_PI);
    if (leftAngle < 0) leftAngle += 360.0;
    double rightAngle = 90.0 - (atan2((right.first - best.first) * -1, right.second - best.second) * 180.0 / M_PI);
    if (rightAngle < 0) rightAngle += 360.0;
    return leftAngle < rightAngle;
}

int main() {
    num part1 = LONG_LONG_MIN, part2 = 0, rows = 0;
    string line;
    vector<string> grid;
    vector<coord> asteroids, direct;
    while (getline(cin, line)) {
        grid.push_back(line);
        for (num col = 0; col < line.length(); ++col) {
            if (line[col] == '#') asteroids.push_back({rows, col});
        }
        ++rows;
    }
    for (num i = 0; i < asteroids.size(); ++i) {
        vector<coord> detects;
        for (num j = 0; j < asteroids.size(); ++j) {
            if (i == j) continue;
            coord a = asteroids[i];
            coord b = asteroids[j];
            coord tmp = {b.first - a.first, b.second - a.second};
            coord step = {tmp.first / gcd(tmp.first, tmp.second), tmp.second / gcd(tmp.first, tmp.second)};
            coord next = {a.first + step.first, a.second + step.second};
            while (true) {
                if (next.first == b.first && next.second == b.second) {
                    detects.push_back(b);
                    break;
                } else if (grid[next.first][next.second] == '#') {
                    break;
                } else {
                    next = {next.first + step.first, next.second + step.second};
                }
            }
        }
        if ((num)detects.size() > part1) {
            part1 = detects.size();
            best = asteroids[i];
            direct = detects;
        }
    }
    sort(direct.begin(), direct.end(), compare);
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << direct[199].second * 100 + direct[199].first << endl;
    return 0;
}
