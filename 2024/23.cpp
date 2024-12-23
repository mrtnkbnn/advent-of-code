#include <bits/stdc++.h>
using namespace std;
using num = long long;

set<string> solve(set<string> group, map<string, set<string>> &adj, map<set<string>, set<string>> &dp) {
    if (dp.find(group) != dp.end()) return dp[group];
    set<set<string>> answers = {group};
    for (auto cur : group) {
        for (auto next : adj[cur]) {
            if (group.find(next) == group.end()) {
                bool adjAll = true;
                for (auto nextAdj : group) {
                    if (adj[next].find(nextAdj) == adj[next].end()) {
                        adjAll = false;
                        break;
                    }
                }
                if (adjAll) {
                    set<string> nextGroup = group;
                    nextGroup.insert(next);
                    auto better = solve(nextGroup, adj, dp);
                    answers.insert(better);
                }

            }
        }
    }
    set<string> bestGroup = group;
    num best = group.size();
    for (auto answer : answers) {
        if (answer.size() > best) {
            best = answer.size();
            bestGroup = answer;
        }
    }
    dp[group] = bestGroup;
    return bestGroup;
}

int main() {
    num part1 = 0, best = 0;
    string line, part2 = "";
    set<string> all, bestGroup;
    map<string, set<string>> adj;
    while (getline(cin, line)) {
        string left = line.substr(0, line.find("-"));
        string right = line.substr(line.find("-") + 1);
        all.insert(left);
        all.insert(right);
        adj[left].insert(right);
        adj[right].insert(left);
    }
    for (auto i = all.begin(); i != all.end(); ++i) {
        for (auto j = next(i); j != all.end(); ++j) {
            for (auto k = next(j); k != all.end(); ++k) {
                auto one = *i;
                auto two = *j;
                auto three = *k;
                if (one[0] == 't' || two[0] == 't' || three[0] == 't') {
                    if (adj[one].find(two) != adj[one].end() && adj[one].find(three) != adj[one].end() && adj[two].find(one) != adj[two].end() && adj[two].find(three) != adj[two].end() && adj[three].find(one) != adj[three].end() && adj[three].find(two) != adj[three].end()) ++part1;
                }
            }
        }
    }
    map<set<string>, set<string>> dp;
    for (auto i = all.begin(); i != all.end(); ++i) {
        for (auto j = next(i); j != all.end(); ++j) {
            if (adj[*i].find(*j) != adj[*i].end()) {
                auto better = solve({*i, *j}, adj, dp);
                if (better.size() > best) {
                    best = better.size();
                    bestGroup = better;
                }
            }
        }
    }
    for (auto a : bestGroup) part2 += a + ",";
    part2 = part2.substr(0, part2.length() - 1);
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
