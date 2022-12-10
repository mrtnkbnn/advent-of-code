#include <bits/stdc++.h>
using namespace std;

int main() {
    string line;
    queue<int> instructions;
    while (getline(cin, line)) {
        if (line == "noop") {
            instructions.push(0);
        } else {
            instructions.push(0);
            instructions.push(stoi(line.substr(5)));
        }
    }
    int X = 1, cycle = 1, row = 0, col = 0, part1 = 0;
    vector<vector<bool>> crt(6, vector<bool>(40));
    while (!instructions.empty()) {
        if (abs(col - X) <= 1) {
            crt[row][col] = true;
        }
        ++col;
        if (col % 40 == 0) {
            ++row;
            col = 0;
        }
        X += instructions.front();
        ++cycle;
        if (cycle == 20 || cycle == 60 || cycle == 100 || cycle == 140 || cycle == 180 || cycle == 220) {
            part1 += cycle * X;
        }
        instructions.pop();
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2:" << endl;
    for (int y = 0; y < 6; ++y) {
        for (int x = 0; x < 40; ++x) {
            cout << (crt[y][x] ? '#' : '.');
        }
        cout << endl;
    }
    return 0;
}
