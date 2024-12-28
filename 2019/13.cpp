#include "intcode.hpp"
using coord = pair<num, num>;

num part2(string input) {
    intcode prog(input);
    prog.memory[0] = 2;
    prog.run();
    num score = 0;
    coord ball, paddle;
    while (!prog.halted) {
        prog.output = {};
        num input = 0;
        if (paddle.second < ball.second) input = 1;
        else if (paddle.second > ball.second) input = -1;
        prog.run(input);
        for (num i = 0; i < prog.output.size(); i += 3) {
            num col = prog.output[i];
            num row = prog.output[i + 1];
            num block = prog.output[i + 2];
            if (col == -1 & row == 0) {
                score = block;
            } else {
                if (block == 4) ball = {row, col};
                else if (block == 3) paddle = {row, col};
            }
        }
    }
    return score;
}

int main() {
    num part1 = 0;
    string line;
    getline(cin, line);
    intcode prog(line);
    prog.run();
    for (num i = 2; i < prog.output.size(); i += 3) {
        if (prog.output[i] == 2) ++part1;
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2(line) << endl;
    return 0;
}
