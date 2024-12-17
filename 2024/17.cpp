#include <bits/stdc++.h>
using namespace std;
using num = long long;

num combo(num operand, num registerA, num registerB, num registerC) {
    if (operand < 4) return operand;
    else if (operand == 4) return registerA;
    else if (operand == 5) return registerB;
    else if (operand == 6) return registerC;
    return -1;
}

void backtrace(num pointer, num a, vector<num> &program, set<num> &results) {
    num b = a % 8;
    b = b ^ 1;
    if ((1LL << b) == 0) return;
    num c = a / (1LL << b);
    b = b ^ c;
    b = b ^ 6;
    num result = b % 8;
    if (result == program[pointer]) {
        if (pointer == 0) {
            results.insert(a);
            return;
        }
        for (num i = 0; i < 8; ++i) {
            backtrace(pointer - 1, a * 8 + i, program, results);
        }
    }
}

int main() {
    string part1 = "", line;
    num registerA, registerB, registerC, n;
    getline(cin, line);
    registerA = stoll(line.substr(line.find(": ") + 2));
    getline(cin, line);
    registerB = stoll(line.substr(line.find(": ") + 2));
    getline(cin, line);
    registerC = stoll(line.substr(line.find(": ") + 2));
    getline(cin, line);
    getline(cin, line);
    stringstream ss(line.substr(line.find(": ") + 2));
    vector<num> program;
    while (ss >> n) {
        program.push_back(n);
        ss.ignore();
    }
    num pointer = 0;
    while (pointer < program.size()) {
        num opcode = program[pointer];
        num operand = program[pointer + 1];
        if (opcode == 0) {
            num numerator = registerA;
            num denominator = 1 << combo(operand, registerA, registerB, registerC);
            registerA = numerator / denominator;
            pointer += 2;
        } else if (opcode == 1) {
            registerB = registerB ^ operand;
            pointer += 2;
        } else if (opcode == 2) {
            registerB = combo(operand, registerA, registerB, registerC) % 8;
            pointer += 2;
        } else if (opcode == 3) {
            if (registerA == 0) pointer += 2;
            else pointer = operand;
        } else if (opcode == 4) {
            registerB = registerB ^ registerC;
            pointer += 2;
        } else if (opcode == 5) {
            part1 += to_string(combo(operand, registerA, registerB, registerC) % 8) + ",";
            pointer += 2;
        } else if (opcode == 6) {
            num numerator = registerA;
            num denominator = 1 << combo(operand, registerA, registerB, registerC);
            registerB = numerator / denominator;
            pointer += 2;
        } else if (opcode == 7) {
            num numerator = registerA;
            num denominator = 1 << combo(operand, registerA, registerB, registerC);
            registerC = numerator / denominator;
            pointer += 2;
        }
    }
    part1.pop_back();
    set<num> results;
    for (num a : {0, 1, 2, 3, 4, 5, 6, 7}) backtrace(program.size() - 1, a, program, results);
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << *results.begin() << endl;
    return 0;
}
