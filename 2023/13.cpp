#include <bits/stdc++.h>
using namespace std;
using num = long long;

string colAsString(vector<string> &pattern, num col) {
    string result = "";
    for (string row : pattern) result += row[col];
    return result;
}

num findRows(vector<string> &pattern, num exclude) {
    for (num i = 1; i < pattern.size(); ++i) {
        if (i == exclude) continue;
        if (pattern[i] == pattern[i - 1]) {
            bool isPossible = true;
            int up = i - 2;
            int down = i + 1;
            while (up >= 0 && down < pattern.size()) {
                if (pattern[up] != pattern[down]) {
                    isPossible = false;
                    break;
                }
                --up;
                ++down;
            }
            if (isPossible) return i;
        }
    }
    return -1;
}

num findCols(vector<string> &pattern, num exclude) {
    num limit = pattern[0].length();
    for (num i = 1; i < limit; ++i) {
        if (i == exclude) continue;
        if (colAsString(pattern, i) == colAsString(pattern, i - 1)) {
            bool isPossible = true;
            int left = i - 2;
            int right = i + 1;
            while (left >= 0 && right < limit) {
                if (colAsString(pattern, left) != colAsString(pattern, right)) {
                    isPossible = false;
                    break;
                }
                --left;
                ++right;
            }
            if (isPossible) return i;
        }
    }
    return -1;
}

int main() {
    num part1 = 0, part2 = 0;
    string line;
    vector<vector<string>> patterns;
    vector<string> currentPattern;
    while (getline(cin, line)) {
        if (line == "") {
            patterns.push_back(currentPattern);
            currentPattern = {};
            continue;
        }
        currentPattern.push_back(line);
    }
    patterns.push_back(currentPattern);
    map<num, pair<num, num>> results;
    for (num i = 0; i < patterns.size(); ++i) {
        vector<string> pattern = patterns[i];
        num rows = findRows(pattern, -1);
        num cols = findCols(pattern, -1);
        if (rows != -1) part1 += (100 * rows);
        if (cols != -1) part1 += cols;
        results[i] = {rows, cols};
    }
    for (num i = 0; i < patterns.size(); ++i) {
        vector<string> pattern = patterns[i];
        num colsLimit = pattern[0].length();
        bool found = false;
        for (num row = 0; row < pattern.size(); ++row) {
            for (num col = 0; col < colsLimit; ++col) {
                char current = pattern[row][col];
                char smudge = current == '.' ? '#' : '.';
                pattern[row][col] = smudge;
                num rows = findRows(pattern, results[i].first);
                num cols = findCols(pattern, results[i].second);
                if (rows != -1 && results[i].first != rows) {
                    part2 += (100 * rows);
                    found = true;
                    break;
                } else if (cols != -1 && results[i].second != cols) {
                    part2 += cols;
                    found = true;
                    break;
                } else {
                    pattern[row][col] = current;
                }
            }
            if (found) break;
        }
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
