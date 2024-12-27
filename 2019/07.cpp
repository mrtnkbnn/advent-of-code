#include "intcode.hpp"

num thruster(vector<num> phase, string line) {
    vector<intcode> amplifiers(5, intcode(line));
    num prev = 0;
    for (num i = 0; i < phase.size(); ++i) {
        amplifiers[i].run({phase[i], prev});
        prev = amplifiers[i].output.back();
    }
    return prev;
}

num feedback(vector<num> phase, string line) {
    vector<intcode> amplifiers(5, intcode(line));
    for (num i = 0; i < 5; ++i) amplifiers[i].input.push_back(phase[i]);
    num pointer = 0;
    num prev = 0;
    while (true) {
        amplifiers[pointer].run(prev);
        prev = amplifiers[pointer].output.back();
        if (pointer == 4 && amplifiers[pointer].halted) break;
        pointer = (pointer + 1) % 5;
    }
    return prev;
}

int main() {
    num part1 = LONG_LONG_MIN, part2 = LONG_LONG_MIN;
    string line;
    getline(cin, line);
    vector<num> phase = {0, 1, 2, 3, 4};
    do {
        part1 = max(part1, thruster(phase, line));
    } while (next_permutation(phase.begin(), phase.end()));
    phase = {5, 6, 7, 8, 9};
    do {
        part2 = max(part2, feedback(phase, line));
    } while (next_permutation(phase.begin(), phase.end()));
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
