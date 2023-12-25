#include <bits/stdc++.h>
using namespace std;
using num = long long;

vector<num> findGroups(map<string, vector<string>> wires) {
    vector<num> result;
    vector<string> unvisited;
    for (auto it : wires) unvisited.push_back(it.first);
    while (!unvisited.empty()) {
        num groupSize = 0;
        string first = unvisited[0];
        queue<string> q;
        q.push(first);
        while (!q.empty()) {
            string current = q.front();
            q.pop();
            if (find(unvisited.begin(), unvisited.end(), current) == unvisited.end()) continue;
            unvisited.erase(remove(unvisited.begin(), unvisited.end(), current), unvisited.end());
            ++groupSize;
            if (wires.find(current) != wires.end()) {
                for (string next : wires[current]) {
                    if(find(unvisited.begin(), unvisited.end(), next) != unvisited.end()) q.push(next);
                }
            }
        }
        result.push_back(groupSize);
    }
    return result;
}

void disconnect(pair<string, string> wire, map<string, vector<string>> &wires) {
    wires[wire.first].erase(remove(wires[wire.first].begin(), wires[wire.first].end(), wire.second), wires[wire.first].end());
    wires[wire.second].erase(remove(wires[wire.second].begin(), wires[wire.second].end(), wire.first), wires[wire.second].end());
}

pair<num, num> disconnect(vector<pair<string, string>> uq, map<string, vector<string>> wires) {
    for (auto wire : uq) disconnect(wire, wires);
    vector<num> groups = findGroups(wires);
    if (groups.size() == 2) return {groups[0], groups[1]};
    else return {-1, -1};
}

int main() {
    string line;
    map<string, vector<string>> wires;
    while (getline(cin, line)) {
        string component1 = line.substr(0, line.find(":"));
        stringstream ss(line.substr(line.find(":") + 2));
        string component2;
        while (ss >> component2) {
            if (wires.find(component1) == wires.end()) wires[component1] = {component2};
            else wires[component1].push_back(component2);
            if (wires.find(component2) == wires.end()) wires[component2] = {component1};
            else wires[component2].push_back(component1);
        }
    }
    vector<pair<string, string>> uq;
    for (auto it1 : wires) {
        for (auto it2 : wires) {
            if (it1.first == it2.first) continue;
            if (it2.first < it1.first) continue;
            if (find(wires[it1.first].begin(), wires[it1.first].end(), it2.first) != wires[it1.first].end()) uq.push_back({it1.first, it2.first});
        }
    }
    bool found = false;
    for (num i = 0; i < uq.size(); ++i) {
        if (found) break;
        for (num j = i + 1; j < uq.size(); ++j) {
            if (found) break;
            for (num k = j + 1; k < uq.size(); ++k) {
                if (found) break;
                pair<num, num> result = disconnect({uq[i], uq[j], uq[k]}, wires);
                if (result.first != -1 && result.second != -1) {
                    cout << "Part 1: " << result.first * result.second << endl;
                    found = true;
                }
            }
        }
    }
    return 0;
}
