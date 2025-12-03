#include <bits/stdc++.h>
using namespace std;
using num = long long;

string joltage(string bank, num len) {
    if (len == 0) return "";
    char best = bank[0];
    num pos = 0;
    for (num i = 1; i < bank.length() - len + 1; ++i) {
        if (bank[i] > best) {
            best = bank[i];
            pos = i;
        }
    }
    return best + joltage(bank.substr(pos + 1), len - 1);
}

int main() {
    num part1 = 0, part2 = 0;
    string line;
    while (getline(cin, line)) {
        part1 += stoll(joltage(line, 2));
        part2 += stoll(joltage(line, 12));
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
