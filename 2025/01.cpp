#include <bits/stdc++.h>
using namespace std;
using num = long long;

int main() {
    num part1 = 0, part2 = 0, cur = 50;
    string line;
    while (getline(cin, line)) {
        num turns = stoll(line.substr(1));
        part2 += turns / 100;
        bool middle = cur == 0 ? true : false;
        if (line[0] == 'L') cur -= (turns % 100);
        else cur += (turns % 100);
        if (!middle) {
            if (cur <= 0) ++part2;
            else if (cur >= 100) ++part2;
        }
        cur = ((cur % 100) + 100) % 100;
        if (cur == 0) ++part1;
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
