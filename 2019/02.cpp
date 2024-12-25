#include <bits/stdc++.h>
using namespace std;
using num = long long;

void run(vector<num> &program) {
    num pointer = 0;
    while (true) {
        num opcode = program[pointer];
        if (opcode == 1) program[program[pointer + 3]] = program[program[pointer + 1]] + program[program[pointer + 2]];
        else if (opcode == 2) program[program[pointer + 3]] = program[program[pointer + 1]] * program[program[pointer + 2]];
        else if (opcode == 99) break;
        pointer += 4;
    }
}

num part1(vector<num> program) {
    program[1] = 12;
    program[2] = 2;
    run(program);
    return program[0];
}

num part2(vector<num> program) {
    for (num noun = 0; noun < 100; ++noun) {
        for (num verb = 0; verb < 100; ++verb) {
            vector<num> prog = program;
            prog[1] = noun;
            prog[2] = verb;
            run(prog);
            if (prog[0] == 19690720) return 100 * noun + verb;
        }
    }
    return 0;
}

int main() {
    num n;
    string line;
    getline(cin, line);
    replace(line.begin(), line.end(), ',', ' ');
    stringstream ss(line);
    vector<num> program;
    while (ss >> n) program.push_back(n);
    cout << "Part 1: " << part1(program) << endl;
    cout << "Part 2: " << part2(program) << endl;
    return 0;
}
