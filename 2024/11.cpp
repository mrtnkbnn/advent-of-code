#include <bits/stdc++.h>
using namespace std;
using num = long long;

num split(num stone, num blinks, map<num, map<num, num>> &dp) {
    if (blinks == 0) return 1;
    num ans = dp[stone][blinks];
    if (ans != 0) return ans;
    else if (stone == 0) ans = split(1, blinks - 1, dp);
    else if (to_string(stone).length() % 2 == 0) ans = split(stoll(to_string(stone).substr(0, to_string(stone).length() / 2)), blinks - 1, dp) + split(stoll(to_string(stone).substr(to_string(stone).length() / 2)), blinks - 1, dp);
    else ans = split(stone * 2024, blinks - 1, dp);
    dp[stone][blinks] = ans;
    return ans;
}

int main() {
    num part1 = 0, part2 = 0, n;
    map<num, map<num, num>> dp;
    while (cin >> n) {
        part1 += split(n, 25, dp);
        part2 += split(n, 75, dp);
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
