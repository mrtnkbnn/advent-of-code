#include <bits/stdc++.h>
using namespace std;
using num = long long;

struct intcode {
    vector<num> program, inputs, outputs;
    num pointer = 0, inputPointer = 0;
    bool halted = false;

    intcode(string input) {
        replace(input.begin(), input.end(), ',', ' ');
        stringstream ss(input);
        num n;
        while (ss >> n) program.push_back(n);
    }

    void run() {
        while (true) {
            num value = program[pointer];
            num opcode = value % 100;
            value /= 100;
            if (opcode == 1) {
                num parameters = 3;
                auto modes = parameterModes(parameters, value);
                num param1 = modes[0] == 0 ? program[program[pointer + 1]] : program[pointer + 1];
                num param2 = modes[1] == 0 ? program[program[pointer + 2]] : program[pointer + 2];
                program[program[pointer + 3]] = param1 + param2;
                pointer += parameters + 1;
            } else if (opcode == 2) {
                num parameters = 3;
                auto modes = parameterModes(parameters, value);
                num param1 = modes[0] == 0 ? program[program[pointer + 1]] : program[pointer + 1];
                num param2 = modes[1] == 0 ? program[program[pointer + 2]] : program[pointer + 2];
                program[program[pointer + 3]] = param1 * param2;
                pointer += parameters + 1;
            } else if (opcode == 3) {
                if (inputPointer >= inputs.size()) {
                    break;
                }
                num parameters = 1;
                program[program[pointer + 1]] = inputs[inputPointer];
                ++inputPointer;
                pointer += parameters + 1;
            } else if (opcode == 4) {
                num parameters = 1;
                auto modes = parameterModes(parameters, value);
                num param1 = modes[0] == 0 ? program[program[pointer + 1]] : program[pointer + 1];
                pointer += parameters + 1;
                outputs.push_back(param1);
            } else if (opcode == 5) {
                num parameters = 2;
                auto modes = parameterModes(parameters, value);
                num param1 = modes[0] == 0 ? program[program[pointer + 1]] : program[pointer + 1];
                num param2 = modes[1] == 0 ? program[program[pointer + 2]] : program[pointer + 2];
                if (param1 != 0) {
                    pointer = param2;
                } else {
                    pointer += parameters + 1;
                }
            } else if (opcode == 6) {
                num parameters = 2;
                auto modes = parameterModes(parameters, value);
                num param1 = modes[0] == 0 ? program[program[pointer + 1]] : program[pointer + 1];
                num param2 = modes[1] == 0 ? program[program[pointer + 2]] : program[pointer + 2];
                if (param1 == 0) {
                    pointer = param2;
                } else {
                    pointer += parameters + 1;
                }
            } else if (opcode == 7) {
                num parameters = 3;
                auto modes = parameterModes(parameters, value);
                num param1 = modes[0] == 0 ? program[program[pointer + 1]] : program[pointer + 1];
                num param2 = modes[1] == 0 ? program[program[pointer + 2]] : program[pointer + 2];
                if (param1 < param2) {
                    program[program[pointer + 3]] = 1;
                } else {
                    program[program[pointer + 3]] = 0;
                }
                pointer += parameters + 1;
            } else if (opcode == 8) {
                num parameters = 3;
                auto modes = parameterModes(parameters, value);
                num param1 = modes[0] == 0 ? program[program[pointer + 1]] : program[pointer + 1];
                num param2 = modes[1] == 0 ? program[program[pointer + 2]] : program[pointer + 2];
                if (param1 == param2) {
                    program[program[pointer + 3]] = 1;
                } else {
                    program[program[pointer + 3]] = 0;
                }
                pointer += parameters + 1;
            } else if (opcode == 99) {
                halted = true;
                break;
            }
        }
    }


    private: vector<num> parameterModes(num n, num value) {
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

num thruster(vector<num> phase, intcode &program) {
    vector<intcode> amplifiers(5, program);
    num prev = 0;
    for (num i = 0; i < phase.size(); ++i) {
        amplifiers[i].inputs = {phase[i], prev};
        amplifiers[i].run();
        prev = amplifiers[i].outputs.back();
    }
    return prev;
}


num feedback(vector<num> phase, intcode &program) {
    vector<intcode> amplifiers(5, program);
    for (num i = 0; i < 5; ++i) amplifiers[i].inputs.push_back(phase[i]);
    num pointer = 0;
    num prev = 0;
    while (true) {
        amplifiers[pointer].inputs.push_back(prev);
        amplifiers[pointer].run();
        prev = amplifiers[pointer].outputs.back();
        if (pointer == 4 && amplifiers[pointer].halted) break;
        pointer = (pointer + 1) % 5;
    }
    return prev;
}


int main() {
    num part1 = LONG_LONG_MIN, part2 = LONG_LONG_MIN;
    string line;
    getline(cin, line);
    intcode program(line);
    vector<num> phase = {0, 1, 2, 3, 4};
    do {
        part1 = max(part1, thruster(phase, program));
    } while (next_permutation(phase.begin(), phase.end()));
    phase = {5, 6, 7, 8, 9};
    do {
        part2 = max(part2, feedback(phase, program));
    } while (next_permutation(phase.begin(), phase.end()));
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
