#include "intcode.hpp"

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
