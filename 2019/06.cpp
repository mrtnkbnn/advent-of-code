#include <bits/stdc++.h>
using namespace std;
using num = long long;

num count(string obj, map<string, string> &orbits) {
    if (orbits.find(obj) == orbits.end()) return 0;
    return 1 + count(orbits[obj], orbits);
}

int main() {
    num part1 = 0, part2 = 0;
    string line;
    set<string> objects;
    map<string, string> orbits;
    map<string, vector<string>> adj;
    while (getline(cin, line)) {
        string left = line.substr(0, line.find(")"));
        string right = line.substr(line.find(")") + 1);
        orbits[right] = left;
        objects.insert(left);
        objects.insert(right);
        adj[left].push_back(right);
        adj[right].push_back(left);
    }
    for (auto obj : objects) part1 += count(obj, orbits);
    map<string, bool> visited;
    queue<pair<string, num>> q;
    q.push({"YOU", 0});
    visited["YOU"] = true;
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        for (auto next : adj[cur.first]) {
            if (!visited[next]) {
                q.push({next, cur.second + 1});
                visited[next] = true;
                if (next == "SAN") part2 = cur.second - 1;
            }
        }
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}
