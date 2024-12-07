#include <bits/stdc++.h>
using namespace std;
using num = long long;

bool isTrue(num eq, vector<num> &cal, num cur, num idx, bool conc) {
    if (idx == cal.size()) return eq == cur;
    num left = idx == 1 ? cal[0] : cur;
    num right = cal[idx];
    return isTrue(eq, cal, left + right, idx + 1, conc) || isTrue(eq, cal, left * right, idx + 1, conc) || (conc && isTrue(eq, cal, stoll(to_string(left) + to_string(right)), idx + 1, conc));
}

int main() {
    num part1 = 0, part2 = 0, n;
    string line;
    while (getline(cin, line)) {
        num eq = stoll(line.substr(0, line.find(":")));
        vector<num> cal;
        stringstream ss(line.substr(line.find(": ") + 2));
        while (ss >> n) cal.push_back(n);
        if (isTrue(eq, cal, 0, 1, false)) part1 += eq;
        if (isTrue(eq, cal, 0, 1, true)) part2 += eq;
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
