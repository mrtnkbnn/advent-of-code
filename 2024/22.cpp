#include <bits/stdc++.h>
using namespace std;
using num = long long;

num next(num secret) {
    num result = secret * 64;
    secret ^= result;
    secret %= 16777216;
    result = secret / 32;
    secret ^= result;
    secret %= 16777216;
    result = secret * 2048;
    secret ^= result;
    secret %= 16777216;
    return secret;
}

num loop(num secret, num n, map<vector<num>, num> &dp) {
    vector<num> secrets = {secret};
    map<vector<num>, bool> mem;
    for (num i = 0; i < n; ++i) {
        secret = next(secret);
        secrets.push_back(secret);
    }
    for (num i = 4; i < n + 1; ++i) {
        vector<num> seq;
        for (num j = i - 3; j <= i; ++j) seq.push_back(secrets[j] % 10 - secrets[j - 1] % 10);
        if (!mem[seq]) {
            mem[seq] = true;
            dp[seq] += secrets[i] % 10;
        }
    }
    return secret;
}

int main() {
    num part1 = 0, part2 = LONG_LONG_MIN, secret;
    map<vector<num>, num> dp;
    while (cin >> secret) part1 += loop(secret, 2000, dp);
    for (auto [key, val] : dp) part2 = max(part2, val);
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
