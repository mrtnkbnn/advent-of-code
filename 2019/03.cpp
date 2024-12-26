#include <bits/stdc++.h>
using namespace std;
using num = long long;
using coord = pair<num, num>;
const map<char, coord> deltas = {{'U', {1, 0}}, {'D', {-1, 0}}, {'R', {0, 1}}, {'L', {0, -1}}};

vector<coord> parse(string line) {
    vector<coord> result;
    replace(line.begin(), line.end(), ',', ' ');
    stringstream ss(line);
    string path;
    coord cur = {0, 0};
    result.push_back(cur);
    while (ss >> path) {
        coord delta = deltas.at(path[0]);
        num mul = stoll(path.substr(1));
        coord next = {cur.first + delta.first * mul, cur.second + delta.second * mul};
        result.push_back(next);
        cur = next;
    }
    return result;
}

num steps(num a, vector<coord> &path) {
    num result = 0;
    for (num i = 1; i <= a; ++i) {
        coord left = path[i - 1];
        coord right = path[i];
        result += abs(left.first - right.first) + abs(left.second - right.second);
    }
    return result;
}

int main() {
    num part1 = LONG_LONG_MAX, part2 = LONG_LONG_MAX;
    string line;
    getline(cin, line);
    auto path1 = parse(line);
    getline(cin, line);
    auto path2 = parse(line);
    for (num i = 1; i < path1.size(); ++i) {
        for (num j = 1; j < path2.size(); ++j) {
            coord a = path1[i - 1];
            coord b = path1[i];
            coord c = path2[j - 1];
            coord d = path2[j];
            if (a.first == b.first && c.second == d.second) {
                if (c.second >= min(a.second, b.second) && c.second <= max(a.second, b.second)) {
                    if (a.first >= min(c.first, d.first) && a.first <= max(c.first, d.first)) {
                        coord intersect = {a.first, c.second};
                        if (intersect.first != 0 && intersect.second != 0) {
                            part1 = min(part1, abs(intersect.first) + abs(intersect.second));
                            part2 = min(part2, steps(i - 1, path1) + steps(j - 1, path2) + abs(path1[i - 1].first - intersect.first) + abs(path1[i - 1].second - intersect.second) + abs(path2[j - 1].first - intersect.first) + abs(path2[j - 1].second - intersect.second));
                        }
                    }
                }
            } else if (a.second == b.second && c.first == d.first) {
                if (c.first >= min(a.first, b.first) && c.first <= max(a.first, b.first)) {
                    if (a.second >= min(c.second, d.second) && a.second <= max(c.second, d.second)) {
                        coord intersect = {a.second, c.first};
                        if (intersect.first != 0 && intersect.second != 0) {
                            part1 = min(part1, abs(intersect.first) + abs(intersect.second));
                            part2 = min(part2, steps(i - 1, path1) + steps(j - 1, path2) + abs(path1[i - 1].first - intersect.first) + abs(path1[i - 1].second - intersect.second) + abs(path2[j - 1].first - intersect.first) + abs(path2[j - 1].second - intersect.second));
                        }
                    }
                }
            }
        }
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
