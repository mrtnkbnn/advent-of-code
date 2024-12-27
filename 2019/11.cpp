#include <bits/stdc++.h>
using namespace std;
using num = long long;
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

struct intcode {
    vector<num> memory, input, output;
    num pointer = 0, inputPointer = 0, relativeBase = 0;
    bool halted = false;

    intcode(string program) {
        replace(program.begin(), program.end(), ',', ' ');
        stringstream ss(program);
        num n;
        while (ss >> n) memory.push_back(n);
    }

    void extend(num pos) {
        num limit = pos - memory.size() + 1;
        for (num i = 0; i < limit; ++i) memory.push_back(0);
    }

    num read(num pos) {
        extend(pos);
        return memory[pos];
    }

    void write(num pos, num val) {
        extend(pos);
        memory[pos] = val;
    }

    num param(num pos, num mode) {
        return read(addr(pos, mode));
    }

    num addr(num pos, num mode) {
        if (mode == 0) {
            return read(pos);
        } else if (mode == 1) {
            return pos;
        } else if (mode == 2) {
            return relativeBase + read(pos);
        } else {
            throw invalid_argument("invalid mode");
        }
    }

    void run(num val) {
        input.push_back(val);
        run();
    }

    void run() {
        if (halted) throw invalid_argument("halted");
        while (true) {
            num value = read(pointer);
            num opcode = value % 100;
            if (opcode == 1) {
                auto mode = modes(3, value);
                num param1 = param(pointer + 1, mode[0]);
                num param2 = param(pointer + 2, mode[1]);
                write(addr(pointer + 3, mode[2]), param1 + param2);
                pointer += 4;
            } else if (opcode == 2) {
                auto mode = modes(3, value);
                num param1 = param(pointer + 1, mode[0]);
                num param2 = param(pointer + 2, mode[1]);
                write(addr(pointer + 3, mode[2]), param1 * param2);
                pointer += 4;
            } else if (opcode == 3) {
                if (inputPointer >= input.size()) {
                    return;
                }
                auto mode = modes(1, value);
                write(addr(pointer + 1, mode[0]), input[inputPointer]);
                ++inputPointer;
                pointer += 2;
            } else if (opcode == 4) {
                auto mode = modes(1, value);
                num param1 = param(pointer + 1, mode[0]);
                output.push_back(param1);
                pointer += 2;
            } else if (opcode == 5) {
                auto mode = modes(2, value);
                num param1 = param(pointer + 1, mode[0]);
                num param2 = param(pointer + 2, mode[1]);
                if (param1 != 0) {
                    pointer = param2;
                } else {
                    pointer += 3;
                }
            } else if (opcode == 6) {
                auto mode = modes(2, value);
                num param1 = param(pointer + 1, mode[0]);
                num param2 = param(pointer + 2, mode[1]);
                if (param1 == 0) {
                    pointer = param2;
                } else {
                    pointer += 3;
                }
            } else if (opcode == 7) {
                auto mode = modes(3, value);
                num param1 = param(pointer + 1, mode[0]);
                num param2 = param(pointer + 2, mode[1]);
                if (param1 < param2) {
                    write(addr(pointer + 3, mode[2]), 1);
                } else {
                    write(addr(pointer + 3, mode[2]), 0);
                }
                pointer += 4;
            } else if (opcode == 8) {
                auto mode = modes(3, value);
                num param1 = param(pointer + 1, mode[0]);
                num param2 = param(pointer + 2, mode[1]);
                if (param1 == param2) {
                    write(addr(pointer + 3, mode[2]), 1);
                } else {
                    write(addr(pointer + 3, mode[2]), 0);
                }
                pointer += 4;
            } else if (opcode == 9) {
                auto mode = modes(1, value);
                num param1 = param(pointer + 1, mode[0]);
                relativeBase += param1;
                pointer += 2;
            } else if (opcode == 99) {
                halted = true;
                return;
            } else {
                throw invalid_argument("invalid opcode");
            }
        }
    }

    private: vector<num> modes(num n, num value) {
        value /= 100;
        vector<num> digits;
        while (value > 0) {
            digits.push_back(value % 10);
            value /= 10;
        }
        vector<num> result = digits;
        for (num i = 0; i < (n - digits.size()); ++i) {
            result.push_back(0);
        }
        return result;
    }
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
