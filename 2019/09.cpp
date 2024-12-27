#include <bits/stdc++.h>
using namespace std;
using num = long long;

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

int main() {
    num part1 = 0, part2 = 0;
    string line;
    getline(cin, line);
    intcode prog1(line), prog2(line);
    prog1.run(1);
    prog2.run(2);
    cout << "Part 1: " << prog1.output[0] << endl;
    cout << "Part 2: " << prog2.output[0] << endl;
    return 0;
}
