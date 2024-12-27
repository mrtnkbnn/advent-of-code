#include "intcode.hpp"
using coord = pair<num, num>;
const map<pair<coord, num>, coord> dirs = {
    {{{-1, 0}, 0}, {0, -1}},
    {{{-1, 0}, 1}, {0, 1}},
    {{{1, 0}, 0}, {0, 1}},
    {{{1, 0}, 1}, {0, -1}},
    {{{0, 1}, 0}, {-1, 0}},
    {{{0, 1}, 1}, {1, 0}},
    {{{0, -1}, 0}, {1, 0}},
    {{{0, -1}, 1}, {-1, 0}},
};

num part1(string line) {
    intcode prog(line);
    map<coord, num> colors;
    set<coord> painted;
    coord pos = {0, 0}, dir = {-1, 0};
    while (!prog.halted) {
        num currentColor = colors[pos];
        prog.run(currentColor);
        num newColor = prog.output[prog.output.size() - 2];
        num newDir = prog.output[prog.output.size() - 1];
        colors[pos] = newColor;
        painted.insert(pos);
        dir = dirs.at({dir, newDir});
        pos = {pos.first + dir.first, pos.second + dir.second};
    }
    return painted.size();
}

void part2(string line) {
    intcode prog(line);
    map<coord, num> colors;
    colors[{0, 0}] = 1;
    set<coord> painted;
    coord pos = {0, 0}, dir = {-1, 0};
    num minRow = 0, maxRow = 0, minCol = 0, maxCol = 0;
    while (!prog.halted) {
        num currentColor = colors[pos];
        prog.run(currentColor);
        num newColor = prog.output[prog.output.size() - 2];
        num newDir = prog.output[prog.output.size() - 1];
        colors[pos] = newColor;
        painted.insert(pos);
        dir = dirs.at({dir, newDir});
        pos = {pos.first + dir.first, pos.second + dir.second};
        minRow = min(minRow, pos.first);
        maxRow = max(maxRow, pos.first);
        minCol = min(minCol, pos.second);
        maxCol = max(maxCol, pos.second);
    }
    for (num row = minRow; row <= maxRow; ++row) {
        for (num col = minCol; col <= maxCol; ++col) {
            cout << (colors[{row, col}] == 1 ? '#' : ' ');
        }
        cout << endl;
    }
}

int main() {
    string line;
    getline(cin, line);
    cout << "Part 1: " << part1(line) << endl;
    cout << "Part 2:" << endl;
    part2(line);
    return 0;
}
