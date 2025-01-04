#include "intcode.hpp"

num part1(string line) {
    intcode prog(line);
    string inst = "OR A T\nAND B T\nAND C T\nNOT T J\nAND D J\nWALK\n";
    vector<num> input;
    for (char c : inst) input.push_back((num)c);
    prog.run(input);
    return prog.output.back();
}

num part2(string line) {
    intcode prog(line);
    string inst = "OR A T\nAND B T\nAND C T\nNOT T J\nAND D J\nAND H J\nNOT A T\nOR T J\nRUN\n";
    vector<num> input;
    for (char c : inst) input.push_back((num)c);
    prog.run(input);
    return prog.output.back();
}

int main() {
    string line;
    getline(cin, line);
    cout << "Part 1: " << part1(line) << endl;
    cout << "Part 2: " << part2(line) << endl;
    return 0;
}
