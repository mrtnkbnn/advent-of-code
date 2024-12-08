#include <bits/stdc++.h>
using namespace std;
using num = long long;
using coord = pair<num, num>;

num count(map<char, set<coord>> &antennas, num rows, num cols, bool multiply) {
    set<coord> result;
    for (auto &[antenna, coords] : antennas) {
        for (auto i = coords.begin(); i != coords.end(); ++i) {
            for (auto j = next(i); j != coords.end(); ++j) {
                coord left = *i;
                coord right = *j;
                for (num m = (multiply ? 0 : 1); m < (multiply ? max(rows, cols) : 2); ++m) {
                    coord diff = {m * (left.first - right.first), m * (left.second - right.second)};
                    vector<coord> antinodes = {{left.first + diff.first, left.second + diff.second}, {right.first - diff.first, right.second - diff.second}};
                    for (auto antinode : antinodes) {
                        if (antinode.first >= 0 && antinode.first < rows && antinode.second >= 0 && antinode.second < cols) result.insert(antinode);
                    }
                }
            }
        }
    }
    return result.size();
}

int main() {
    num rows = 0, cols;
    string line;
    map<char, set<coord>> antennas;
    while (getline(cin, line)) {
        for (num c = 0; c < line.length(); ++c) {
            if (line[c] != '.') antennas[line[c]].insert({rows, c});
        }
        ++rows;
        cols = line.length();
    }
    cout << "Part 1: " << count(antennas, rows, cols, false) << endl;
    cout << "Part 2: " << count(antennas, rows, cols, true) << endl;
    return 0;
}
