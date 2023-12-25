#include <bits/stdc++.h>
using namespace std;
using num = long long;

map<pair<string, string>, num> bfs(string start, map<string, vector<string>> &wires, map<string, bool> visited) {
    map<pair<string, string>, num> result;
    queue<string> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        string current = q.front();
        q.pop();
        for (string next : wires[current]) {
            if (!visited[next]) {
                q.push(next);
                visited[next] = true;
                ++result[{min(current, next), max(current, next)}];
            }
        }
    }
    return result;
}

pair<string, string> popular(set<string> &vertices, map<string, vector<string>> &wires, map<string, bool> visited) {
    num mostPopularCount = LONG_LONG_MIN;
    pair<string, string> mostPopular;
    map<pair<string, string>, num> results;
    for (string vertex : vertices) {
        map<pair<string, string>, num> result = bfs(vertex, wires, visited);
        for (auto it : result) results[it.first] += it.second;
    }
    for (auto it : results) {
        if (it.second > mostPopularCount) {
            mostPopularCount = it.second;
            mostPopular = it.first;
        }
    }
    return mostPopular;
}

int main() {
    string line;
    map<string, vector<string>> wires;
    set<string> vertices;
    while (getline(cin, line)) {
        string component = line.substr(0, line.find(":"));
        vertices.insert(component);
        stringstream ss(line.substr(line.find(":") + 2));
        string wire;
        while (ss >> wire) {
            vertices.insert(wire);
            if (wires.find(component) == wires.end()) wires[component] = {wire};
            else wires[component].push_back(wire);
            if (wires.find(wire) == wires.end()) wires[wire] = {component};
            else wires[wire].push_back(component);
        }
    }
    map<string, bool> visited;
    for (string vertex : vertices) visited[vertex] = false;
    for (num i = 0; i < 3; ++i) {
        pair<string, string> result = popular(vertices, wires, visited);
        wires[result.first].erase(find(wires[result.first].begin(), wires[result.first].end(), result.second));
        wires[result.second].erase(find(wires[result.second].begin(), wires[result.second].end(), result.first));
        if (wires[result.first].empty()) wires.erase(wires.find(result.first));
        if (wires[result.second].empty()) wires.erase(wires.find(result.second));
    }
    num groupSize = 0;
    string start = *vertices.begin();
    queue<string> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        string current = q.front();
        q.pop();
        ++groupSize;
        for (string next : wires[current]) {
            if (!visited[next]) {
                q.push(next);
                visited[next] = true;
            }
        }
    }
    cout << "Part 1: " << groupSize * (vertices.size() - groupSize) << endl;
    return 0;
}
