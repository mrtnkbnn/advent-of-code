#include <bits/stdc++.h>
using namespace std;
using num = long long;

int main() {
    num part1 = 0;
    string line;
    vector<vector<string>> schematics;
    vector<string> cur;
    while (getline(cin, line)) {
        if (line == "") {
            schematics.push_back(cur);
            cur = {};
            continue;
        }
        cur.push_back(line);
    }
    schematics.push_back(cur);
    vector<vector<num>> locks;
    vector<vector<num>> keys;
    for (auto schematic : schematics) {
        if (schematic[0][0] == '#') {
            vector<num> heights;
            for (num col = 0; col < schematic[0].length(); ++col) {
                for (num row = 1; row < schematic.size(); ++row) {
                    if (schematic[row][col] == '.') {
                        heights.push_back(row - 1);
                        break;
                    }
                }
            }
            locks.push_back(heights);
        } else {
            vector<num> heights;
            for (num col = 0; col < schematic[0].length(); ++col) {
                for (num row = schematic.size() - 2; row >= 0; --row) {
                    if (schematic[row][col] == '.') {
                        heights.push_back(schematic.size() - 2 - row);
                        break;
                    }
                }
            }
            keys.push_back(heights);
        }
    }
    for (auto lock : locks) {
        for (auto key : keys) {
            bool fits = true;
            for (num i = 0; i < lock.size(); ++i) {
                if (lock[i] + key[i] >= 6) fits = false;
            }
            if (fits) ++part1;
        }
    }
    cout << "Part 1: " << part1 << endl;
    return 0;
}
