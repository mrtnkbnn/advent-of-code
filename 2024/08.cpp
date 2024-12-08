#include <bits/stdc++.h>
using namespace std;
using num = long long;
using coord = pair<num, num>;

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
    set<coord> antinodes;
    set<coord> antinodes2;
    for (auto &[antenna, coords] : antennas) {
        for (auto i = coords.begin(); i != coords.end(); ++i) {
            for (auto j = next(i); j != coords.end(); ++j) {
                coord left = *i;
                coord right = *j;
                num rowD = left.first - right.first;
                num colD = left.second - right.second;
                vector<coord> poss = {{left.first + rowD, left.second + colD}, {right.first + rowD, right.second + colD}, {left.first - rowD, left.second - colD}, {right.first - rowD, right.second - colD}};
                for (auto pos : poss) {
                    if (pos != left && pos != right && pos.first >= 0 && pos.first < rows && pos.second >= 0 && pos.second < cols) antinodes.insert(pos);
                }
            }
        }
    }
    for (auto &[antenna, coords] : antennas) {
        for (auto i = coords.begin(); i != coords.end(); ++i) {
            for (auto j = next(i); j != coords.end(); ++j) {
                coord left = *i;
                coord right = *j;
                for (num m = 1; m < max(rows, cols); ++m) {
                    num rowD = m * (left.first - right.first);
                    num colD = m * (left.second - right.second);
                    vector<coord> poss = {{left.first + rowD, left.second + colD}, {right.first + rowD, right.second + colD}, {left.first - rowD, left.second - colD}, {right.first - rowD, right.second - colD}};
                    for (auto pos : poss) {
                        if (pos.first >= 0 && pos.first < rows && pos.second >= 0 && pos.second < cols) antinodes2.insert(pos);
                    }
                }
            }
        }
    }
    cout << "Part 1: " << antinodes.size() << endl;
    cout << "Part 2: " << antinodes2.size() << endl;
    return 0;
}
