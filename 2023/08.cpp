#include <bits/stdc++.h>
using namespace std;
using num = long long;

int main() {
    num part1 = 0, part2 = 1;
    string instructions, line;
    map<string, pair<string, string>> network;
    vector<string> currents;
    getline(cin, instructions);
    while (getline(cin, line)) {
        if (line == "") continue;
        network[line.substr(0, 3)] = {line.substr(7, 3), line.substr(12, 3)};
        if (line.substr(0, 3)[2] == 'A') currents.push_back(line.substr(0, 3));
    }
    num instructionIndex = 0;
    string current = "AAA";
    while (current != "ZZZ") {
        char instruction = instructions[instructionIndex];
        if (instruction == 'L') current = network[current].first;
        else current = network[current].second;
        ++part1;
        ++instructionIndex;
        if (instructionIndex == instructions.size()) instructionIndex = 0;
    }
    vector<num> results;
    for (num i = 0; i < currents.size(); ++i) {
        num result = 0;
        instructionIndex = 0;
        string current = currents[i];
        while (current[2] != 'Z') {
            char instruction = instructions[instructionIndex];
            if (instruction == 'L') current = network[current].first;
            else current = network[current].second;
            ++result;
            ++instructionIndex;
            if (instructionIndex == instructions.size()) instructionIndex = 0;
        }
        results.push_back(result);
    }
    for (num n : results) part2 = lcm(part2, n);
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
