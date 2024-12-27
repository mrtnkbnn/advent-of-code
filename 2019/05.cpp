#include "intcode.hpp"

int main() {
    string line;
    getline(cin, line);
    intcode prog1(line), prog2(line);
    prog1.run(1);
    prog2.run(5);
    cout << "Part 1: " << prog1.output.back() << endl;
    cout << "Part 2: " << prog2.output.back() << endl;
    return 0;
}
