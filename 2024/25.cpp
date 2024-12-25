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
    for (num i = 0; i < schematics.size(); ++i) {
        for (num j = i + 1; j < schematics.size(); ++j) {
            bool fits = true;
            for (num row = 0; row < schematics[i].size(); ++row) {
                for (num col = 0; col < schematics[i][0].length(); ++col) {
                    if (schematics[i][row][col] == '#' && schematics[j][row][col] == '#') {
                        fits = false;
                    }
                }
            }
            if (fits) ++part1;
        }
    }
    cout << "Part 1: " << part1 << endl;
    return 0;
}
