#include <bits/stdc++.h>
using namespace std;
using num = long long;

bool isSafe(vector<num> &level) {
    num prev = 0;
    for (num i = 0; i < level.size() - 1; ++i) {
        num step = level[i + 1] - level[i];
        if (step == 0 || abs(step) > 3) return false;
        if (prev == 0) {
            prev = step;
            continue;
        }
        if ((prev < 0 && step > 0) || (prev > 0 && step < 0)) return false;
        prev = step;
    }
    return true;
}

bool isSafe2(vector<num> &level) {
    if (isSafe(level)) return true;
    for (num i = 0; i < level.size(); ++i) {
        vector<num> bad = level;
        bad.erase(bad.begin() + i);
        if (isSafe(bad)) return true;
    }
    return false;
}

int main() {
    num part1 = 0, part2 = 0, n;
    string line;
    while (getline(cin, line)) {
        vector<num> level;
        stringstream ss(line);
        while (ss >> n) level.push_back(n);
        if (isSafe(level)) ++part1;
        if (isSafe2(level)) ++part2;
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
