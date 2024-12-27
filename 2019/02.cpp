#include "intcode.hpp"

num part2(string line) {
    for (num noun = 0; noun < 100; ++noun) {
        for (num verb = 0; verb < 100; ++verb) {
            intcode prog(line);
            prog.memory[1] = noun;
            prog.memory[2] = verb;
            prog.run();
            if (prog.memory[0] == 19690720) return 100 * noun + verb;
        }
    }
    return 0;
}

int main() {
    num n;
    string line;
    getline(cin, line);
    intcode prog(line);
    prog.memory[1] = 12;
    prog.memory[2] = 2;
    prog.run();
    cout << "Part 1: " << prog.memory[0] << endl;
    cout << "Part 2: " << part2(line) << endl;
    return 0;
}
