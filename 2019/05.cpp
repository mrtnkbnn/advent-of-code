#include <bits/stdc++.h>
using namespace std;
using num = long long;

vector<num> init(string input) {
    replace(input.begin(), input.end(), ',', ' ');
    stringstream ss(input);
    vector<num> program;
    num n;
    while (ss >> n) program.push_back(n);
    return program;
}

vector<num> parameterModes(num parameters, vector<num> current) {
    vector<num> result = current;
    for (num i = 0; i < (parameters - current.size()); ++i) {
        result.push_back(0);
    }
    return result;
}

void run(vector<num> &program, num input) {
    num pointer = 0;
    while (true) {
        num value = program[pointer];
        vector<num> digits;
        while (value > 0) {
            digits.push_back(value % 10);
            value /= 10;
        }
        if (digits.size() == 1) digits.push_back(0);
        num opcode = digits[1] * 10 + digits[0];
        digits.erase(digits.begin(), digits.begin() + 2);
        if (opcode == 1) {
            num parameters = 3;
            auto modes = parameterModes(parameters, digits);
            num param1 = modes[0] == 0 ? program[program[pointer + 1]] : program[pointer + 1];
            num param2 = modes[1] == 0 ? program[program[pointer + 2]] : program[pointer + 2];
            program[program[pointer + 3]] = param1 + param2;
            pointer += parameters + 1;
        } else if (opcode == 2) {
            num parameters = 3;
            auto modes = parameterModes(parameters, digits);
            num param1 = modes[0] == 0 ? program[program[pointer + 1]] : program[pointer + 1];
            num param2 = modes[1] == 0 ? program[program[pointer + 2]] : program[pointer + 2];
            program[program[pointer + 3]] = param1 * param2;
            pointer += parameters + 1;
        } else if (opcode == 3) {
            num parameters = 1;
            program[program[pointer + 1]] = input;
            pointer += parameters + 1;
        } else if (opcode == 4) {
            num parameters = 1;
            auto modes = parameterModes(parameters, digits);
            num param1 = modes[0] == 0 ? program[program[pointer + 1]] : program[pointer + 1];
            cout << "Out: " << param1 << endl;
            pointer += parameters + 1;
        } else if (opcode == 5) {
            num parameters = 2;
            auto modes = parameterModes(parameters, digits);
            num param1 = modes[0] == 0 ? program[program[pointer + 1]] : program[pointer + 1];
            num param2 = modes[1] == 0 ? program[program[pointer + 2]] : program[pointer + 2];
            if (param1 != 0) {
                pointer = param2;
            } else {
                pointer += parameters + 1;
            }
        } else if (opcode == 6) {
            num parameters = 2;
            auto modes = parameterModes(parameters, digits);
            num param1 = modes[0] == 0 ? program[program[pointer + 1]] : program[pointer + 1];
            num param2 = modes[1] == 0 ? program[program[pointer + 2]] : program[pointer + 2];
            if (param1 == 0) {
                pointer = param2;
            } else {
                pointer += parameters + 1;
            }
        } else if (opcode == 7) {
            num parameters = 3;
            auto modes = parameterModes(parameters, digits);
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
            auto modes = parameterModes(parameters, digits);
            num param1 = modes[0] == 0 ? program[program[pointer + 1]] : program[pointer + 1];
            num param2 = modes[1] == 0 ? program[program[pointer + 2]] : program[pointer + 2];
            if (param1 == param2) {
                program[program[pointer + 3]] = 1;
            } else {
                program[program[pointer + 3]] = 0;
            }
            pointer += parameters + 1;
        } else if (opcode == 99) break;
    }
}

int main() {
    string line;
    getline(cin, line);
    auto original = init(line);
    auto program1 = original;
    auto program2 = original;
    cout << "Part 1:" << endl;
    run(program1, 1);
    cout << "Part 2:" << endl;
    run(program2, 5);
    return 0;
}
