#include <bits/stdc++.h>
using namespace std;
using num = long long;

map<tuple<string, bool, bool>, num> dp;

num dfs(map<string, vector<string>> &adj, string cur, pair<bool, bool> seen) {
    if (dp.find({cur, seen.first, seen.second}) != dp.end()) return dp[{cur, seen.first, seen.second}];
    if (cur == "out") return seen.first == true && seen.second == true ? 1 : 0;
    num sum = 0;
    for (string a : adj[cur]) {
        auto b = seen;
        if (!b.first && a == "dac") b.first = true;
        if (!b.second && a == "fft") b.second = true;
        sum += dfs(adj, a, b);
    }
    dp[{cur, seen.first, seen.second}] = sum;
    return sum;
}


int main() {
    num part1 = 0, part2 = 0;
    string line;
    map<string, vector<string>> adj;
    while (getline(cin, line)) {
        string from = line.substr(0, line.find(':'));
        vector<string> c;
        string o = line.substr(line.find(':') + 2);
        stringstream ss(o);
        string p;
        while (getline(ss, p, ' ')) c.push_back(p);
        adj[from] = c;
    }
    queue<string> q;
    q.push("you");
    while (!q.empty()) {
        string cur = q.front(); q.pop();
        if (cur == "out") {
            ++part1;
            continue;
        }
        for (string a : adj[cur]) q.push(a);
    }
    part2 = dfs(adj, "svr", {false, false});
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
