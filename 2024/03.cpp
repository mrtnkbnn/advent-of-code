#include <bits/stdc++.h>
using namespace std;
using num = long long;

int main() {
    num part1 = 0, part2 = 0;
    regex r("mul\\(\\d+,\\d+\\)|do\\(\\)|don't");
    string memory;
    bool enabled = true;
    while (getline(cin, memory)) {
        for (sregex_iterator i = sregex_iterator(memory.begin(), memory.end(), r); i != sregex_iterator(); ++i) {
            smatch match = *i;
            if (match.str() == "do()") {
                enabled = true;
            } else if (match.str() == "don't") {
                enabled = false;
            } else {
                num left = stoll(match.str().substr(4, match.str().find(",") - 4));
                num right = stoll(match.str().substr(match.str().find(",") + 1, match.str().find(")") - match.str().find(",") - 1));
                part1 += left * right;
                if (enabled) part2 += left * right;
            }
        }
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
