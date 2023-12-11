#include <bits/stdc++.h>
using namespace std;
using num = long long;
using pos = pair<num, num>;

num steps(pos galaxy1, pos galaxy2, vector<num> &emptyRows, vector<num> &emptyCols, num expansion) {
    num rowFrom = min(galaxy1.first, galaxy2.first);
    num rowTo = max(galaxy1.first, galaxy2.first);
    num colFrom = min(galaxy1.second, galaxy2.second);
    num colTo = max(galaxy1.second, galaxy2.second);
    num additionalSteps = 0;
    for (num i = rowFrom; i < rowTo; ++i) {
        if (find(emptyRows.begin(), emptyRows.end(), i) != emptyRows.end()) additionalSteps += (expansion - 1);
    }
    for (num i = colFrom; i < colTo; ++i) {
        if (find(emptyCols.begin(), emptyCols.end(), i) != emptyCols.end()) additionalSteps += (expansion - 1);
    }
    return (rowTo - rowFrom) + (colTo - colFrom) + additionalSteps;
}

int main() {
    string line;
    vector<pos> galaxies;
    vector<num> emptyRows, emptyCols;
    num cols, rows = 0, part1 = 0, part2 = 0;
    while (getline(cin, line)) {
        bool emptyRow = true;
        cols = line.length();
        for (num col = 0; col < line.length(); ++col) {
            if (line[col] == '#') {
                galaxies.push_back({rows, col});
                emptyRow = false;
            }
        }
        if (emptyRow) emptyRows.push_back(rows);
        ++rows;
    }
    for (num i = 0; i < cols; ++i) {
        bool emptyCol = true;
        for (pos &galaxy : galaxies) {
            if (galaxy.second == i) {
                emptyCol = false;
                break;
            }
        }
        if (emptyCol) emptyCols.push_back(i);
    }
    for (num i = 0; i < galaxies.size(); ++i) {
        for (num j = i + 1; j < galaxies.size(); ++j) {
            part1 += steps(galaxies[i], galaxies[j], emptyRows, emptyCols, 2);
            part2 += steps(galaxies[i], galaxies[j], emptyRows, emptyCols, 1000000);
        }
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
