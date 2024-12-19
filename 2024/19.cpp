#include <bits/stdc++.h>
using namespace std;
using num = long long;

num count(string design, vector<string> &towels, map<string, num> &dp) {
    if (dp[design] != 0) return dp[design];
    num ans = 0;
    for (string towel : towels) {
        if (design.length() > towel.length()) {
            if (design.substr(0, towel.length()) == towel) {
                string sub = design.substr(towel.length());
                ans += count(sub, towels, dp);
            }
        } else if (design == towel) {
            ++ans;
        }
    }
    dp[design] = ans;
    return ans;
}

int main() {
    num part1 = 0, part2 = 0;
    string line, towel;
    getline(cin, line);
    replace(line.begin(), line.end(), ',', ' ');
    stringstream ss(line);
    vector<string> towels;
    while (ss >> towel) towels.push_back(towel);
    getline(cin, line);
    map<string, num> dp;
    while (getline(cin, line)) {
        num ways = count(line, towels, dp);
        if (ways != 0) ++part1;
        part2 += ways;
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
