#include <bits/stdc++.h>
using namespace std;
using num = long long;

bool invalid(string s) {
    return s.substr(0, s.length() / 2) == s.substr(s.length() / 2);
}

bool invalid2(string s) {
    for (num i = 1; i <= s.length() / 2; ++i) {
        string p = s.substr(0, i), t = "";
        for (num j = 0; j < s.length() / i; ++j) t += p;
        if (t == s) return true;
    }
    return false;
}

int main() {
    num part1 = 0, part2 = 0, a, b;
    string line;
    getline(cin, line);
    replace(line.begin(), line.end(), ',', ' ');
    replace(line.begin(), line.end(), '-', ' ');
    stringstream ss(line);
    while (ss >> a >> b) {
        for (num i = a; i <= b; ++i) {
            if (invalid(to_string(i))) part1 += i;
            if (invalid2(to_string(i))) part2 += i;
        }
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
