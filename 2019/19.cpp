#include "intcode.hpp"

int main() {
    num part1 = 0, part2 = 0;
    string line;
    getline(cin, line);
    intcode orig(line);
    for (num x = 0; x < 50; ++x) {
        for (num y = 0; y < 50; ++y) {
            intcode prog = orig;
            prog.run({x, y});
            if (prog.output[0] == 1) ++part1;
        }
    }
    cout << "Part 1: " << part1 << endl;
    num y = 100, prevX = 0;
    while (true) {
        num x = prevX, lastX;
        bool foundLineStart = false;
        while (true) {
            intcode prog = orig;
            prog.run({x, y});
            if (prog.output[0] == 1) {
                if (!foundLineStart) {
                    foundLineStart = true;
                    prevX = x;
                }
            } else {
                if (foundLineStart) {
                    lastX = x - 1;
                    break;
                }
            }
            ++x;
        }
        num length = lastX - prevX;
        if (length >= 100) {
            num testX = lastX - 99;
            bool found = true;
            for (num yy = 0; yy < 100; ++yy) {
                intcode prog = orig;
                prog.run({testX, y + yy});
                if (prog.output[0] != 1) {
                    found = false;
                    break;
                }
            }
            if (found) {
                cout << "Part 2: " << testX * 10000 + y << endl;
                return 0;
            }
        }
        ++y;
    }
    return 0;
}
